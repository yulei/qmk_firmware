/**
 * @file ble_keyboard.c
 */

#include "ble_keyboard.h"
#include "ble_hid_service.h"
#include "app_timer.h"
#include "app_uart.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "nrf_uart.h"
#include "nrf_pwr_mgmt.h"

#include "report.h"
#include "host.h"
#include "keyboard.h"

// qmk stuff
#include "quantum.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

#define MAX_SCAN_COUNT 100
static volatile uint32_t scan_count = 0;

#define SYNC_BYTE_1 0xAA
#define SYNC_BYTE_2 0x55

typedef enum {
  CMD_KEY_REPORT,
  CMD_MOUSE_REPORT,
  CMD_SYSTEM_REPORT,
  CMD_CONSUMER_REPORT,
  CMD_RESET_TO_BOOTLOADER,
} command_t;

#define UART_TX_BUF_SIZE 128                        /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 128                        /**< UART RX buffer size. */

#define KEYBOARD_SCAN_INTERVAL APP_TIMER_TICKS(10) // keyboard scan interval
APP_TIMER_DEF(m_keyboard_timer_id); // keyboard scan timer id

static bool keyboard_pwr_mgmt_shutdown_handler(nrf_pwr_mgmt_evt_t event);
NRF_PWR_MGMT_HANDLER_REGISTER(keyboard_pwr_mgmt_shutdown_handler, NRF_PWR_MGMT_CONFIG_HANDLER_PRIORITY_COUNT - 1);

static void keyboard_pins_init(void);
static void keyboard_timer_init(void);
static void sense_pins_init(void);

static void keyboard_timout_handler(void *p_context);
static void keybaord_timer_start(void);
static void keybaord_timer_stop(void);

static void pin_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

static void vbus_detect_init(void);

static void uart_init(void);
static void uart_uninit(void);
static void uart_event_handle(app_uart_evt_t * p_event);
static void uart_send_cmd(command_t cmd, const uint8_t* report, uint32_t size);
static uint8_t compute_checksum(const uint8_t* data, uint32_t size);
static void send_reboot_cmd(void);

extern uint32_t row_pins[];
extern uint32_t col_pins[];
static bool matrix_trigger_enabled = false;

static void keyboard_matrix_trigger_start(void);
static void keyboard_matrix_trigger_stop(void);
static void keyboard_matrix_scan_init(void);

/* Host driver */
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

host_driver_t kbd_driver = {
    .keyboard_leds = keyboard_leds,
    .send_keyboard = send_keyboard,
    .send_mouse = send_mouse,
    .send_system = send_system,
    .send_consumer = send_consumer,
};


void ble_keyboard_init(void)
{
    ret_code_t err_code;
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    keyboard_setup();
    keyboard_init();
    host_set_driver(&kbd_driver);
    keyboard_timer_init();
    keyboard_pins_init();
    uart_init();
}

void ble_keyboard_start(void)
{
    keyboard_matrix_trigger_start();
}

void ble_keyboard_sleep_prepare(void)
{
    NRF_LOG_INFO("power down sleep preparing");
    // stop uart
    uart_uninit();
    // stop all timer
    app_timer_stop_all();
    // turn matrix to sense mode
    keyboard_matrix_trigger_stop();
    sense_pins_init();
}

void ble_keyboard_jump_bootloader(void)
{
    send_reboot_cmd();
}

void keyboard_pins_init(void)
{
    vbus_detect_init();
}

static void keyboard_timer_init(void)
{
    ret_code_t err_code;
    err_code = app_timer_create(&m_keyboard_timer_id,
                            APP_TIMER_MODE_REPEATED,
                            keyboard_timout_handler);
    APP_ERROR_CHECK(err_code);
}

/** this should implemented at keyboard level */
__attribute__((weak)) void keyboard_turnoff_leds(void)
{
#ifdef RGBLIGHT_ENABLE
    rgblight_disable();
    ws2812_uninit();
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable();
    // shutdown issi
    #ifdef IS31FL3731
        #ifdef DRIVER_ADDR_1
        //IS31FL3731_write_register(DRIVER_ADDR_1, 0x0A, 0);
        #endif
        #ifdef DRIVER_ADDR_2
        //IS31FL3731_write_register(DRIVER_ADDR_2, 0x0A, 0);
        #endif
    #endif
#endif
}

static bool keyboard_rgb_on(void)
{
#if defined(RGBLIGHT_ENABLE)
    extern rgblight_config_t rgblight_config;
    if (rgblight_config.enable ) return true;
#endif

#if defined(RGB_MATRIX_ENABLE)
    extern rgb_config_t rgb_matrix_config;
    if (rgb_matrix_config.enable) return true;
#endif
    return false;
}

static void keyboard_timout_handler(void *p_context)
{
    keyboard_task();

    if (ble_driver.matrix_changed) {
        scan_count = 0;
        ble_driver.matrix_changed = false;
    } else {
        if (!keyboard_rgb_on()) {
            scan_count++;
        } else if (ble_driver.battery_power <= BATTERY_LED_THRESHHOLD) {
            keyboard_turnoff_leds();
        }
    }

    // scan count overflow, switch to trigger mode
    if (scan_count >= MAX_SCAN_COUNT) {
        keybaord_timer_stop();
        keyboard_matrix_trigger_start();
        NRF_LOG_INFO("keyboard matrix swtiched to trigger mode");
        scan_count = 0;
    }
    // feed the power manager
    nrf_pwr_mgmt_feed();
}

static void keybaord_timer_start(void)
{
    ret_code_t err_code;

    err_code = app_timer_start(m_keyboard_timer_id, KEYBOARD_SCAN_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

static void keybaord_timer_stop(void)
{
    ret_code_t err_code;

    err_code = app_timer_stop(m_keyboard_timer_id);
    APP_ERROR_CHECK(err_code);

}

static uint8_t keyboard_leds(void) { return ble_driver.keyboard_led; }

static void send_keyboard(report_keyboard_t *report)
{
    if (ble_driver.output_target & OUTPUT_BLE) {
        ble_hid_service_send_report(NRF_REPORT_ID_KEYBOARD, &(report->raw[0]));
    }
    if ((ble_driver.output_target & OUTPUT_USB) && ble_driver.vbus_enabled) {
        if (!ble_driver.uart_enabled) {
            return;
            /*uart_init();
            if (!ble_driver.uart_enabled) {
                NRF_LOG_WARNING("Failed to initialize uart");
                return;
            }*/
        }

        uart_send_cmd(CMD_KEY_REPORT, (uint8_t*)report, sizeof(*report));
        NRF_LOG_INFO("Key report:");
        for (int i = 0; i < sizeof(*report); i++) {
            NRF_LOG_INFO("0x%x", report->raw[i]);
        }
    }
}

#ifdef MOUSEKEY_ENABLE

static void send_mouse(report_mouse_t *report)
{
    if (ble_driver.output_target & OUTPUT_BLE) {
        ble_hid_service_send_report(NRF_REPORT_ID_MOUSE, (uint8_t *)report);
    }
    if ((ble_driver.output_target & OUTPUT_USB) && ble_driver.vbus_enabled) {
        if (!ble_driver.uart_enabled) {
            return;
            /*uart_init();
            if (!ble_driver.uart_enabled) {
                NRF_LOG_WARNING("Failed to initialize uart");
                return;
            }*/
        }

        uart_send_cmd(CMD_MOUSE_REPORT, (uint8_t*)report, sizeof(*report));
        NRF_LOG_INFO("mouse report: 0x%x,0x%x,0x%x,0x%x,0x%x", report->buttons, report->x, report->y, report->v, report->h);
    }
}

#else

static void send_mouse(report_mouse_t *report) { (void)report; }

#endif

#ifdef EXTRAKEY_ENABELE

static void send_system(uint16_t data)
{
    if (ble_driver.output_target & OUTPUT_BLE) {
        ble_hid_service_send_report(NRF_REPORT_ID_SYSTEM, (uint8_t *)&data);
    }
    if ((ble_driver.output_target & OUTPUT_USB) && ble_driver.vbus_enabled) {
        if (!ble_driver.uart_enabled) {
            return;
            /*uart_init();
            if (!ble_driver.uart_enabled) {
                NRF_LOG_WARNING("Failed to initialize uart");
                return;
            }*/
        }
        uart_send_cmd(CMD_SYSTEM_REPORT, (uint8_t*) &data, sizeof(data));
        NRF_LOG_INFO("system report: 0x%x", data);
    }
}

static void send_consumer(uint16_t data)
{
    if (ble_driver.output_target & OUTPUT_BLE) {
        ble_hid_service_send_report(NRF_REPORT_ID_CONSUMER, (uint8_t *)&data);
    }

    if ((ble_driver.output_target & OUTPUT_USB) && ble_driver.vbus_enabled) {
        if (!ble_driver.uart_enabled) {
            return;
            /*uart_init();
            if (!ble_driver.uart_enabled) {
                NRF_LOG_WARNING("Failed to initialize uart");
                return;
            }*/
        }
        uart_send_cmd(CMD_CONSUMER_REPORT, (uint8_t*) &data, sizeof(data));
        NRF_LOG_INFO("sonsumer report: 0x%x", data);
    }
}

#else

static void send_system(uint16_t data) { (void)data; }
static void send_consumer(uint16_t data) { (void)data; }

#endif

static void pin_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    NRF_LOG_INFO("PIN EVENT: pin=%d, action=%d", pin, action);
    if (pin == VBUS_DETECT_PIN) {
        if (nrf_drv_gpiote_in_is_set(VBUS_DETECT_PIN)) {
            ble_driver.vbus_enabled = 1;
            ble_driver.output_target = OUTPUT_USB;
            uart_init();
            NRF_LOG_INFO("VBUS on, set output to USB");
        } else {
            ble_driver.vbus_enabled = 0;
            ble_driver.output_target = OUTPUT_BLE;
            uart_uninit();
            NRF_LOG_INFO("VBUS off, set output to BLE");
        }
    } else if (action == NRF_GPIOTE_POLARITY_LOTOHI) {
        bool row_pressed = false;
        for (uint32_t i = 0; i < MATRIX_ROWS; i++) {
            if (pin == row_pins[i]) {
                row_pressed = true;
                break;
            }
        }
        if (row_pressed) {
            // disable row event
            keyboard_matrix_trigger_stop();
            keyboard_matrix_scan_init();
            keybaord_timer_start();
            keyboard_task();
            scan_count = 0;
        }
    }

    // feed the power manager
    nrf_pwr_mgmt_feed();
}

static void vbus_detect_init(void)
{
    ret_code_t err_code;
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    err_code = nrf_drv_gpiote_in_init(VBUS_DETECT_PIN, &in_config, pin_event_handler);
    APP_ERROR_CHECK(err_code);
    ble_driver.vbus_enabled = nrf_drv_gpiote_in_is_set(VBUS_DETECT_PIN);
    nrf_drv_gpiote_in_event_enable(VBUS_DETECT_PIN, true);

    if (ble_driver.vbus_enabled) {
        ble_driver.output_target = OUTPUT_USB;
    } else {
        ble_driver.output_target = OUTPUT_BLE;
    }
}

static volatile bool uart_tx_done = false;

static void uart_event_handle(app_uart_evt_t *p_event)
{
    switch (p_event->evt_type) {
        case APP_UART_COMMUNICATION_ERROR:
            NRF_LOG_INFO("UART communication error: 0x%x", p_event->data.error_communication);
            break;
        case APP_UART_FIFO_ERROR:
            app_uart_flush();
            break;
        case APP_UART_DATA_READY:
            break;
        case APP_UART_TX_EMPTY:
            uart_tx_done = true;
            break;
        default:
            break;
    }
}

static void uart_init(void)
{
    uint32_t err_code;
    if (ble_driver.uart_enabled) {
        NRF_LOG_INFO("uart already enabled.\n");
        return;
    }

    NRF_LOG_INFO("uart tx pin: %d, rx pin: %d", UART_TX_PIN, UART_RX_PIN);
    const app_uart_comm_params_t comm_params = {
        .rx_pin_no = UART_RX_PIN,//NRF_UART_PSEL_DISCONNECTED,//UART_RX_PIN,
        .tx_pin_no = UART_TX_PIN,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity = false,
        .baud_rate = NRF_UART_BAUDRATE_115200,
    };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_event_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
    ble_driver.uart_enabled = 1;
    NRF_LOG_INFO("uart enabled.\n");
}

static void uart_uninit(void)
{
    uint32_t err_code;
    if (ble_driver.uart_enabled == 0) {
        NRF_LOG_INFO("uart not enabled.\n");
        return;
    }
    err_code = app_uart_close();
    APP_ERROR_CHECK(err_code);
    ble_driver.uart_enabled = 0;
    NRF_LOG_INFO("uart disabled.\n");
}

static void uart_send_cmd(command_t cmd, const uint8_t* report, uint32_t size)
{
    uint8_t checksum = cmd;
    checksum += compute_checksum(report, size);
    app_uart_put(SYNC_BYTE_1);
    app_uart_put(SYNC_BYTE_2);
    app_uart_put(size+3);
    app_uart_put(checksum);
    app_uart_put(cmd);
    for (uint32_t i = 0; i < size; i++) {
        app_uart_put(report[i]);
    }
}

static uint8_t compute_checksum(const uint8_t* data, uint32_t size)
{
    uint8_t checksum = 0;
    for (uint32_t i = 0; i < size; i++) {
        checksum += data[i];
    }
    return checksum;
}

static void sense_pins_init(void)
{
    for (uint32_t i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_cfg_output(col_pins[i]);
        nrf_gpio_pin_set(col_pins[i]);
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        nrf_gpio_cfg_sense_input(row_pins[i], NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    }
    // vbus detect
    nrf_gpio_cfg_sense_input(VBUS_DETECT_PIN, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
}

static void keyboard_matrix_trigger_start(void)
{
    if (matrix_trigger_enabled) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_pin_set(col_pins[i]);
    }

    ret_code_t err_code;
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLDOWN;
    for (uint32_t i = 0; i < MATRIX_ROWS; i++) {
        //NRF_LOG_INFO("trigger init: pin=%d", row_pins[i]);
        err_code = nrf_drv_gpiote_in_init(row_pins[i], &in_config, pin_event_handler);
        APP_ERROR_CHECK(err_code);
        nrf_drv_gpiote_in_event_enable(row_pins[i], true);
    }
    matrix_trigger_enabled = true;
    NRF_LOG_INFO("keyboard matrix trigger mode started");
}

static void keyboard_matrix_trigger_stop(void)
{
    if (!matrix_trigger_enabled) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_pin_clear(col_pins[i]);
    }

    for (uint32_t i = 0; i < MATRIX_ROWS; i++) {
        //NRF_LOG_INFO("trigger uninit: pin=%d", row_pins[i]);
        nrf_drv_gpiote_in_event_disable(row_pins[i]);
        nrf_drv_gpiote_in_uninit(row_pins[i]);
    }
    matrix_trigger_enabled = false;
    NRF_LOG_INFO("keyboard matrix trigger mode stopped");
}

extern void matrix_init(void);
static void keyboard_matrix_scan_init(void)
{
    matrix_init();
}

static bool keyboard_pwr_mgmt_shutdown_handler(nrf_pwr_mgmt_evt_t event)
{
    // currently we did not handle case by case
    switch (event) {
        case NRF_PWR_MGMT_EVT_PREPARE_WAKEUP:
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_SYSOFF:
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_DFU:
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_RESET:
            break;
        default:
            break;
    }
    ble_keyboard_sleep_prepare();
    return true;
}

#include "nrf_delay.h"
static void send_reboot_cmd(void)
{
    if (!ble_driver.vbus_enabled) {
        NRF_LOG_INFO("vbus not enable, can't reboot the usb controller");
        return;
    }

    if (!ble_driver.uart_enabled) {
        NRF_LOG_INFO("uart not enabled, can't send reboot command");
        return;
    }

    uint8_t checksum = CMD_RESET_TO_BOOTLOADER;
    uart_tx_done = false;
    app_uart_put(SYNC_BYTE_1);
    app_uart_put(SYNC_BYTE_2);
    app_uart_put(3);
    app_uart_put(checksum);
    app_uart_put(CMD_RESET_TO_BOOTLOADER);
    NRF_LOG_INFO("send reboot command to usb controller, set output to ble");
    ble_driver.output_target = OUTPUT_BLE;
}

// bluetooth control command
// F21 for toggle usb/ble output
// F22 for erase bond
// F23 for enter bootloader mode
bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed) {
        switch(keycode) {
        case KC_F21: // toggle usb/ble output
            if (ble_driver.output_target == OUTPUT_BLE) {
                if (ble_driver.vbus_enabled) {
                    NRF_LOG_INFO("set output to USB");
                    ble_driver.output_target = OUTPUT_USB;
                } else {
                    NRF_LOG_INFO("vbus not enabled, still using BLE");
                }
            } else {
                NRF_LOG_INFO("set output to BLE");
                ble_driver.output_target = OUTPUT_BLE;
            }
            return false;

        case KC_F22: // reset to erase bond mode
            NRF_LOG_INFO("reset to erase bond");
            sd_power_gpregret_set(RST_REGISTER, RST_ERASE_BOND);
            sd_nvic_SystemReset();
            return false;

        case KC_F23: // usb mcu to bootloader mode
            NRF_LOG_INFO("send reboot command");
            send_reboot_cmd();
            return false;
        default:
            break;
        }
    }
    return true;
}
