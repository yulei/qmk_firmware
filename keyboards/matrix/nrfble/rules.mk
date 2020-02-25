#For platform and packs
NRF_MCU = NRF52832xxAA
MCU = cortex-m4

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # USB Nkey Rollover
NO_USB_STARTUP_CHECK = yes  # Disable initialization only when usb is plugged in

CUSTOM_MATRIX = yes
RGBLIGHT_ENABLE = yes
#RGB_MATRIX_ENABLE = yes

SDK_ROOT := $(TOP_DIR)/lib/nRF5_SDK_16.0.0_98a08e2

# project specific files
#SRC += indicator_pca9554.c
