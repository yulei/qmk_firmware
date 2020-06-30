/**
 * rgb_effects.c
 * rgb effects implementation
 */

#include <stdlib.h>
#include "rgb_effects.h"
#include "timer.h"
#include "eeconfig.h"

#define SPEED_MIN 0
#define SPEED_MAX 15
#define SPEED_DEFAULT 7

#define HUE_MIN 0
#define HUE_MAX 255
#define HUE_DEFAULT HUE_MAX
#define HUE_SETP 8

#define SAT_MIN 0
#define SAT_MAX 255
#define SAT_DEFAULT SAT_MIN
#define SAT_SETP 8

#define VAL_MIN 0
#define VAL_MAX 255
#define VAL_DEFAULT VAL_MAX
#define VAL_SETP 8

#define GRADIENT_STEP_DEFAULT   32
#define BREATH_STEP_DEFAULT     32

enum rgb_effects_type {
    RGB_EFFECT_OFF,
    RGB_EFFECT_STATIC,
    RGB_EFFECT_BLINK,
    RGB_EFFECT_GRADIENT,
    RGB_EFFECT_RANDOM,
    RGB_EFFECT_BREATH,
    RGB_EFFECT_MAX
};

typedef void (*RGB_EFFECT_FUN)(void);


typedef union {
    uint32_t raw;
    struct {
        uint8_t mode:4;
        uint8_t speed:4;
        uint8_t hue;
        uint8_t sat;
        uint8_t val;
    }__attribute__((packed));
} keyboard_config_t;

typedef struct {
    uint32_t last_ticks;
    uint32_t counter;
    uint32_t gradient_step;
    uint32_t breath_step;
    RGB_EFFECT_FUN effects[RGB_EFFECT_MAX];
} rgb_effects_state_t;

static keyboard_config_t effects_config;
static rgb_effects_state_t effects_state;

// utilities
static uint8_t get_random_hue(uint8_t hue)
{
  uint8_t r = 0;
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t d = 0;

  while(d < 42) {
    r = rand() % 360;
    x = hue > r ? hue - r : r - hue;
    y = 360 - x;
    d = x > y ? y : x;
  }

  return r;
}

extern void effects_set_color(uint8_t index, uint8_t hue, uint8_t sat, uint8_t val);
extern void effects_set_color_all(uint8_t hue, uint8_t sat, uint8_t val);

//effects
static void effects_mode_off(void)
{
    effects_set_color_all(0, 0, 0);
}

static void effects_mode_static(void)
{
    effects_set_color_all(effects_config.hue, effects_config.sat, effects_config.val);
}

static void effects_mode_blink(void)
{
    if(effects_state.counter % 2 == 1) {
        // on
        effects_set_color_all(effects_config.hue, effects_config.sat, effects_config.val);
    }
    else {
        // off
        effects_set_color_all(0, 0, 0);
    }
    effects_state.counter++;
}

static void effects_mode_random(void)
{
    for (int i = 0; i < EFFECTS_LED_NUM; i++) {
        effects_config.hue = get_random_hue(effects_config.hue);
        effects_set_color_all(effects_config.hue, effects_config.sat, effects_config.val);
    }
}

static void effects_mode_gradient(void)
{
    uint8_t step = HUE_MAX / effects_state.gradient_step;

    for (int i = 0; i < EFFECTS_LED_NUM; i++) {
        effects_set_color(i, effects_config.hue + i*step, effects_config.sat, effects_config.val);
    }
}

static void effects_mode_breath(void)
{
    uint8_t breath = VAL_MAX / effects_state.breath_step;

    effects_set_color_all(effects_config.hue, effects_config.sat, effects_config.val);
    effects_config.val += breath;
}


static uint32_t effects_delay(void)
{
    return 50;
}

static void effects_set_hue(uint8_t hue)
{
    effects_config.hue = hue;
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_sat(uint8_t sat)
{
    effects_config.sat = sat;
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_val(uint8_t val)
{
    effects_config.val = val;
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_speed(uint8_t speed)
{
    effects_config.speed = speed;
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_mode(uint8_t mode)
{
    effects_config.mode = mode;
    eeconfig_update_kb(effects_config.raw);
}

// interface
void rgb_effects_init(void)
{
    //effects_config.raw = eeconfig_read_kb();
    effects_config.mode = RGB_EFFECT_STATIC;
    effects_config.speed = SPEED_DEFAULT;
    effects_config.hue = HUE_DEFAULT;
    effects_config.sat = SAT_DEFAULT;
    effects_config.val = VAL_DEFAULT;

    effects_state.counter = 0;
    effects_state.gradient_step = GRADIENT_STEP_DEFAULT;
    effects_state.breath_step = BREATH_STEP_DEFAULT;
    effects_state.last_ticks = timer_read32();
    srand(effects_state.last_ticks);
    effects_state.effects[RGB_EFFECT_OFF]       = effects_mode_off;
    effects_state.effects[RGB_EFFECT_STATIC]    = effects_mode_static;
    effects_state.effects[RGB_EFFECT_BLINK]     = effects_mode_blink;
    effects_state.effects[RGB_EFFECT_GRADIENT]  = effects_mode_gradient;
    effects_state.effects[RGB_EFFECT_RANDOM]    = effects_mode_random;
    effects_state.effects[RGB_EFFECT_BREATH]    = effects_mode_breath;
}

void rgb_effects_inc_hue(void)
{
    effects_set_hue(effects_config.hue + HUE_SETP);
}

void rgb_effects_dec_hue(void)
{
    effects_set_hue(effects_config.hue - HUE_SETP);
}

void rgb_effects_inc_sat(void)
{
    effects_set_sat(effects_config.sat + SAT_SETP);
}

void rgb_effects_dec_sat(void)
{
    effects_set_sat(effects_config.sat - SAT_SETP);
}

void rgb_effects_inc_val(void)
{
    effects_set_val(effects_config.val + VAL_SETP);
}

void rgb_effects_dec_val(void)
{
    effects_set_val(effects_config.val - VAL_SETP);
}

void rgb_effects_inc_speed(void)
{
    effects_set_speed(effects_config.speed++);
}

void rgb_effects_dec_speed(void)
{
    effects_set_speed(effects_config.speed--);
}

void rgb_effects_inc_mode(void)
{
    uint8_t mode = effects_config.mode++;
    if (mode >= RGB_EFFECT_MAX) {
        mode = RGB_EFFECT_STATIC;
    }
    effects_set_mode(mode == RGB_EFFECT_OFF? RGB_EFFECT_STATIC : mode);
}

void rgb_effects_dec_mode(void)
{
    uint8_t mode = effects_config.mode--;
    if (mode >= RGB_EFFECT_MAX) {
        mode = RGB_EFFECT_MAX-1;
    }
    effects_set_mode(mode == RGB_EFFECT_OFF? RGB_EFFECT_MAX-1 : mode);
}

void rgb_effects_toggle(void)
{
    if (effects_config.mode == RGB_EFFECT_OFF) {
        effects_set_mode(RGB_EFFECT_STATIC);
    } else {
        effects_set_mode(RGB_EFFECT_OFF);
    }
}

void rgb_effects_task(void)
{
    if (timer_elapsed32(effects_state.last_ticks) > effects_delay()) {
        effects_state.effects[effects_config.mode]();
        effects_state.last_ticks = timer_read32();
    }
}
