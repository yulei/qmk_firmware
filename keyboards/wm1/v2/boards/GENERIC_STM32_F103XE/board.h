/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_GENERIC_STM32_F103XE
#define BOARD_NAME              "stm32 based wm1"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768U

#define STM32_HSECLK            8000000U
//#define STM32_HSE_BYPASS

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xE

/*
 * IO pins assignments.
 */

/*
 * MCU voltage
 */
#define STM32_VDD 300
/*
 * IO pins assignments.
 */
#define GPIOA_PIN0       0U
#define GPIOA_PIN1       1U
#define GPIOA_PIN2       2U
#define GPIOA_PIN3       3U
#define GPIOA_PIN4       4U
#define GPIOA_PIN5       5U
#define GPIOA_PIN6       6U
#define GPIOA_PIN7       7U
#define GPIOA_PIN8       8U
#define GPIOA_PIN9       9U
#define GPIOA_PIN10      10U
#define GPIOA_USB_DM     11U
#define GPIOA_USB_DP     12U
#define GPIOA_TMS        13U
#define GPIOA_TCK        14U
#define GPIOA_TDI        15U

#define GPIOB_PIN0       0U
#define GPIOB_PIN1       1U
#define GPIOB_PIN2       2U
#define GPIOB_TDO        3U
#define GPIOB_NTRST      4U
#define GPIOB_PIN5       5U
#define GPIOB_PIN6       6U
#define GPIOB_PIN7       7U
#define GPIOB_PIN8       8U
#define GPIOB_PIN9       9U
#define GPIOB_PIN10      10U
#define GPIOB_PIN11      11U
#define GPIOB_PIN12      12U
#define GPIOB_PIN13      13U
#define GPIOB_PIN14      14U
#define GPIOB_PIN15      15U

#define GPIOC_PIN0       0U
#define GPIOC_PIN1       1U
#define GPIOC_PIN2       2U
#define GPIOC_PIN3       3U
#define GPIOC_PIN4       4U
#define GPIOC_PIN5       5U
#define GPIOC_PIN6       6U
#define GPIOC_PIN7       7U
#define GPIOC_PIN8       8U
#define GPIOC_PIN9       9U
#define GPIOC_PIN10      10U
#define GPIOC_PIN11      11U
#define GPIOC_PIN12      12U
#define GPIOC_PIN13      13U
#define GPIOC_PIN14      14U
#define GPIOC_PIN15      15U

#define GPIOD_PIN0       0U
#define GPIOD_PIN1       1U
#define GPIOD_PIN2       2U
#define GPIOD_PIN3       3U
#define GPIOD_PIN4       4U
#define GPIOD_PIN5       5U
#define GPIOD_PIN6       6U
#define GPIOD_PIN7       7U
#define GPIOD_PIN8       8U
#define GPIOD_PIN9       9U
#define GPIOD_PIN10      10U
#define GPIOD_PIN11      11U
#define GPIOD_PIN12      12U
#define GPIOD_PIN13      13U
#define GPIOD_PIN14      14U
#define GPIOD_PIN15      15U

#define GPIOE_PIN0       0U
#define GPIOE_PIN1       1U
#define GPIOE_PIN2       2U
#define GPIOE_PIN3       3U
#define GPIOE_PIN4       4U
#define GPIOE_PIN5       5U
#define GPIOE_PIN6       6U
#define GPIOE_PIN7       7U
#define GPIOE_PIN8       8U
#define GPIOE_PIN9       9U
#define GPIOE_PIN10      10U
#define GPIOE_PIN11      11U
#define GPIOE_PIN12      12U
#define GPIOE_PIN13      13U
#define GPIOE_PIN14      14U
#define GPIOE_PIN15      15U

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */
/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define CRL_INPUT(n)             (0U << ((n) * 4U))
#define CRL_OUTPUT_LOW(n)        (1U << ((n) * 4U))
#define CRL_OUTPUT_MEDIUM(n)     (2U << ((n) * 4U))
#define CRL_OUTPUT_HIGH(n)       (3U << ((n) * 4U))
#define CRL_INPUT_ANOLOG(n)      (0U << (((n) * 4U + 2)))
#define CRL_INPUT_FLOATING(n)    (1U << (((n) * 4U + 2)))
#define CRL_INPUT_PULLUPDOWN(n)  (2U << (((n) * 4U + 2)))
#define CRL_OUTPUT_PUSHPULL(n)   (0U << (((n) * 4U + 2)))
#define CRL_OUTPUT_OPENDRAIN(n)  (1U << (((n) * 4U + 2)))
#define CRL_ALT_PUSHPULL(n)      (2U << (((n) * 4U + 2)))
#define CRL_ALT_OPENDRAIN(n)     (3U << (((n) * 4U + 2)))

#define CRH_INPUT(n)             CRL_INPUT((n-8))
#define CRH_OUTPUT_LOW(n)        CRL_OUTPUT_LOW((n-8))
#define CRH_OUTPUT_MEDIUM(n)     CRL_OUTPUT_MEDIUM((n-8))
#define CRH_OUTPUT_HIGH(n)       CRL_OUTPUT_HIGH((n-8))
#define CRH_INPUT_ANOLOG(n)      CRL_INPUT_ANOLOG((n-8))
#define CRH_INPUT_FLOATING(n)    CRL_INPUT_FLOATING((n-8))
#define CRH_INPUT_PULLUPDOWN(n)  CRL_INPUT_PULLUPDOWN((n-8))
#define CRH_OUTPUT_PUSHPULL(n)   CRL_OUTPUT_PUSHPULL((n-8))
#define CRH_OUTPUT_OPENDRAIN(n)  CRL_OUTPUT_OPENDRAIN((n-8))
#define CRH_ALT_PUSHPULL(n)      CRL_ALT_PUSHPULL((n-8))
#define CRH_ALT_OPENDRAIN(n)     CRL_ALT_OPENDRAIN((n-8))

#define ODR_INPUT_PULLDOWN(n)     (0U << (n))
#define ODR_INPUT_PULLUP(n)       (1U << (n))

/*
 * Port A setup.
 * Everything input with pull-down except:
 * PA11 - Alternate output          (USB_DM).
 * PA12 - Alternate output          (USB_DP).
 * PA13 - Pull-up input             (TMS)
 * PA14 - Pull-down input           (TCK)
 * PA15 - Pull-up input             (TDI)
 */
/* PA7...PA0 */
#define VAL_GPIOACRL            0x88888888
/* PA15...PA8 */
#define VAL_GPIOACRH            (CRH_OUTPUT_HIGH(11)|CRH_ALT_PUSHPULL(11) \
                                | CRH_OUTPUT_HIGH(12)|CRH_ALT_PUSHPULL(12) \
                                | CRH_INPUT(13) | CRH_INPUT_PULLUPDOWN(13) \
                                | CRH_INPUT(14) | CRH_INPUT_PULLUPDOWN(13) \
                                | CRH_INPUT(15) | CRH_INPUT_PULLUPDOWN(13))

#define VAL_GPIOAODR            (ODR_INPUT_PULLUP(13)|ODR_INPUT_PULLDOWN(14)|ODR_INPUT_PULLUP(15))

/*
 * Port B setup.
 * Everything input with pull-down except:
 * PB3  - Pull-up input             (TDO).
 */
/* PB7...PB0 */
#define VAL_GPIOBCRL            (CRL_INPUT(3)|CRL_INPUT_PULLUPDOWN(3))
/* PB15...PB8 */
#define VAL_GPIOBCRH            0x88888888
#define VAL_GPIOBODR            (ODR_INPUT_PULLUP(3))

/*
 * Port C setup.
 * Everything input with pull-down except:
 */
/*  PC7...PC0 */
#define VAL_GPIOCCRL            0x88888888
/* PC15...PC8 */
#define VAL_GPIOCCRH            0x88888888

#define VAL_GPIOCODR            0x00000000

/*
 * Port D setup.
 * Everything input with pull-down except:
 */
/*  PD7...PD0 */
#define VAL_GPIODCRL            0x88888888
/* PD15...PD8 */
#define VAL_GPIODCRH            0x88888888

#define VAL_GPIODODR            0x00000000

/*
 * Port E setup.
 * Everything input with pull-down except:
 */
/*  PE7...PE0 */
#define VAL_GPIOECRL            0x88888888
/* PE15...PE8 */
#define VAL_GPIOECRH            0x88888888

#define VAL_GPIOEODR            0x00000000

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
