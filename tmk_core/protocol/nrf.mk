NRF_DIR = protocol/nrf

SRC += $(NRF_DIR)/ble/ble_bas_service.c
SRC += $(NRF_DIR)/ble/ble_hid_service.c
SRC += $(NRF_DIR)/ble/ble_services.c
SRC += $(NRF_DIR)/ble_keyboard.c
SRC += $(NRF_DIR)/matrix.c
SRC += $(NRF_DIR)/main.c

# Search Path
VPATH += $(TMK_DIR)/$(NRF_DIR)
VPATH += $(TMK_DIR)/$(NRF_DIR)/ble
VPATH += $(TMK_DIR)/protocol/chibios/lufa_utils
