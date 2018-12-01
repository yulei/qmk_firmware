/**
 * rgb_backlight.c
 */
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "rgb_matrix.h"
#include "rgb_backlight.h"
#include "ws2811.h"
#include "wait.h"


// 74HC595 control
#define LINE_SER    PAL_LINE(GPIOA, 0U)
#define LINE_OE     PAL_LINE(GPIOA, 1U)
#define LINE_OCLK   PAL_LINE(GPIOA, 2U)
#define LINE_SCLK   PAL_LINE(GPIOA, 3U)

// column iteration period was 1 ms
#define REFRESH_INTERVAL 1

static rgb_config rgb_conf;
static virtual_timer_t vt;
/*
static const uint8_t rgb_led_matrix[][8][2] =
{
    {{0,0},   {0,1},    {1,0},    {2,0},    {3,0},    {4,0},        {4,1},    {4,2}},
    {{0,2},   {0,3},    {1,1},    {1,2},    {2,1},    {2,2},        {3,1},    {3,2}},
    {{0,4},   {0,5},    {1,3},    {1,4},    {2,3},    {2,4},        {3,3},    {3,4}},
    {{0,6},   {1,5},    {1,6},    {2,5},    {2,6},    {3,5},        {3,6},    {4,5}},
    {{0,7},   {0,8},    {1,7},    {1,8},    {2,7},    {2,8},        {3,7},    {3,8}},
    {{0,9},   {0,10},   {1,9},    {1,10},   {2,9},    {2,10},       {3,9},    {4,6}},
    {{0,11},  {0,12},   {1,11},   {1,12},   {2,11},   {3,10},       {3,11},   {4,7}},
    {{0,13},  {0,14},   {1,13},   {2,12},   {3,12},   {0xFF,0xFF},  {4,9},    {4,8}}
};
*/
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0|(0<<4)},    {  0,  0}, 1},
    {{0|(1<<4)},    { 17,  0}, 0},
    {{1|(0<<4)},    {  0, 16}, 1},
    {{2|(0<<4)},    {  0, 32}, 1},
    {{3|(0<<4)},    {  0, 48}, 1},
    {{4|(0<<4)},    {  0, 64}, 1},
    {{4|(1<<4)},    { 17, 64}, 1},
    {{4|(2<<4)},    { 34, 64}, 1},

    {{0|(2<<4)},    { 34,  0}, 0},
    {{0|(3<<4)},    { 51,  0}, 0},
    {{1|(1<<4)},    { 17, 16}, 0},
    {{1|(2<<4)},    { 34, 16}, 0},
    {{2|(1<<4)},    { 17, 32}, 0},
    {{2|(2<<4)},    { 34, 32}, 0},
    {{3|(1<<4)},    { 17, 48}, 0},
    {{3|(2<<4)},    { 34, 48}, 0},

    {{0|(4<<4)},    { 68,  0}, 0},
    {{0|(5<<4)},    { 85,  0}, 0},
    {{1|(3<<4)},    { 51, 16}, 0},
    {{1|(4<<4)},    { 68, 16}, 0},
    {{2|(3<<4)},    { 51, 32}, 0},
    {{2|(4<<4)},    { 68, 32}, 0},
    {{3|(3<<4)},    { 51, 48}, 0},
    {{3|(4<<4)},    { 68, 48}, 0},

    {{0|(6<<4)},    {102,  0}, 0},
    {{1|(5<<4)},    { 85, 16}, 0},
    {{1|(6<<4)},    {102, 16}, 0},
    {{2|(5<<4)},    { 85, 32}, 0},
    {{2|(6<<4)},    {102, 32}, 0},
    {{3|(5<<4)},    { 85, 48}, 0},
    {{3|(6<<4)},    {102, 48}, 0},
    {{4|(5<<4)},    {102, 64}, 0},

    {{0|(7<<4)},    {119,  0}, 0},
    {{0|(8<<4)},    {136,  0}, 0},
    {{1|(7<<4)},    {119, 16}, 0},
    {{1|(8<<4)},    {136, 16}, 0},
    {{2|(7<<4)},    {119, 32}, 0},
    {{2|(8<<4)},    {136, 32}, 0},
    {{3|(7<<4)},    {119, 48}, 0},
    {{3|(8<<4)},    {136, 48}, 0},

    {{0|(9<<4)},    {153,  0}, 0},
    {{0|(10<<4)},   {170,  0}, 0},
    {{1|(9<<4)},    {153, 16}, 0},
    {{1|(10<<4)},   {170, 16}, 0},
    {{2|(9<<4)},    {153, 32}, 0},
    {{2|(10<<4)},   {170, 32}, 0},
    {{3|(9<<4)},    {153, 48}, 0},
    {{4|(6<<4)},    {102, 48}, 1},

    {{0|(11<<4)},   {187,  0}, 0},
    {{0|(12<<4)},   {204,  0}, 0},
    {{1|(11<<4)},   {187, 16}, 0},
    {{1|(12<<4)},   {204, 16}, 0},
    {{2|(11<<4)},   {187, 32}, 0},
    {{3|(10<<4)},   {170, 48}, 0},
    {{3|(11<<4)},   {187, 48}, 1},
    {{4|(7<<4)},    {153, 48}, 1},

    {{0|(13<<4)},   {221,  0}, 0},
    {{0|(14<<4)},   {221,  0}, 0},
    {{1|(13<<4)},   {221, 32}, 1},
    {{2|(12<<4)},   {221, 16}, 1},
    {{3|(12<<4)},   {221, 48}, 1},
    {{4|(10<<4)},   {221, 64}, 1},
    {{4|(9<<4)},    {221, 64}, 1},
    {{4|(8<<4)},    {204, 64}, 1},
};

static color rgb_color_matrix[5][14];

static void col_write(uint8_t d);
static void col_clear(void);
static void col_init(void);
static void col_update(void *param);
static void col_start(void);
static void col_next(void);
static void col_stop(void);
static void col_render(uint8_t col);

void col_write(uint8_t d)
{
  palClearLine(LINE_OCLK);
  palClearLine(LINE_SCLK);
  for (uint8_t i = 0; i < 8; i++) {
    if (d&0x80) {
      palSetLine(LINE_SER);
    } else {
      palClearLine(LINE_SER);
    }
    wait_us(10);
    palSetLine(LINE_SCLK);
    wait_us(10);
    palClearLine(LINE_SCLK);
    d <<= 1;
  }
  palSetLine(LINE_OCLK);
  wait_us(10);
  palClearLine(LINE_OCLK);
}

void col_clear(void)
{
  col_write(0xFF);
  //col_write(0);
}

void col_init(void)
{
    palSetLineMode(LINE_SER, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OCLK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_SCLK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_OE);
    col_clear();
    palClearLine(LINE_OE);
    ws2811_transfer();
}

void col_update(void *param)
{
  (void)param;
  chSysLockFromISR();
  col_next();
  if (rgb_conf.on) {
      chVTSetI(&vt, MS2ST(REFRESH_INTERVAL), col_update, NULL);
  }
  chSysUnlockFromISR();
}

void col_start(void)
{
    col_clear();
    rgb_conf.cur_col = 0;
    rgb_conf.on = true;
    // start iteration timer
    chVTSet(&vt, MS2ST(REFRESH_INTERVAL), col_update, NULL);
}

void col_next(void)
{
    palClearLine(LINE_SCLK);
    palClearLine(LINE_OCLK);

    if( rgb_conf.cur_col == 0) {
        palClearLine(LINE_SER);
    } else {
        palSetLine(LINE_SER);
    }

    // shift 74hc595
    wait_us(10);
    palSetLine(LINE_SCLK);
    wait_us(10);
    palClearLine(LINE_SCLK);
    palSetLine(LINE_OCLK);
    wait_us(10);
    palClearLine(LINE_OCLK);

    col_render(rgb_conf.cur_col);
    rgb_conf.cur_col = (rgb_conf.cur_col + 1) % 8;
}

void col_render(uint8_t col)
{
    for(uint8_t i = 0; i < 8; i++) {
      uint32_t x = g_rgb_leds[col * 8 + i].matrix_co.row;
      uint32_t y = g_rgb_leds[col * 8 + i].matrix_co.col;
      ws2811_write_led(i, rgb_color_matrix[x][y].r, rgb_color_matrix[x][y].g, rgb_color_matrix[x][y].b);
    }
    ws2811_transfer();
}

void col_stop(void)
{
    rgb_conf.cur_col = 0;
    rgb_conf.on = false;
    col_clear();
}

void rb_init(void)
{
    ws2811_init();
    col_init();
    rb_set_color_all(255, 0, 0);
}

void rb_set_state(bool on)
{
  rgb_conf.on = on;
  if (on) {
    col_start();
  } else {
    col_stop();
  }
}

void rb_flush(void)
{
}

void rb_set_color(int index, uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t row = g_rgb_leds[index].matrix_co.row;
  uint32_t col = g_rgb_leds[index].matrix_co.col;
  rgb_color_matrix[col][row].r = r;
  rgb_color_matrix[col][row].g = g;
  rgb_color_matrix[col][row].b = b;
}

void rb_set_color_all(uint8_t r, uint8_t g, uint8_t b)
{
  for (uint32_t i = 0; i < 5; i++) {
    for (uint32_t j = 0; j < 14; j++) {
      rgb_color_matrix[i][j].r = r;
      rgb_color_matrix[i][j].g = g;
      rgb_color_matrix[i][j].b = b;
    }
  }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = rb_init,
    .flush = rb_flush,
    .set_color = rb_set_color,
    .set_color_all = rb_set_color_all,
};
