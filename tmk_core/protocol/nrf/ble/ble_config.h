/**
 * @file ble_config.h
 */

#pragma once

#ifdef PASSKEY_REQUIRED
#define SEC_CURRENT SEC_MITM
#define SEC_PARAM_MITM 1
#define SEC_PARAM_IO_CAPABILITIES BLE_GAP_IO_CAPS_KEYBOARD_ONLY
#else
#define SEC_CURRENT SEC_JUST_WORKS
#define SEC_PARAM_MITM 0 /**< Man In The Middle protection not required. */
#define SEC_PARAM_IO_CAPABILITIES BLE_GAP_IO_CAPS_NONE /**< No I/O capabilities. */
#endif

#define SEC_PARAM_BOND 1 /**< Perform bonding. */
#define SEC_PARAM_LESC 0 /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS 0 /**< Keypress notifications not enabled. */
#define SEC_PARAM_OOB 0 /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE 7 /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE 16 /**< Maximum encryption key size. */

#define NAME_XSTR(x) #x
#define NAME_STR(x) NAME_XSTR(x)
#define DEVICE_NAME NAME_STR(PRODUCT)
#define MANUFACTURER_NAME NAME_STR(MANUFACTURER)

#ifndef BATTERY_ADC_PIN
    #define BATTERY_ADC_PIN NRF_SAADC_INPUT_AIN4
#endif
