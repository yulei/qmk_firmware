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

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for STMicroelectronics STM32 Nucleo64-F411RE board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_NUCLEO64_F411RE
#define BOARD_NAME                  "STM32 KeyBoard"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

//#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F412Rx

/*
 * IO pins assignments.
 */
#define GPIOA_SER                   0U
#define GPIOA_OE                    1U
#define GPIOA_OCLK                  2U
#define GPIOA_SCLK                  3U
#define GPIOA_PIN4                  4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6                  6U
#define GPIOA_RGB_BL                7U
#define GPIOA_ILED_4                8U
#define GPIOA_COL2                  9U
#define GPIOA_COL3                  10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_TMS                   13U
#define GPIOA_TCK                   14U
#define GPIOA_TDI                   15U

#define GPIOB_COL7                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_TDO                   3U
#define GPIOB_nTRST                 4U
#define GPIOB_ROW1                  5U
#define GPIOB_ROW2                  6U
#define GPIOB_ROW3                  7U
#define GPIOB_ROW4                  8U
#define GPIOB_COL8                  9U
#define GPIOB_ILED_5                10U
#define GPIOB_ROW5                  12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_RGB_BTN               15U

#define GPIOC_COL11                 0U
#define GPIOC_COL12                 1U
#define GPIOC_COL13                 2U
#define GPIOC_COL14                 3U
#define GPIOC_COL5                  4U
#define GPIOC_COL6                  5U
#define GPIOC_COL1                  6U
#define GPIOC_ILED_1                7U
#define GPIOC_ILED_2                8U
#define GPIOC_ILED_3                9U
#define GPIOC_COL4                  10U
#define GPIOC_ILED_6                11U
#define GPIOC_ILED_7                12U
#define GPIOC_COL10                 13U
#define GPIOC_COL9                  14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_ILED_8                2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/**
 * io line definitons
 */
//#define LINE_RGB                    PAL_LINE(GPIOA, 7U)
//#define LINE_USB_PU                 PAL_LINE(GPIOA, 8U)

#define LINE_I_LED1                 PAL_LINE(GPIOB, GPIOC_ILED_1)
#define LINE_I_LED2                 PAL_LINE(GPIOB, GPIOC_ILED_2)
#define LINE_I_LED3                 PAL_LINE(GPIOC, GPIOC_ILED_3)
#define LINE_I_LED4                 PAL_LINE(GPIOC, GPIOA_ILED_4)
#define LINE_I_LED5                 PAL_LINE(GPIOB, GPIOB_ILED_5)
#define LINE_I_LED6                 PAL_LINE(GPIOC, GPIOC_ILED_6)
#define LINE_I_LED7                 PAL_LINE(GPIOC, GPIOC_ILED_7)
#define LINE_I_LED8                 PAL_LINE(GPIOD, GPIOD_ILED_8)

//#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
//#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)

#define LINE_COL_1                  PAL_LINE(GPIOC, GPIOC_COL1)
#define LINE_COL_2                  PAL_LINE(GPIOA, GPIOA_COL2)
#define LINE_COL_3                  PAL_LINE(GPIOA, GPIOA_COL3)
#define LINE_COL_4                  PAL_LINE(GPIOC, GPIOC_COL4)
#define LINE_COL_5                  PAL_LINE(GPIOC, GPIOC_COL5)
#define LINE_COL_6                  PAL_LINE(GPIOC, GPIOC_COL6)
#define LINE_COL_7                  PAL_LINE(GPIOB, GPIOB_COL7)
#define LINE_COL_8                  PAL_LINE(GPIOB, GPIOB_COL8)
#define LINE_COL_9                  PAL_LINE(GPIOC, GPIOC_COL9)
#define LINE_COL_10                 PAL_LINE(GPIOC, GPIOC_COL10)
#define LINE_COL_11                 PAL_LINE(GPIOC, GPIOC_COL11)
#define LINE_COL_12                 PAL_LINE(GPIOC, GPIOC_COL12)
#define LINE_COL_13                 PAL_LINE(GPIOC, GPIOC_COL13)
#define LINE_COL_14                 PAL_LINE(GPIOC, GPIOC_COL14)

#define LINE_ROW_1                  PAL_LINE(GPIOB, GPIOB_ROW1)
#define LINE_ROW_2                  PAL_LINE(GPIOB, GPIOB_ROW2)
#define LINE_ROW_3                  PAL_LINE(GPIOB, GPIOB_ROW3)
#define LINE_ROW_4                  PAL_LINE(GPIOB, GPIOB_ROW4)
#define LINE_ROW_5                  PAL_LINE(GPIOB, GPIOB_ROW5)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - 74HC595 SER               (output pushpull high)
 * PA1  - 74HC595 OE                (output pushpull low).
 * PA2  - 74HC595 output clock      (output pushpull low).
 * PA3  - 74HC595 shift clock       (output pushpull low).
 * PA4  - NC                        (input pullup).
 * PA5  - SPI1 SCK                  (alternate 5).
 * PA6  - NC                        (input pullup).
 * PA7  - SPI1 MOSI                 (alternate 5).
 * PA8  - LED 4                     (output pushpull low).
 * PA9  - KEY column 2              (output pushpull low).
 * PA10 - KEY column 3              (output pushpull low).
 * PA11 - USB_DM                    (alternate 10).
 * PA12 - USB_DP                    (alternate 10).
 * PA13 - JTAG TMS/SWDIO            (alternate 0).
 * PA14 - JTAG TCK/SWCLK            (alternate 0).
 * PA15 - JTAG TDI                  (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(GPIOA_SER) |         \
                                     PIN_MODE_OUTPUT(GPIOA_OE) |         \
                                     PIN_MODE_OUTPUT(GPIOA_OCLK) |     \
                                     PIN_MODE_OUTPUT(GPIOA_SCLK) |     \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN5) |     \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_RGB_BL) |        \
                                     PIN_MODE_OUTPUT(GPIOA_ILED_4) |         \
                                     PIN_MODE_OUTPUT(GPIOA_COL2) |         \
                                     PIN_MODE_OUTPUT(GPIOA_COL3) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DP) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_TMS) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_TCK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_TDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_SER) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OE) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OCLK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SCLK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RGB_BL) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ILED_4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_COL2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_COL3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TMS) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TCK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_SER) |        \
                                     PIN_OSPEED_HIGH(GPIOA_OE) |        \
                                     PIN_OSPEED_HIGH(GPIOA_OCLK) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SCLK) |      \
                                     PIN_OSPEED_HIGH(GPIOA_PIN4) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN5) |   \
                                     PIN_OSPEED_HIGH(GPIOA_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOA_RGB_BL) |       \
                                     PIN_OSPEED_LOW(GPIOA_ILED_4) |        \
                                     PIN_OSPEED_VERYLOW(GPIOA_COL2) |        \
                                     PIN_OSPEED_VERYLOW(GPIOA_COL3) |        \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DP) |     \
                                     PIN_OSPEED_HIGH(GPIOA_TMS) |         \
                                     PIN_OSPEED_HIGH(GPIOA_TCK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_TDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_SER) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_OE) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOA_OCLK) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SCLK) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN5) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN6) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_RGB_BL) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOA_ILED_4) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_COL2) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_COL3) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DP) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_TMS) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_TCK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_TDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_SER) |           \
                                     PIN_ODR_LOW(GPIOA_OE) |           \
                                     PIN_ODR_LOW(GPIOA_OCLK) |           \
                                     PIN_ODR_LOW(GPIOA_SCLK) |           \
                                     PIN_ODR_LOW(GPIOA_PIN4) |           \
                                     PIN_ODR_LOW(GPIOA_PIN5) |         \
                                     PIN_ODR_LOW(GPIOA_PIN6) |          \
                                     PIN_ODR_HIGH(GPIOA_RGB_BL) |          \
                                     PIN_ODR_LOW(GPIOA_ILED_4) |           \
                                     PIN_ODR_LOW(GPIOA_COL2) |           \
                                     PIN_ODR_LOW(GPIOA_COL3) |           \
                                     PIN_ODR_HIGH(GPIOA_USB_DM) |        \
                                     PIN_ODR_HIGH(GPIOA_USB_DP) |        \
                                     PIN_ODR_LOW(GPIOA_TMS) |            \
                                     PIN_ODR_LOW(GPIOA_TCK) |            \
                                     PIN_ODR_HIGH(GPIOA_TDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_SER, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_OE, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_OCLK, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_SCLK, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN4, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN5, 5U) |     \
                                     PIN_AFIO_AF(GPIOA_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_RGB_BL, 5U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_ILED_4, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_COL2, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_COL3, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_USB_DM, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_USB_DP, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_TMS, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_TCK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_TDI, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - KEY column 7              (output pushpull).
 * PB1  - PIN1                      (input pulldown).
 * PB2  - PIN2                      (input pulldown).
 * PB3  - JTAG TDO/SWO              (alternate 0).
 * PB4  - JTAG nTRST                (alternate 0).
 * PB5  - KEY row 1                 (input pulldown).
 * PB6  - KEY row 2                 (input pulldown).
 * PB7  - KEY row 3                 (input pulldown).
 * PB8  - KEY row 4                 (input pulldown).
 * PB9  - KEY column 8              (output pushpull).
 * PB10 - LED 5                     (output pushpull).
 * PB11 - KEY row 5                 (input pulldown).
 * PB13 - PIN13                     (alternate 5).
 * PB14 - PIN14                     (input pulldown).
 * PB15 - RGB button                (alternate 5).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_COL7) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_TDO) |        \
                                     PIN_MODE_INPUT(GPIOB_nTRST) |         \
                                     PIN_MODE_INPUT(GPIOB_ROW1) |         \
                                     PIN_MODE_INPUT(GPIOB_ROW2) |        \
                                     PIN_MODE_INPUT(GPIOB_ROW3) |           \
                                     PIN_MODE_INPUT(GPIOB_ROW4) |        \
                                     PIN_MODE_OUTPUT(GPIOB_COL8) |        \
                                     PIN_MODE_OUTPUT(GPIOB_ILED_5) |         \
                                     PIN_MODE_INPUT(GPIOB_ROW5) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_RGB_BTN))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_COL7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TDO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_nTRST) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ROW1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ROW2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ROW3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ROW4) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_COL8) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ILED_5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ROW5) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RGB_BTN))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOB_COL7) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_TDO) |           \
                                     PIN_OSPEED_HIGH(GPIOB_nTRST) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ROW1) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ROW2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_ROW3) |          \
                                     PIN_OSPEED_VERYLOW(GPIOB_ROW4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_COL8) |       \
                                     PIN_OSPEED_LOW(GPIOB_ILED_5) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ROW5) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOB_RGB_BTN))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_COL7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_TDO) |          \
                                     PIN_PUPDR_PULLUP(GPIOB_nTRST) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ROW1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ROW2) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ROW3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ROW4) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_COL8) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ILED_5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ROW5) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN13) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN14) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_RGB_BTN))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_COL7) |           \
                                     PIN_ODR_LOW(GPIOB_PIN1) |             \
                                     PIN_ODR_LOW(GPIOB_PIN2) |             \
                                     PIN_ODR_LOW(GPIOB_TDO) |              \
                                     PIN_ODR_LOW(GPIOB_nTRST) |           \
                                     PIN_ODR_LOW(GPIOB_ROW1) |           \
                                     PIN_ODR_LOW(GPIOB_ROW2) |          \
                                     PIN_ODR_LOW(GPIOB_ROW3) |             \
                                     PIN_ODR_LOW(GPIOB_ROW4) |          \
                                     PIN_ODR_LOW(GPIOB_COL8) |          \
                                     PIN_ODR_LOW(GPIOB_ILED_5) |           \
                                     PIN_ODR_LOW(GPIOB_ROW5) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |            \
                                     PIN_ODR_LOW(GPIOB_RGB_BTN))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_COL7, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_TDO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_nTRST, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ROW1, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ROW2, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ROW3, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_ROW4, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_COL8, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ILED_5, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ROW5, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN13, 5U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_RGB_BTN, 5U))

/*
 * GPIOC setup:
 *
 * PC0  - KEY column 11             (output pushpull).
 * PC1  - KEY column 12             (output pushpull).
 * PC2  - KEY column 13             (output pushpull).
 * PC3  - KEY column 14             (output pushpull).
 * PC4  - KEY column 5              (output pushpull).
 * PC5  - KEY column 6              (output pushpull).
 * PC6  - KEY column 1              (output pushpull).
 * PC7  - LED 1                     (output pushpull).
 * PC8  - LED 2                     (output pushpull).
 * PC9  - LED 3                     (output pushpull).
 * PC10 - KEY column 4              (output pushpull).
 * PC11 - LED 6                     (output pushpull).
 * PC12 - LED 7                     (output pushpull).
 * PC13 - KEY column 10             (output pushpull).
 * PC14 - KEY column 9              (output pushpull).
 * PC15 - NC                        (input pulldown).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_COL11) |         \
                                     PIN_MODE_OUTPUT(GPIOC_COL12) |         \
                                     PIN_MODE_OUTPUT(GPIOC_COL13) |           \
                                     PIN_MODE_OUTPUT(GPIOC_COL14) |           \
                                     PIN_MODE_OUTPUT(GPIOC_COL5) |           \
                                     PIN_MODE_OUTPUT(GPIOC_COL6) |           \
                                     PIN_MODE_OUTPUT(GPIOC_COL1) |           \
                                     PIN_MODE_OUTPUT(GPIOC_ILED_1) |         \
                                     PIN_MODE_OUTPUT(GPIOC_ILED_2) |           \
                                     PIN_MODE_OUTPUT(GPIOC_ILED_3) |           \
                                     PIN_MODE_OUTPUT(GPIOC_COL4) |          \
                                     PIN_MODE_OUTPUT(GPIOC_ILED_6) |          \
                                     PIN_MODE_OUTPUT(GPIOC_ILED_7) |          \
                                     PIN_MODE_OUTPUT(GPIOC_COL10) |         \
                                     PIN_MODE_OUTPUT(GPIOC_COL9) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_COL11) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL12) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL13) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL14) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ILED_1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ILED_2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ILED_3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ILED_6) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ILED_7) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_COL9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOC_COL11) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL12) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL13) |          \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL14) |          \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL5) |          \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL6) |          \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL1) |          \
                                     PIN_OSPEED_LOW(GPIOC_ILED_1) |        \
                                     PIN_OSPEED_LOW(GPIOC_ILED_2) |          \
                                     PIN_OSPEED_LOW(GPIOC_ILED_3) |          \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL4) |         \
                                     PIN_OSPEED_LOW(GPIOC_ILED_6) |         \
                                     PIN_OSPEED_LOW(GPIOC_ILED_7) |         \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL10) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_COL9) |      \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOC_COL11) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL12) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL13) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL14) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL5) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_ILED_1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_ILED_2) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_ILED_3) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL4) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_ILED_6) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_ILED_7) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL10) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOC_COL9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_COL11) |           \
                                     PIN_ODR_LOW(GPIOC_COL12) |           \
                                     PIN_ODR_LOW(GPIOC_COL13) |             \
                                     PIN_ODR_LOW(GPIOC_COL14) |             \
                                     PIN_ODR_LOW(GPIOC_COL5) |             \
                                     PIN_ODR_LOW(GPIOC_COL6) |             \
                                     PIN_ODR_LOW(GPIOC_COL1) |             \
                                     PIN_ODR_LOW(GPIOC_ILED_1) |           \
                                     PIN_ODR_LOW(GPIOC_ILED_2) |             \
                                     PIN_ODR_LOW(GPIOC_ILED_3) |             \
                                     PIN_ODR_LOW(GPIOC_COL4) |            \
                                     PIN_ODR_LOW(GPIOC_ILED_6) |            \
                                     PIN_ODR_LOW(GPIOC_ILED_7) |            \
                                     PIN_ODR_LOW(GPIOC_COL10) |           \
                                     PIN_ODR_LOW(GPIOC_COL9) |         \
                                     PIN_ODR_LOW(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_COL11, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_COL12, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_COL13, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_COL14, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_COL5, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_COL6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_COL1, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_ILED_1, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_ILED_2, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_ILED_3, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_COL4, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_ILED_6, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_ILED_7, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_COL10, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_COL9, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup).
 * PD1  - PIN1                      (input pullup).
 * PD2  - LED 8                     (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - PIN4                      (input pullup).
 * PD5  - PIN5                      (input pullup).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD10 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - PIN12                     (input pullup).
 * PD13 - PIN13                     (input pullup).
 * PD14 - PIN14                     (input pullup).
 * PD15 - PIN15                     (input pullup).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_OUTPUT(GPIOD_ILED_8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ILED_8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN1) |          \
                                     PIN_OSPEED_LOW(GPIOD_ILED_8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOD_ILED_8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_LOW(GPIOD_ILED_8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_ILED_8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - PIN2                      (input pullup).
 * PE3  - PIN3                      (input pullup).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - PIN7                      (input pullup).
 * PE8  - PIN8                      (input pullup).
 * PE9  - PIN9                      (input pullup).
 * PE10 - PIN10                     (input pullup).
 * PE11 - PIN11                     (input pullup).
 * PE12 - PIN12                     (input pullup).
 * PE13 - PIN13                     (input pullup).
 * PE14 - PIN14                     (input pullup).
 * PE15 - PIN15                     (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input pullup).
 * PF1  - PIN1                      (input pullup).
 * PF2  - PIN2                      (input pullup).
 * PF3  - PIN3                      (input pullup).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF8  - PIN8                      (input pullup).
 * PF9  - PIN9                      (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - PIN12                     (input pullup).
 * PF13 - PIN13                     (input pullup).
 * PF14 - PIN14                     (input pullup).
 * PF15 - PIN15                     (input pullup).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP(GPIOF_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input pullup).
 * PG1  - PIN1                      (input pullup).
 * PG2  - PIN2                      (input pullup).
 * PG3  - PIN3                      (input pullup).
 * PG4  - PIN4                      (input pullup).
 * PG5  - PIN5                      (input pullup).
 * PG6  - PIN6                      (input pullup).
 * PG7  - PIN7                      (input pullup).
 * PG8  - PIN8                      (input pullup).
 * PG9  - PIN9                      (input pullup).
 * PG10 - PIN10                     (input pullup).
 * PG11 - PIN11                     (input pullup).
 * PG12 - PIN12                     (input pullup).
 * PG13 - PIN13                     (input pullup).
 * PG14 - PIN14                     (input pullup).
 * PG15 - PIN15                     (input pullup).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLUP(GPIOG_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
