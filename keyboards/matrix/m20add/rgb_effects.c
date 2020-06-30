/**
 * rgb_effects.c
 * rgb effects implementation
 */

#include <stdlib.h>
#include "rgb_effects.h"
#include "timer.h"

#define SPEED_MIN 0
#define SPEED_MAX 255
#define SPEED_DEFAULT 150
#define DELAY_DEFAULT 100

#define HUE_MIN 0
#define HUE_MAX 255
#define HUE_DEFAULT HUE_MAX
#define SAT_MIN 0
#define SAT_MAX 255
#define SAT_DEFAULT SAT_MIN
#define VAL_MIN 0
#define VAL_MAX 255
#define VAL_DEFAULT VAL_MAX

enum rgb_effects_type {
    RGB_EFFECT_STATIC,
    RGB_EFFECT_BLINK,
    RGB_EFFECT_GRADIENT,
    RGB_EFFECT_RANDOM,
    RGB_EFFECT_BREATH,
    RGB_EFFECT_MAX
};

typedef void (*RGB_EFFECT_FUN)(void);

typedef struct {
    uint8_t  mode;
    uint32_t counter;
    uint8_t speed;
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
    uint32_t last_ticks;
    RGB_EFFECT_FUN effects[RGB_EFFECT_MAX];
} rgb_effects_state_t;

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
static void rgb_effects_mode_static(void) { effects_set_color_all(effects_state.hue, effects_state.sat, effects_state.val); }
static void rgb_effects_mode_blink(void)
{
    if(effects_state.counter % 2 == 1) {
        // on
        effects_set_color_all(effects_state.hue, effects_state.sat, effects_state.val);
    }
    else {
        // off
        effects_set_color_all(0, 0, 0);
    }
    effects_state.counter++;
}


static void rgb_effects_mode_random(void)
{
    effects_state.hue = get_random_hue(effects_state.hue);

    for (int i = 0; i < RGB_EFFECTS_LED_NUM; i++) {
        effects_set_color_all(effects_state.hue, effects_state.sat, effects_state.val);
    }
}

static void rgb_effects_mode_gradient(void)
{
    uint8_t step = HUE_MAX / RGB_EFFECTS_LED_NUM;

    for (int i = 0; i < RGB_EFFECTS_LED_NUM; i++) {
        effects_set_color(i, effects_state.hue + i*step, effects_state.sat, effects_state.val);
    }
}

static void rgb_effects_mode_breath(void)
{
    uint8_t breath = VAL_MAX / (RGB_EFFECTS_LED_NUM);

    effects_set_color_all(effects_state.hue, effects_state.sat, effects_state.val);
    effects_state.val += breath;
}


static uint32_t rgb_effects_delay(void)
{
    return 50;
}



// interface
void rgb_effects_init(void)
{
    effects_state.mode = RGB_EFFECT_STATIC;
    effects_state.counter = 0;
    effects_state.speed = SPEED_DEFAULT;
    effects_state.hue = HUE_DEFAULT;
    effects_state.sat = SAT_DEFAULT;
    effects_state.val = VAL_DEFAULT;
    effects_state.last_ticks = timer_read32();
    srand(effects_state.last_ticks);
    effects_state.effects[RGB_EFFECT_STATIC]    = rgb_effects_mode_static;
    effects_state.effects[RGB_EFFECT_BLINK]     = rgb_effects_mode_blink;
    effects_state.effects[RGB_EFFECT_GRADIENT]  = rgb_effects_mode_gradient;
    effects_state.effects[RGB_EFFECT_RANDOM]    = rgb_effects_mode_random;
    effects_state.effects[RGB_EFFECT_BREATH]    = rgb_effects_mode_breath;
}

void rgb_effects_set_hue(uint8_t hue) { effects_state.hue = hue; }
void rgb_effects_set_sat(uint8_t sat) { effects_state.sat = sat; }
void rgb_effects_set_val(uint8_t val) { effects_state.val = val; }
void rgb_effects_set_speed(uint8_t speed) { effects_state.speed = speed; }
void rgb_effects_step_mode(void) { effects_state.mode = (effects_state.mode + 1) % RGB_EFFECT_MAX; }

void rgb_effects_task(void)
{
    if (timer_elapsed32(effects_state.last_ticks) > rgb_effects_delay()) {
        effects_state.effects[effects_state.mode]();
        effects_state.last_ticks = timer_read32();
    }
}
