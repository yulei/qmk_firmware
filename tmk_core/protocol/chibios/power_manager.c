/**
 * power_manager.c
 */

#include "power_manager.h"
#include <ch.h>
#include <hal.h>

#include "timer.h"
#include "usb_main.h"
#include "adafruit_ble.h"

#define PWR_VBUS_DETECT_PORT  GPIOB
#define PWR_VBUS_DETECT_PIN   3

#define PWR_BLE_PORT GPIOA
#define PWR_BLE_PIN 10

// pre-defined time interval
#define PWR_NORMAL_SCAN_INTERVAL    10      // 10 ms
#define PWR_SLEEP_SCAN_INTERVAL     100     // 100 ms

#define PWR_NORMAL_INTERVAL         1000    // 1 s
#define PWR_SLEEP_INTERVAL          10000   // 10 s
#define PWR_STANDBY_INTERVAL        60000   // 60 s

typedef struct {
    uint8_t     supply;
    uint8_t     mode;
    bool        modified;
    uint32_t    modified_time;
    uint32_t    scan_time;
    thread_reference_t thread;
} pwr_obj_t;

static pwr_obj_t pwr_obj;

#define GPTDEV GPTD1
static void gptcb(GPTDriver *gptp) {
    (void)gptp;
    chSysLockFromISR();
    osalThreadResumeI(&(pwr_obj.thread), MSG_OK);
    chSysUnlockFromISR();
}

static const GPTConfig gptcfg = {
    10000,    /* 10kHz timer clock.*/
    gptcb,   /* Timer callback.*/
    0,
    0
};

static void pwr_vbus_init(void);
static bool pwr_vbus_on(void);
static void pwr_timer_init(void);

static void pwr_usb_start(void);
static void pwr_usb_stop(void);
static void pwr_ble_start(void);
static void pwr_ble_stop(void);
/*static void pwr_gpio_start(void);
static void pwr_gpio_stop(void);
static void pwr_spi_start(void);
static void pwr_spi_stop(void);
*/

static void pwr_sleep_ms(uint32_t ms);
static void pwr_suspend(void);

static void pwr_mode_run(void);
static void pwr_mode_sleep(void);
static void pwr_mode_stanby(void);


void pwr_init(void)
{
    pwr_vbus_init();
    pwr_timer_init();

    pwr_obj.supply          = pwr_vbus_on() ? PWR_VBUS : PWR_BATTERY;
    pwr_obj.mode            = PWR_MODE_RUN;
    pwr_obj.modified        = false;
    pwr_obj.scan_time       = timer_read32();
    pwr_obj.modified_time   = timer_read32();
    pwr_obj.thread          = NULL;
}

void pwr_task(void)
{
    if (pwr_vbus_on()) {
        if (pwr_obj.supply == PWR_BATTERY) {
            // usb power supplied
            pwr_usb_start();
        }
        pwr_obj.supply = PWR_VBUS;
        pwr_obj.mode   = PWR_MODE_RUN;
    } else {
        if (pwr_obj.supply == PWR_VBUS) {
            // usb power lost
            pwr_usb_stop();
        }
        pwr_obj.supply = PWR_BATTERY;
    }

    switch (pwr_obj.mode) {
    case PWR_MODE_RUN:
        pwr_mode_run();
        break;
    case PWR_MODE_SLEEP:
        pwr_mode_sleep();
        break;
    case PWR_MODE_STANDBY:
        pwr_mode_stanby();
        break;
    default:
        break;
    }
}

void pwr_scan_hook(matrix_row_t* matrix)
{
    pwr_obj.scan_time = timer_read32();
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix_row_t row = matrix_get_row(i);
        if (row != matrix[i]) {
            pwr_obj.modified = true;
            pwr_obj.modified_time = timer_read32();
            break;
        }
    }
}

// private functions
void pwr_vbus_init(void) { palSetPadMode(PWR_VBUS_DETECT_PORT, PWR_VBUS_DETECT_PIN, PAL_MODE_INPUT_PULLDOWN); }

bool pwr_vbus_on(void) { return palReadPad(PWR_VBUS_DETECT_PORT, PWR_VBUS_DETECT_PIN) != 0; }

void pwr_timer_init(void) { gptStart(&GPTDEV, &gptcfg); }

void pwr_sleep_ms(uint32_t ms)
{
    osalThreadSleepMilliseconds(ms);
}

void pwr_suspend(void)
{
    osalSysLock();
    osalThreadSuspendS(&pwr_obj.thread);
    osalSysUnlock();
}

void pwr_usb_start(void) { usb_driver_start(&USB_DRIVER); }
void pwr_usb_stop(void) { usb_driver_stop(&USB_DRIVER); }

/* void pwr_gpio_start(void){}
void pwr_gpio_stop(void){}
void pwr_spi_start(void){}
void pwr_spi_stop(void){}
*/
void pwr_ble_start(void)
{
    palSetPadMode(PWR_BLE_PORT, PWR_BLE_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(PWR_BLE_PORT, PWR_BLE_PIN);
    adafruit_ble_enable_keyboard();
}

void pwr_ble_stop(void)
{
    palSetPad(PWR_BLE_PORT, PWR_BLE_PIN);
    palSetPadMode(PWR_BLE_PORT, PWR_BLE_PIN, PAL_MODE_INPUT_ANALOG);
}

void pwr_mode_run(void)
{
    if (pwr_obj.supply == PWR_VBUS) {
        // do nothing in such case
        return;
    }

    uint32_t interval = 0;
    uint32_t scan_elapse = timer_elapsed32(pwr_obj.scan_time);
    if (pwr_obj.modified) {
        interval = PWR_NORMAL_SCAN_INTERVAL > scan_elapse ? PWR_NORMAL_INTERVAL - scan_elapse : 0;
        pwr_obj.modified = false;
    } else {
        uint32_t modified_elapse = timer_elapsed32(pwr_obj.modified_time);
        if (modified_elapse > PWR_SLEEP_INTERVAL) {
            interval = PWR_SLEEP_SCAN_INTERVAL > scan_elapse ? PWR_SLEEP_SCAN_INTERVAL - scan_elapse : 0;
            // move to sleep mode
            pwr_obj.mode = PWR_MODE_SLEEP;
        } else {
            interval = PWR_NORMAL_SCAN_INTERVAL > scan_elapse ? PWR_NORMAL_SCAN_INTERVAL - scan_elapse : 0;
        }
    }
    // sleep some time to save power
    pwr_sleep_ms(interval);
}

void pwr_mode_sleep(void)
{
    if (pwr_obj.supply == PWR_VBUS) {
        // move back to run mode
        pwr_obj.mode = PWR_MODE_RUN;
        return;
    }

    if (pwr_obj.modified) {
        // back to run mode
        pwr_obj.mode = PWR_MODE_RUN;
        pwr_obj.modified = false;
    } else {
        uint32_t modified_elapse = timer_elapsed32(pwr_obj.modified_time);
        if (modified_elapse > PWR_STANDBY_INTERVAL) {
            // turn BLE off
            pwr_ble_stop();
            pwr_obj.mode = PWR_MODE_STANDBY;
        }
        // setup time and suspend thread
        gptStartOneShot(&GPTDEV, 1000);
        pwr_suspend();
    }
}

void pwr_mode_stanby(void)
{
    if (pwr_obj.supply == PWR_VBUS) {
        // move back to run mode, turn ble on
        pwr_ble_start();
        pwr_obj.mode = PWR_MODE_RUN;
        return;
    }

    if (pwr_obj.modified) {
        // back to run mode
        pwr_ble_start();
        pwr_obj.mode     = PWR_MODE_RUN;
        pwr_obj.modified = false;
    } else {
        // setup time and suspend thread
        gptStartOneShot(&GPTDEV, 1000);
        pwr_suspend();
    }
}
