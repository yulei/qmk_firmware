/**
 * matrix_driver.c
 * default matrix implementation
 */

#include "quantum.h"
#include "debounce.h"
#include "ble_config.h"
#include "matrix_driver.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"

#ifdef MATRIX_USE_TCA6424
#   ifndef MATRIX_DETECT_PIN
#       error "the tca6424 interrupt detect pin must be defined first"
#   endif
#   include "i2c_master.h"
#   include "tca6424.h"
#endif

#ifndef MATRIX_PIN
#   define MATRIX_PIN uint32_t
#endif

MATRIX_PIN row_pins[] = MATRIX_ROW_PINS;
MATRIX_PIN col_pins[] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];    //raw values
static matrix_row_t matrix[MATRIX_ROWS];        //debounced values

matrix_driver_t matrix_driver;

#if defined(MATRIX_USE_GPIO)

static void matrix_pin_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    if (action == NRF_GPIOTE_POLARITY_LOTOHI) {
        for (int i = 0; i < MATRIX_ROWS; i++) {
            if (pin == row_pins[i]) {
                if (matrix_driver.event_callback) matrix_driver.event_callback(true);
                break;
            };
        }
    }
}
static void matrix_trigger_start(matrix_event_callback_f me_cb)
{
    if (matrix_driver.trigger_mode) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_pin_set(col_pins[i]);
    }

    ret_code_t                 err_code;
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull                       = NRF_GPIO_PIN_PULLDOWN;
    for (uint32_t i = 0; i < MATRIX_ROWS; i++) {
        // NRF_LOG_INFO("trigger init: pin=%d", row_pins[i]);
        err_code = nrf_drv_gpiote_in_init(row_pins[i], &in_config, matrix_pin_event_handler);
        APP_ERROR_CHECK(err_code);
        nrf_drv_gpiote_in_event_enable(row_pins[i], true);
    }
    matrix_driver.trigger_mode = true;
    matrix_driver.event_callback = me_cb;
    NRF_LOG_INFO("keyboard matrix trigger mode started");
}

static void matrix_trigger_stop(void)
{
    if (!matrix_driver.trigger_mode) {
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
    matrix_driver.trigger_mode = false;
    matrix_driver.event_callback = NULL;
    NRF_LOG_INFO("keyboard matrix trigger mode stopped");
}

static void init_pins(void)
{
    uint8_t i = 0;
    for (i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_cfg_output(col_pins[i]);
        nrf_gpio_pin_clear(col_pins[i]);
    }

    for (i = 0; i < MATRIX_ROWS; i++) {
        nrf_gpio_cfg_input(row_pins[i], NRF_GPIO_PIN_PULLDOWN);
    }
}

static void set_pin(MATRIX_PIN pin)
{
    nrf_gpio_pin_set(pin);
}

static void clear_pin(MATRIX_PIN pin)
{
    nrf_gpio_pin_clear(pin);
}

static uint8_t read_pin(MATRIX_PIN pin)
{
    return nrf_gpio_pin_read(pin) ? 1 : 0;
}

static void matrix_prepare_sleep(void)
{
    for (uint32_t i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_cfg_output(col_pins[i]);
        nrf_gpio_pin_set(col_pins[i]);
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        nrf_gpio_cfg_sense_input(row_pins[i], NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    }
}

static void matrix_scan_start(void) { init_pins(); }
static void matrix_scan_stop(void) { }


#elif defined(MATRIX_USE_TCA6424)

#define GET_PORT(p) (((p) >> 8) & 0xFF)
#define GET_PIN(p) ((p) & 0xFF)

static void set_pin(MATRIX_PIN pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data |= (1<<GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

static void clear_pin(MATRIX_PIN pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data &= ~(1<<GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

static uint8_t read_pin(MATRIX_PIN pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    return (data & (1<<GET_PIN(pin))) ? 1 : 0;
}

static void init_pins(void)
{
    tca6424_init();
    // set port0
    tca6424_write_config(TCA6424_PORT0, 0);
    // set port1
    tca6424_write_config(TCA6424_PORT1, 0);
    // set port2
    tca6424_write_config(TCA6424_PORT2, 0xF5);

    // clear output
    tca6424_write_port(TCA6424_PORT0, 0);
    tca6424_write_port(TCA6424_PORT1, 0);
    tca6424_write_port(TCA6424_PORT2, 0);
}

static void matrix_pin_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    if ((pin == MATRIX_DETECT_PIN) && (action == NRF_GPIOTE_POLARITY_HITOLO)) {
        // read port will clear the interrupt event
        tca6424_read_port(TCA6424_PORT0);
        tca6424_read_port(TCA6424_PORT1);
        tca6424_read_port(TCA6424_PORT2);
        if (matrix_driver.event_callback) matrix_driver.event_callback(true);
    }
}

static void matrix_trigger_start(matrix_event_callback_f event_cb)
{
    if (matrix_driver.trigger_mode) {
        return;
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        set_pin(col_pins[i]);
    }

    ret_code_t                 err_code;
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    in_config.pull                       = NRF_GPIO_PIN_PULLUP;
    err_code = nrf_drv_gpiote_in_init(MATRIX_DETECT_PIN, &in_config, matrix_pin_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(MATRIX_DETECT_PIN, true);
    matrix_driver.trigger_mode = true;
    matrix_driver.event_callback = event_cb;
    i2c_uninit();
    NRF_LOG_INFO("keyboard matrix trigger mode started");
}

static void matrix_trigger_stop(void)
{
    if (!matrix_driver.trigger_mode) {
        return;
    }

    i2c_init();

    for (int i = 0; i < MATRIX_COLS; i++) {
        clear_pin(col_pins[i]);
    }

    nrf_drv_gpiote_in_event_disable(MATRIX_DETECT_PIN);
    nrf_drv_gpiote_in_uninit(MATRIX_DETECT_PIN);
    matrix_driver.trigger_mode = false;
    matrix_driver.event_callback = NULL;
    NRF_LOG_INFO("keyboard matrix trigger mode stopped");
}

static void matrix_scan_start(void) { init_pins(); }

static void matrix_scan_stop(void) {}

static void matrix_prepare_sleep(void)
{
    i2c_uninit();
    for (uint32_t i = 0; i < MATRIX_COLS; i++) {
        set_pin(col_pins[i]);
    }

    nrf_gpio_cfg_sense_input(MATRIX_DETECT_PIN, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
}

#else
#error "Custom matrix implementation not supported"
#endif


void matrix_init(void)
{
    // init pins
    matrix_driver_init();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);
    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        set_pin(col_pins[col]);
        wait_us(30);
        // For each row...
        for(uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uint8_t tmp = row;
            // Store last value of row prior to reading
            matrix_row_t last_row_value = raw_matrix[tmp];

            // Check row pin state
            if (read_pin(row_pins[row])) {
                // Pin HI, set col bit
                raw_matrix[tmp] |= (1 << col);
            } else {
                // Pin LOW, clear col bit
                raw_matrix[tmp] &= ~(1 << col);
            }

            // Determine if the matrix changed state
            if ((last_row_value != raw_matrix[tmp]) && !(changed)) {
                changed = true;
            }
        }
        // Unselect col
        clear_pin(col_pins[col]);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    ble_driver.matrix_changed = changed ? 1 : 0;
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1<<col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void)
{
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}

__attribute__((weak))
void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak))
void matrix_init_user(void) { }

__attribute__((weak))
void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak))
void matrix_scan_user(void) {}

void matrix_driver_init(void)
{
    matrix_driver.trigger_start     = matrix_trigger_start;
    matrix_driver.trigger_stop      = matrix_trigger_stop;
    matrix_driver.scan_start        = matrix_scan_start;
    matrix_driver.scan_stop         = matrix_scan_stop;
    matrix_driver.prepare_sleep     = matrix_prepare_sleep;
    matrix_driver.event_callback    = NULL;
    matrix_driver.trigger_mode      = false;
    init_pins();
}
