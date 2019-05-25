 /**
  * rb40.h
  *
  */
#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_default( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, \
	k30, k31, k32,      k34,      k36,      k38, k39, k3a \
) \
{ \
	{k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a}, \
  {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a}, \
  {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a}, \
  {k30, k31, k32, KC_NO, k34, KC_NO, k36, k0b, k38, k39, k3a} \
}
