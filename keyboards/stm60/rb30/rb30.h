 /**
  * rb30.h
  *
  */
#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_default( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k21, k22, k23, k24, k25, k26, k27, k28, k29 \
) \
{ \
  {k01, k02, k03, k04, k05, k06, k07, k08, k09, KC_NO, k0a}, \
  {k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,   k0b}, \
  {k21, KC_NO, k22, k23, k24, k25, k26, k27, k28, k29, k1b}, \
}
