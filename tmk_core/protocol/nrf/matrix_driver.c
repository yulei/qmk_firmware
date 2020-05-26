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

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];    //raw values
static matrix_row_t matrix[MATRIX_ROWS];        //debounced values
matrix_driver_t matrix_driver;

#if defined(MATRIX_USE_GPIO)

uint32_t row_pins[] = MATRIX_ROW_PINS;
uint32_t col_pins[] = MATRIX_COL_PINS;
matrix_event_callback_f event_cb = NULL;

static void matrix_pin_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    if (action == NRF_GPIOTE_POLARITY_LOTOHI) {
        for (int i = 0; i < MATRIX_ROWS; i++) {
            if (pin == row_pins[i]) {
                if (event_cb) event_cb(true);
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

    event_cb = me_cb;

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
    NRF_LOG_INFO("keyboard matrix trigger mode stopped");
}

static void matrix_scan_init(void)
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

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    nrf_gpio_pin_set(col_pins[current_col]);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        uint8_t tmp = row_index;
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[tmp];

        // Check row pin state
        if (nrf_gpio_pin_read(row_pins[row_index])) {
            // Pin HI, set col bit
            current_matrix[tmp] |= (1 << current_col);
        } else {
            // Pin LOW, clear col bit
            current_matrix[tmp] &= ~(1 << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[tmp]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    nrf_gpio_pin_clear(col_pins[current_col]);

    return matrix_changed;
}

static bool matrix_scan_task(void)
{
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        changed |= read_rows_on_col(raw_matrix, col);
    }
    return changed;
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

static void matrix_scan_start(void)
{
    matrix_scan_init();
}

static void matrix_scan_stop(void)
{
    // do nothing
}

void matrix_driver_init(void)
{
    matrix_driver.trigger_start = matrix_trigger_start;
    matrix_driver.trigger_stop  = matrix_trigger_stop;
    matrix_driver.scan_start    = matrix_scan_start;
    matrix_driver.scan_stop     = matrix_scan_stop;
    matrix_driver.scan_init     = matrix_scan_init;
    matrix_driver.scan_task     = matrix_scan_task;
    matrix_driver.prepare_sleep = matrix_prepare_sleep;
    matrix_driver.trigger_mode  = false;
    matrix_driver.scan_init();
}

#elif defined(MATRIX_USE_TC6424)

#else
#error "Custom matrix implementation not supported"
#endif

__attribute__((weak))
void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak))
void matrix_init_user(void) { }

__attribute__((weak))
void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak))
void matrix_scan_user(void) {}

void matrix_init(void)
{
    matrix_driver_init();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);
    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    bool changed = matrix_driver.scan_task();

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
