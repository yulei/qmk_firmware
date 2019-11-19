/**
 * pad.cpp
 */

#include <hal.h>
#include "Usb.h"
#include "usbhub.h"
#include "usbhid.h"
#include "hidboot.h"
#include "parser.h"
#include "pad.h"

extern "C" {
#include "quantum.h"
#include "wait.h"
}

// Integrated key state of all keyboards
static report_keyboard_t              local_keyboard_report;

USB                                   usb_host;
USBHub hub1(&usb_host);
USBHub hub2(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd1(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd2(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd3(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd4(&usb_host);
KBDReportParser kbd_parser1;
KBDReportParser kbd_parser2;
KBDReportParser kbd_parser3;
KBDReportParser kbd_parser4;

static void or_report(report_keyboard_t report)
{
    // integrate reports into local_keyboard_report
    local_keyboard_report.mods |= report.mods;
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(report.keys[i])) {
            for (uint8_t j = 0; j < KEYBOARD_REPORT_KEYS; j++) {
                if (! local_keyboard_report.keys[j]) {
                    local_keyboard_report.keys[j] = report.keys[i];
                    break;
                }
            }
        }
    }
}

#define SPIDEV SPID1
#define SPI_CS_PORT GPIOA
#define SPI_CS_PIN  4
// APB run at 48MHz, need divided with 8 to 12MHz
// CPOL=0, CPHA=0
SPIConfig spicfg = {
    NULL,
    SPI_CS_PORT,
    SPI_CS_PIN,
    SPI_CR1_MSTR | SPI_CR1_BR_1,
    0};

static void pad_spi_init(void)
{
    palSetLineMode(LINE_U2U_RST, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_U2U_RST);
    palSetLineMode(LINE_U2U_IRQ, PAL_MODE_INPUT);
    palSetLineMode(LINE_U2U_CS, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_U2U_CS);
    palSetLineMode(LINE_U2U_SCK, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(LINE_U2U_MISO, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(LINE_U2U_MOSI, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);
    wait_ms(1);
    spiStart(&SPIDEV, &spicfg);
}

void pad_init(void)
{
    pad_spi_init();

    usb_host.Init();
    kbd1.SetReportParser(0, (HIDReportParser*)&kbd_parser1);
    kbd2.SetReportParser(0, (HIDReportParser*)&kbd_parser2);
    kbd3.SetReportParser(0, (HIDReportParser*)&kbd_parser3);
    kbd4.SetReportParser(0, (HIDReportParser*)&kbd_parser4);
}

void pad_scan(void)
{
    static uint16_t last_time_stamp1 = 0;
    static uint16_t last_time_stamp2 = 0;
    static uint16_t last_time_stamp3 = 0;
    static uint16_t last_time_stamp4 = 0;

    // check report came from keyboards
    if (kbd_parser1.time_stamp != last_time_stamp1 ||
        kbd_parser2.time_stamp != last_time_stamp2 ||
        kbd_parser3.time_stamp != last_time_stamp3 ||
        kbd_parser4.time_stamp != last_time_stamp4) {

        last_time_stamp1 = kbd_parser1.time_stamp;
        last_time_stamp2 = kbd_parser2.time_stamp;
        last_time_stamp3 = kbd_parser3.time_stamp;
        last_time_stamp4 = kbd_parser4.time_stamp;

        // clear and integrate all reports
        local_keyboard_report = {};
        or_report(kbd_parser1.report);
        or_report(kbd_parser2.report);
        or_report(kbd_parser3.report);
        or_report(kbd_parser4.report);

        host_keyboard_send(&local_keyboard_report);

        dprintf("state:  %02X %02X", local_keyboard_report.mods, local_keyboard_report.reserved);
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            dprintf(" %02X", local_keyboard_report.keys[i]);
        }
        dprint("\r\n");
    }

    uint16_t timer;
    timer = timer_read();
    usb_host.Task();
    timer = timer_elapsed(timer);
    if (timer > 100) {
        dprintf("host.Task: %d\n", timer);
    }

    static uint8_t usb_state = 0;
    if (usb_state != usb_host.getUsbTaskState()) {
        usb_state = usb_host.getUsbTaskState();
        dprintf("usb_state: %02X\n", usb_state);

        // restore LED state when keyboard comes up
        if (usb_state == USB_STATE_RUNNING) {
            dprintf("speed: %s\n", usb_host.getVbusState()==FSHOST ? "full" : "low");
            keyboard_set_leds(host_keyboard_leds());
        }
    }
}

void led_set(uint8_t usb_led)
{
#ifdef NOAH_U2U
    kbd1.SetReport(0, 0, 2, 0, 1, &usb_led);
    kbd2.SetReport(0, 0, 2, 0, 1, &usb_led);
    kbd3.SetReport(0, 0, 2, 0, 1, &usb_led);
    kbd4.SetReport(0, 0, 2, 0, 1, &usb_led);
#endif
    led_set_kb(usb_led);
}
