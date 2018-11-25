/**
 * rgb_backlight.c
 */
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "rgb_backlight.h"
#include "ws2811.h"
#include "wait.h"


// 74HC595 control
#define LINE_SER    PAL_LINE(GPIOA, 0U)
#define LINE_OE     PAL_LINE(GPIOA, 1U)
#define LINE_OCLK   PAL_LINE(GPIOA, 2U)
#define LINE_SCLK   PAL_LINE(GPIOA, 3U)

// column iteration period was 2 ms
#define REFRESH_INTERVAL 2

static rgb_config rgb_conf;
static virtual_timer_t vt;

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

static color rgb_color_matrix[5][14];

static void col_clear(void);
static void col_init(void);
static void col_update(void *param);
static void col_start(void);
static void col_next(void);
static void col_stop(void);
static void col_render(uint8_t col);

void col_clear(void)
{
    palClearLine(LINE_SER);
    palClearLine(LINE_OCLK);
    palClearLine(LINE_SCLK);
    wait_us(10);
    for (uint8_t i = 0; i < 8; i++) {
        palSetLine(LINE_SCLK);
        wait_us(10);
        palClearLine(LINE_SCLK);
    }
    palSetLine(LINE_OCLK);
    wait_us(10);
    palClearLine(LINE_OCLK);
}

void col_init(void)
{
    palSetLineMode(LINE_SER, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_OCLK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_SCLK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LINE_OE);

    col_clear();
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
    palClearLine(LINE_OE);
    rgb_conf.cur_col = 0;
    // start iteration timer
    chVTSet(&vt, MS2ST(REFRESH_INTERVAL), col_update, NULL);
}

void col_next(void)
{
    if( rgb_conf.cur_col == 0) {
        palSetLine(LINE_SER);
    } else {
        palClearLine(LINE_SER);
    }

    palClearLine(LINE_SCLK);
    wait_us(10);
    palSetLine(LINE_SCLK);
    palClearLine(LINE_OCLK);
    wait_us(10);
    palSetLine(LINE_OCLK);
    wait_us(10);
    palClearLine(LINE_SCLK);
    palClearLine(LINE_OCLK);
    col_render(rgb_conf.cur_col);
    rgb_conf.cur_col = (rgb_conf.cur_col + 1) % 8;
}

void col_render(uint8_t col)
{
    for(uint8_t i = 0; i < 8; i++) {
        uint32_t x = rgb_led_matrix[col][i][0];
        uint32_t y = rgb_led_matrix[col][i][1];
        ws2811_write_led(i, rgb_color_matrix[x][y].r, rgb_color_matrix[x][y].g, rgb_color_matrix[x][y].b);
    }
    ws2811_transfer();
}

void col_stop(void)
{
    col_clear();
    rgb_conf.cur_col = 0;
}

void rb_init(void)
{
    memset(&rgb_color_matrix[0][0], 0, sizeof(rgb_color_matrix));
    ws2811_init();
    col_init();
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

void rb_update(void)
{
    if( !rgb_conf.on)
        return;
}

