/**
 * wcid.h
 */
#pragma once

#include <stdint.h>
#include <string.h>
//#include <LUFA/Common/Common.h>
#include <LUFA/Drivers/USB/USB.h>

/** Device control request used for retrieving the OS Feature descriptors of the device. */
		#define REQ_GetOSFeatureDescriptor       0x20

		/** Descriptor index for a Microsoft Proprietary Extended Device Compatibility descriptor. */
		#define EXTENDED_COMPAT_ID_DESCRIPTOR    0x0004

		/** Descriptor index for a Microsoft Proprietary Extended Device Properties OS Feature Descriptor. */
		#define EXTENDED_PROPERTIES_DESCRIPTOR   0x0005

		/** wchar_t is not available on all platforms */
		#if ((ARCH == ARCH_AVR8) || (ARCH == ARCH_XMEGA))
		#define WCHAR                  wchar_t
		#else
		#define WCHAR                  uint16_t
		#endif

		/** Interface & (dummy) Endpoint properties */
		/* #define WCID_IF_NUMBER         0
		#define WCID_IN_EPNUM          1
		#define WCID_OUT_EPNUM         2
		#define WCID_IO_EPSIZE         64
        */

		/** Registry values we want to set using the Properties Descriptor */
		/* #define NB_PROPERTIES          2
		#define PROPERTY1_NAME         L"DeviceInterfaceGUID"
		#define PROPERTY1_TYPE         REG_SZ
		#define PROPERTY1_DATA         L"{12341234-1234-1234-1234-123412341234}"
		#define PROPERTY2_NAME         L"Icons"
		#define PROPERTY2_TYPE         REG_EXPAND_SZ
		#define PROPERTY2_DATA         L"%SystemRoot%\\system32\\setupapi.dll,-20"
        */

		/** Helper Macro for the above. Header size is 14 bytes */
		//#define PROPERTY_SIZE(idx)     (14 + sizeof(PROPERTY##idx##_NAME) + sizeof(PROPERTY##idx##_DATA))

	/* Type Defines: */
		/* typedef struct
		{
			USB_Descriptor_Configuration_Header_t  Config;
			USB_Descriptor_Interface_t             Interface;
			USB_Descriptor_Endpoint_t              DataInEndpoint;
			USB_Descriptor_Endpoint_t              DataOutEndpoint;
		} USB_Descriptor_Configuration_t;
        */

		typedef struct
		{
			USB_Descriptor_Header_t                Header;
			int                                    Signature[7];
			uint8_t                                VendorCode;
			uint8_t                                Reserved;
		} USB_OSDescriptor_t;

		typedef struct
		{
			uint8_t                                FirstInterfaceNumber;
			uint8_t                                Reserved;
			uint8_t                                CompatibleID[8];
			uint8_t                                SubCompatibleID[8];
			uint8_t                                Reserved2[6];
		} USB_OSCompatibleSection_t;

		typedef struct
		{
			uint32_t                               TotalLength;
			uint16_t                               Version;
			uint16_t                               Index;
			uint8_t                                TotalSections;
			uint8_t                                Reserved[7];
			USB_OSCompatibleSection_t              CompatID;
		} USB_OSCompatibleIDDescriptor_t;

		/* typedef struct
		{
			uint16_t                               Length;
			WCHAR                                  Value[];
		} USB_OSPropertiesName_t;

		typedef struct
		{
			uint32_t                               Length;
			WCHAR                                  Value[];
		} USB_OSPropertiesData_t;

		typedef struct
		{
			uint32_t                               Length;
			uint32_t                               Type;
			USB_OSPropertiesName_t                 Name;
			USB_OSPropertiesData_t                 Data;
		} USB_OSPropertiesSection_t;

		typedef struct
		{
			uint32_t                               TotalLength;
			uint16_t                               Version;
			uint16_t                               Index;
			uint16_t                               TotalSections;
		} USB_OSPropertiesHeader_t;

		typedef struct
		{
			USB_OSPropertiesHeader_t               Header;
			USB_OSPropertiesSection_t              Property[NB_PROPERTIES];
		} USB_OSPropertiesDescriptor_t;
        */

	/* Function Prototypes: */
		/* uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

		uint16_t USB_GetOSFeatureDescriptor(const uint8_t InterfaceNumber,
		                                    const uint8_t wIndex,
		                                    const uint8_t Recipient,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(4);
                                            */
