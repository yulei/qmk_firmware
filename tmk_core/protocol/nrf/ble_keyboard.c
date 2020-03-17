/**
 * @file ble_keyboard.c
 */

#include "ble_keyboard.h"
#include "ble_hid_service.h"
#include "app_timer.h"
#include "app_uart.h"
#include "app_gpiote.h"
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

// app gpiote
#define MAX_GPIOTE_USERS  2 /**< usb sense and matrix scann */
static uint32_t row_mask_all = 0;
static uint32_t col_mask_all = 0;
app_gpiote_user_id_t keyboard_user_id;
app_gpiote_user_id_t usb_sense_user_id;

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
static void keyboard_timout_handler(void *p_context);
static void keybaord_timer_start(void);
static void keybaord_timer_stop(void);

static void usb_sense_init(void);
static void usb_sense_handler(uint32_t const * p_low_to_high, uint32_t const * p_high_to_low);
static void uart_init(void);
static void uart_uninit(void);
static void uart_event_handle(app_uart_evt_t * p_event);
static void uart_send_cmd(command_t cmd, const uint8_t* report, uint32_t size);
static uint8_t compute_checksum(const uint8_t* data, uint32_t size);

extern uint32_t row_pins[];
extern uint32_t col_pins[];
static bool matrix_trigger_enabled = false;
static void keyboard_matrix_trigger_handler(uint32_t const * p_low_to_high, uint32_t const * p_high_to_low);
static void keyboard_matrix_trigger_init(void);
static void keyboard_matrix_trigger_start(void);
static void keyboard_matrix_trigger_stop(void);
static void keyboard_matrix_scan_init(void);
//static void keyboard_matrix_scan_uninit(void);

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
    APP_GPIOTE_INIT(MAX_GPIOTE_USERS);
    keyboard_setup();
    keyboard_init();
    host_set_driver(&kbd_driver);
    keyboard_timer_init();
    keyboard_pins_init();
    nrf_pwr_mgmt_feed();
}

void ble_keyboard_start(void)
{
    keyboard_matrix_trigger_start();
}

void keyboard_pins_init(void)
{
    usb_sense_init();
    keyboard_matrix_trigger_init();
}

static void keyboard_timer_init(void)
{
    ret_code_t err_code;
    err_code = app_timer_create(&m_keyboard_timer_id,
                            APP_TIMER_MODE_REPEATED,
                            keyboard_timout_handler);
    APP_ERROR_CHECK(err_code);
}

static void keyboard_timout_handler(void *p_context)
{

#ifdef RGBLIGHT_ENABLE
    extern rgblight_config_t rgblight_config;
    if ( !rgblight_config.enable) {
#endif
        scan_count++;
#ifdef RGBLIGHT_ENABLE
    }
#endif
    keyboard_task();
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
    if (ble_driver.output_target & OUTPUT_USB) {
        if ( !ble_driver.uart_enabled) {
            return;
        }

        uart_send_cmd(CMD_KEY_REPORT, (uint8_t*)report, sizeof(*report));
        NRF_LOG_INFO("Key report:");
        for (int i = 0; i < sizeof(*report); i++) {
            NRF_LOG_INFO("0x%x", report->raw[i]);
        }
    }

    scan_count = 0;
}

#ifdef MOUSEKEY_ENABLE

static void send_mouse(report_mouse_t *report)
{
    if (ble_driver.output_target & OUTPUT_BLE) {
        ble_hid_service_send_report(NRF_REPORT_ID_MOUSE, (uint8_t *)report);
    }
    if (ble_driver.output_target & OUTPUT_USB) {
        if ( !ble_driver.uart_enabled) {
            return;
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
    if (ble_driver.output_target & OUTPUT_USB) {
        if ( !ble_driver.uart_enabled) {
            return;
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
    if (ble_driver.output_target & OUTPUT_USB) {
        if ( !ble_driver.uart_enabled) {
            return;
        }
        uart_send_cmd(CMD_CONSUMER_REPORT, (uint8_t*) &data, sizeof(data));
        NRF_LOG_INFO("sonsumer report: 0x%x", data);
    }
}

#else

static void send_system(uint16_t data) { (void)data; }
static void send_consumer(uint16_t data) { (void)data; }

#endif

static void usb_sense_handler(uint32_t const * p_low_to_high, uint32_t const * p_high_to_low)
{
    if ((*p_low_to_high) & (1ul<<USB_SENSE_PIN)) {
        ble_driver.usb_enabled = 1;
        uart_init();
    }

    if ((*p_high_to_low) & (1ul<<USB_SENSE_PIN)) {
        ble_driver.usb_enabled = 0;
        uart_uninit();
    }
    NRF_LOG_INFO("usb sense: status = %d\n", ble_driver.usb_enabled);
}

static void usb_sense_init(void)
{
    ret_code_t err_code;
    static uint32_t usb_sense_h2l = 1ul << USB_SENSE_PIN;
    static uint32_t usb_sense_l2h = 1ul << USB_SENSE_PIN;
    err_code = app_gpiote_user_register(&usb_sense_user_id, &usb_sense_l2h, &usb_sense_h2l, usb_sense_handler);
    APP_ERROR_CHECK(err_code);
    int state = nrf_gpio_pin_read(USB_SENSE_PIN);
    if (state > 0) {
        ble_driver.usb_enabled = 1;
        uart_init();
    } else {
        ble_driver.usb_enabled = 0;
        uart_uninit();
    }
    NRF_LOG_INFO("usb init state: status = %d\n", ble_driver.usb_enabled);
    app_gpiote_user_enable(usb_sense_user_id);
}

static volatile bool uart_tx_done = false;

static void uart_event_handle(app_uart_evt_t *p_event)
{
    switch (p_event->evt_type) {
        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
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
        NRF_LOG_INFO("uart alread enabled.\n");
        return;
    }

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

static void keyboard_matrix_trigger_handler(uint32_t const * p_low_to_high, uint32_t const * p_high_to_low)
{
    if (matrix_trigger_enabled) {
        NRF_LOG_INFO("Row was pressed");
        // turn off trigger
        keyboard_matrix_trigger_stop();
        // turn on scan mode
        keyboard_matrix_scan_init();
        // start scan timer
        keybaord_timer_start();
    }
}

static void keyboard_matrix_trigger_init(void)
{
    ret_code_t err_code;
    uint32_t high_to_low = 0;
    if (col_mask_all == 0) {
        for (int i = 0; i < MATRIX_COLS; i++)  {
            col_mask_all |= 1ul << col_pins[i];
        }
    }
    if (row_mask_all == 0) {
        for (int i = 0; i < MATRIX_ROWS; i++) {
            row_mask_all |= 1ul << row_pins[i];
        }
    }

    err_code = app_gpiote_user_register(&keyboard_user_id, &row_mask_all, &high_to_low, keyboard_matrix_trigger_handler);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_INFO("keyboard matrix trigger mode initialized");
}

static void keyboard_matrix_trigger_start(void)
{
    if (matrix_trigger_enabled) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_pin_set(col_pins[i]);
    }
    app_gpiote_user_enable(keyboard_user_id);
    matrix_trigger_enabled = true;
}

static void keyboard_matrix_trigger_stop(void)
{
    if (!matrix_trigger_enabled) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_pin_clear(col_pins[i]);
    }
    app_gpiote_user_disable(keyboard_user_id);
    matrix_trigger_enabled = false;
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
    // stop all timer
    app_timer_stop_all();

    // turn matrix to trigger mode
    keyboard_matrix_trigger_start();

    return true;
}

//static void keyboard_matrix_scan_uninit(void) {}
#ifdef COMMAND_ENABLE
#include "command.h"
#include "nrf_delay.h"

static void send_reboot_cmd(void)
{
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
    while(!uart_tx_done) {
        nrf_delay_ms(1);
    }
    sd_power_gpregret_set(RST_REGISTER, RST_BOOTLOADER);
    sd_nvic_SystemReset();
}

// bluetooth control command, try to not confilict with the pre-defined key in command.h

bool command_extra(uint8_t code)
{
    switch (code) {
        case MAGIC_KC(CMD_BLE_TOGGLE):
            if (ble_driver.output_target&OUTPUT_BLE) {
                ble_driver.output_target &= ~OUTPUT_BLE;
            } else {
                ble_driver.output_target |= OUTPUT_BLE;
            }
            break;
        case MAGIC_KC(CMD_USB_TOGGLE):
            if (ble_driver.output_target&OUTPUT_USB) {
                ble_driver.output_target &= ~OUTPUT_USB;
            } else {
                ble_driver.output_target |= OUTPUT_USB;
            }
            break;
        case MAGIC_KC(CMD_ERASE_BOND):
            sd_power_gpregret_set(RST_REGISTER, RST_ERASE_BOND);
            sd_nvic_SystemReset();
            break;
        case MAGIC_KC(CMD_BOOTLOADER):
            // send reboot command to peer mcu
            send_reboot_cmd();
            break;
        default:
            break;
    }
    return false;
}
#endif
