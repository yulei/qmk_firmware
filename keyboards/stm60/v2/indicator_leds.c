/**
 * led.c
 *
 */

#include "hal.h"
#include "quantum.h"
#include "indicator_leds.h"

void indicator_leds_init(void) {
  palSetLineMode(LINE_I_LED1, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED1);
  palSetLineMode(LINE_I_LED2, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED2);
  palSetLineMode(LINE_I_LED3, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED3);
  palSetLineMode(LINE_I_LED4, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED4);
  palSetLineMode(LINE_I_LED5, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED5);
  palSetLineMode(LINE_I_LED6, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED6);
  palSetLineMode(LINE_I_LED7, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED7);
  palSetLineMode(LINE_I_LED8, PAL_MODE_OUTPUT_PUSHPULL);
  palClearLine(LINE_I_LED8);
}

void indicator_leds_set(uint32_t index, bool on)
{
  switch(index) {
    case 0:
      on ? palSetLine(LINE_I_LED1) : palClearLine(LINE_I_LED1);
      break;
    case 1:
      on ? palSetLine(LINE_I_LED2) : palClearLine(LINE_I_LED2);
      break;
    case 2:
      on ? palSetLine(LINE_I_LED3) : palClearLine(LINE_I_LED3);
      break;
    case 3:
      on ? palSetLine(LINE_I_LED4) : palClearLine(LINE_I_LED4);
      break;
    case 4:
      on ? palSetLine(LINE_I_LED5) : palClearLine(LINE_I_LED5);
      break;
    case 5:
      on ? palSetLine(LINE_I_LED6) : palClearLine(LINE_I_LED6);
      break;
    case 6:
      on ? palSetLine(LINE_I_LED7) : palClearLine(LINE_I_LED7);
      break;
    case 7:
      on ? palSetLine(LINE_I_LED8) : palClearLine(LINE_I_LED8);
      break;
    default:
      break;
    }
}

void led_set_kb(uint8_t usb_led)
{
  // led 1
  indicator_leds_set(0, host_keyboard_leds() & (1 << USB_LED_NUM_LOCK));
  // led 2
  indicator_leds_set(1, host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK));
  // led 3
  indicator_leds_set(2, host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK));
  // led 4
  indicator_leds_set(3, layer_state & (1 << 0));
  // led 5
  indicator_leds_set(4, layer_state & (1 << 1));
  // led 6
  indicator_leds_set(5, layer_state & (1 << 2));
  // led 7
  indicator_leds_set(6, layer_state & (1 << 3));
  // led 8
  indicator_leds_set(7, layer_state & (1 << 4));
}
