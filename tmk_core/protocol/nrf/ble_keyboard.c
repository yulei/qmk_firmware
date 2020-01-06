/**
 * @file ble_keyboard.c
 */

#include "ble_keyboard.h"
#include "ble_hid_service.h"
#include "app_timer.h"
#include "report.h"
#include "host.h"
#include "keyboard.h"

#define KEYBOARD_SCAN_INTERVAL APP_TIMER_TICKS(10) // keyboard scan interval
APP_TIMER_DEF(m_keyboard_timer_id); // keyboard scan timer id

static void keyboard_timer_init(void);
static void keyboard_timout_handler(void *p_context);

/* Host driver */
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);
host_driver_t  ble_driver = { keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer };

void keyboard_timout_handler(void *p_context) { keyboard_task(); }
void keyboard_timer_init(void)
{
    ret_code_t err_code;
    err_code = app_timer_create(&m_keyboard_timer_id,
                            APP_TIMER_MODE_REPEATED,
                            keyboard_timout_handler);
    APP_ERROR_CHECK(err_code);
}

void ble_keyboard_init(void)
{
    keyboard_setup();
    keyboard_init();
    host_set_driver(&ble_driver);
    keyboard_timer_init();
}

void ble_keyboard_timer_start(void)
{
    ret_code_t err_code;

    err_code = app_timer_start(m_keyboard_timer_id, KEYBOARD_SCAN_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

uint8_t keyboard_leds(void) { return keyboard_led_val_ble; }

void send_keyboard(report_keyboard_t *report) { hid_send_report(NRF_REPORT_ID_KEYBOARD, KEYBOARD_REPORT_SIZE, report->raw); }

#ifdef MOUSEKEY_ENABLE
void send_mouse(report_mouse_t *report) { hid_send_report(NRF_REPORT_ID_MOUSE, sizeof(report_mouse_t), (uint8_t *)report); }
#else
void send_mouse(report_mouse_t *report) { (void)report; }
#endif
#ifdef EXTRAKEY_ENABELE
void send_system(uint16_t data) { hid_send_report(NRF_REPORT_ID_SYSTEM, sizeof(uint16_t), (uint8_t *)&data); }
void send_consumer(uint16_t data) { hid_send_report(NRF_REPORT_ID_CONSUMER, sizeof(uint16_t), (uint8_t *)&data); }
#else
void send_system(uint16_t data) { (void)data; }
void send_consumer(uint16_t data) { (void)data; }
#endif
