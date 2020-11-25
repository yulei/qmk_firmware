/**
 * rgb_effects.c
 * rgb effects implementation
 */

#include <stdlib.h>
#include "rgb_effects.h"
#include "timer.h"
#include "eeconfig.h"
#include "eeprom.h"

//#define EECONFIG_EFFECTS (uint32_t *)64

#define DELAY_MIN   0
#define DELAY_DEFAULT 1500

#define SPEED_MIN 0
#define SPEED_MAX 15
#define SPEED_DEFAULT 7

#define HUE_MIN 0
#define HUE_MAX 255
#define HUE_DEFAULT HUE_MIN
#define HUE_STEP 8

#define SAT_MIN 0
#define SAT_MAX 255
#define SAT_DEFAULT SAT_MAX
#define SAT_STEP 8

#define VAL_MIN 0
#define VAL_MAX 255
#define VAL_DEFAULT VAL_MAX
#define VAL_STEP 8

#define GRADIENT_STEP_DEFAULT   32
#define BREATH_STEP_DEFAULT     32

enum rgb_effects_type {
    RGB_EFFECT_STATIC,
    RGB_EFFECT_BLINK,
    RGB_EFFECT_GRADIENT,
    RGB_EFFECT_RANDOM,
    RGB_EFFECT_BREATH,
    RGB_EFFECT_WIPE,
    RGB_EFFECT_SCAN,
    RGB_EFFECT_MAX
};

typedef void (*RGB_EFFECT_FUN)(void);

typedef union {
    uint32_t raw;
    struct __attribute__((__packed__)) {
        uint8_t enable : 1;
        uint8_t mode : 3;
        uint8_t speed : 4;
        uint8_t hue;
        uint8_t sat;
        uint8_t val;
    };
} keyboard_config_t;

typedef struct {
    uint32_t        last_ticks;
    uint32_t        counter;
    uint32_t        gradient_step;
    uint32_t        breath_step;
    bool            wipe_on;
    RGB_EFFECT_FUN  effects[RGB_EFFECT_MAX];
} rgb_effects_state_t;

static keyboard_config_t effects_config;
static rgb_effects_state_t effects_state;

// utilities
#define RANDOM_DISTANCE 17
static uint8_t get_random_hue(uint8_t hue) { return (rand() % HUE_MAX) + RANDOM_DISTANCE; }

extern void effects_set_color(uint8_t index, uint8_t hue, uint8_t sat, uint8_t val);
extern void effects_set_color_all(uint8_t hue, uint8_t sat, uint8_t val);

static void effects_mode_init(void)
{
    switch(effects_config.mode) {
        case RGB_EFFECT_STATIC:
            break;
        case RGB_EFFECT_BLINK:
            break;
        case RGB_EFFECT_GRADIENT:
            break;
        case RGB_EFFECT_RANDOM:
            break;
        case RGB_EFFECT_BREATH:
            break;
        case RGB_EFFECT_WIPE:
            effects_state.wipe_on = true;
            effects_state.counter = 0;
            effects_set_color_all(0, 0, 0);
            break;
        case RGB_EFFECT_SCAN:
            effects_state.counter = 0;
            effects_set_color_all(0, 0, 0);
            break;
        default:
            break;
    }
}

static uint32_t effects_mode_delay(void)
{
    switch(effects_config.mode) {
        case RGB_EFFECT_STATIC:
            return DELAY_MIN;
        case RGB_EFFECT_BLINK:
            break;
        case RGB_EFFECT_GRADIENT:
            return DELAY_MIN;
        case RGB_EFFECT_RANDOM:
            break;
        case RGB_EFFECT_BREATH:
            break;
        default:
            break;
    }

    return DELAY_DEFAULT;
}

static bool effects_need_update(void) { return timer_elapsed(effects_state.last_ticks)*effects_config.speed >= effects_mode_delay(); }
static void effects_update_timer(void) { effects_state.last_ticks = timer_read(); }

//effects
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
    uint8_t hue = effects_config.hue;
    for (int i = 0; i < EFFECTS_LED_NUM; i++) {
        hue = get_random_hue(hue);
        effects_set_color(i, hue, effects_config.sat, effects_config.val);
    }
}

static void effects_mode_gradient(void)
{
    uint8_t step = HUE_MAX / EFFECTS_LED_NUM;//effects_state.gradient_step;

    for (int i = 0; i < EFFECTS_LED_NUM; i++) {
        effects_set_color(i, effects_config.hue + i*step, effects_config.sat, effects_config.val);
    }
    //effects_config.hue += step;
}

static void effects_mode_breath(void)
{
    uint8_t breath = VAL_MAX / effects_state.breath_step;

    effects_set_color_all(effects_config.hue, effects_config.sat, effects_config.val);
    effects_config.val += breath;
}

static void effects_mode_wipe(void)
{
    if (effects_state.counter >= EFFECTS_LED_NUM) {
        effects_state.counter = 0;
        effects_state.wipe_on = !effects_state.wipe_on;
    }

    if (effects_state.wipe_on) {
        effects_set_color(effects_state.counter, effects_config.hue, effects_config.sat, effects_config.val);
    } else {
        effects_set_color(effects_state.counter, 0, 0, 0);
    }
    effects_state.counter++;
}

static void effects_mode_scan(void)
{
    uint8_t prev = (effects_state.counter == 0) ? EFFECTS_LED_NUM - 1 : effects_state.counter - 1;
    effects_set_color(prev, 0, 0, 0);
    effects_set_color(effects_state.counter, effects_config.hue, effects_config.sat, effects_config.val);
    effects_state.counter = (effects_state.counter + 1) % EFFECTS_LED_NUM;
}

static void effects_set_hue(uint8_t hue)
{
    effects_config.hue = hue;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_sat(uint8_t sat)
{
    effects_config.sat = sat;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_val(uint8_t val)
{
    effects_config.val = val;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_speed(uint8_t speed)
{
    effects_config.speed = !speed ? 1 : speed;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_mode(uint8_t mode)
{
    effects_config.mode = mode;
    effects_mode_init();
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_set_enable(uint8_t enable)
{
    effects_config.enable = enable;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

static void effects_update_default(void)
{
    effects_config.enable = 1;
    effects_config.mode = RGB_EFFECT_GRADIENT;
    effects_config.speed = SPEED_DEFAULT;
    effects_config.hue = HUE_DEFAULT;
    effects_config.sat = SAT_DEFAULT;
    effects_config.val = VAL_DEFAULT;
    //eeprom_update_dword(EECONFIG_EFFECTS, effects_config.raw);
    eeconfig_update_kb(effects_config.raw);
}

void eeconfig_init_kb(void)
{
    effects_update_default();
    eeconfig_init_user();
}

// interface
void rgb_effects_init(void)
{
    //effects_update_default();
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    } else {
        //effects_config.raw = eeprom_read_dword(EECONFIG_EFFECTS);
        effects_config.raw = eeconfig_read_kb();
    }

    effects_state.counter       = 0;
    effects_state.wipe_on       = true;
    effects_state.gradient_step = GRADIENT_STEP_DEFAULT;
    effects_state.breath_step   = BREATH_STEP_DEFAULT;
    effects_state.last_ticks    = timer_read();
    srand(effects_state.last_ticks);
    effects_state.effects[RGB_EFFECT_STATIC]    = effects_mode_static;
    effects_state.effects[RGB_EFFECT_BLINK]     = effects_mode_blink;
    effects_state.effects[RGB_EFFECT_GRADIENT]  = effects_mode_gradient;
    effects_state.effects[RGB_EFFECT_RANDOM]    = effects_mode_random;
    effects_state.effects[RGB_EFFECT_BREATH]    = effects_mode_breath;
    effects_state.effects[RGB_EFFECT_WIPE]      = effects_mode_wipe;
    effects_state.effects[RGB_EFFECT_SCAN]      = effects_mode_scan;
    effects_mode_init();
}

void rgb_effects_inc_hue(void)
{
    effects_set_hue(effects_config.hue + HUE_STEP);
}

void rgb_effects_dec_hue(void)
{
    effects_set_hue(effects_config.hue - HUE_STEP);
}

void rgb_effects_inc_sat(void)
{
    effects_set_sat(effects_config.sat + SAT_STEP);
}

void rgb_effects_dec_sat(void)
{
    effects_set_sat(effects_config.sat - SAT_STEP);
}

void rgb_effects_inc_val(void)
{
    effects_set_val(effects_config.val + VAL_STEP);
}

void rgb_effects_dec_val(void)
{
    effects_set_val(effects_config.val - VAL_STEP);
}

void rgb_effects_inc_speed(void)
{
    effects_set_speed(++effects_config.speed);
}

void rgb_effects_dec_speed(void)
{
    effects_set_speed(--effects_config.speed);
}

void rgb_effects_inc_mode(void)
{
    effects_config.mode++;
    if (effects_config.mode >= RGB_EFFECT_MAX) {
        effects_config.mode = RGB_EFFECT_STATIC;
    }
    effects_set_mode(effects_config.mode);
}

void rgb_effects_dec_mode(void)
{
    if (effects_config.mode == 0) {
        effects_config.mode = RGB_EFFECT_MAX - 1;
    } else {
        effects_config.mode--;
    }

    effects_set_mode(effects_config.mode);
}

void rgb_effects_toggle(void)
{
    effects_config.enable = !effects_config.enable;
    effects_set_enable(effects_config.enable);
}

void rgb_effects_task(void)
{
    if (!effects_config.enable) {
        effects_set_color_all(0, 0, 0);
    } else {
        if (effects_need_update() ) {
            effects_state.effects[effects_config.mode]();
            effects_update_timer();
        }
    }
}
