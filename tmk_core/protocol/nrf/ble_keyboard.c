/**
 * @file ble_keyboard.c
 */

#include "ble_keyboard.h"
#include "ble_hid_service.h"
#include "report.h"
#include "host.h"
#include "keyboard.h"

/* Host driver */
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);
host_driver_t  ble_driver = { keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer };

void ble_keyboard_init(void)
{
    keyboard_setup();
    keyboard_init();
    host_set_driver(&ble_driver);
}

uint8_t keyboard_leds(void) { return keyboard_led_val_ble; }

void    send_keyboard(report_keyboard_t *report) { keys_send(REPORT_ID_KEYBOARD-1, KEYBOARD_REPORT_SIZE, report->raw); }
void    send_mouse(report_mouse_t *report) { keys_send(REPORT_ID_MOUSE-1, sizeof(report_mouse_t), (uint8_t *)report); }
void    send_system(uint16_t data) { keys_send(REPORT_ID_SYSTEM-1, sizeof(uint16_t), (uint8_t *)&data); }
void    send_consumer(uint16_t data) { keys_send(REPORT_ID_CONSUMER-1, sizeof(uint16_t), (uint8_t *)&data); }


void trig_event_param(enum user_event event, uint8_t arg)
{
    //trig_event(event, (void*)(uint32_t)arg);
}
