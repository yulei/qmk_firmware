/**
 * @file nrfusb.h
 */

#pragma once
#include "quantum.h"

#define LAYOUT_60_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k48,  k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}
