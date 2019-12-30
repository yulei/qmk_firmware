#For platform and packs
NRF_MCU = NRF52832xxAA
MCU = cortex-m4

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes	    # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # USB Nkey Rollover
NO_USB_STARTUP_CHECK = no   # Disable initialization only when usb is plugged in

CUSTOM_MATRIX = yes

# project specific files
