/*!
    \file    hid_printer_wrapper.c
    \brief   this file calls to the separate HID and printer class layer handlers

    \version 2020-08-04, V1.1.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "usbd_composite.h"
#include "usbd_conf.h"
#include "usbd_enum.h"

#include "usbd-hid-keyboard.h"
#include "usbd_hid_cntlr.h"
#include "usbd_hid_mouse.h"

#define USBD_VID                     0x28e9U
#if KB_SIDE == KB_SIDE_LEFT
    #define USBD_PID 0x038aU
#else
    #define USBD_PID 0x038bU
#endif

/* Note:it should use the C99 standard when compiling the below codes */
/* USB device descriptor */
const usb_desc_dev usbd_composite_dev_desc =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV
     },
    .bcdUSB                = USB_BCD_RELEASE,
    .bDeviceClass          = 0x00U,
    .bDeviceSubClass       = 0x00U,
    .bDeviceProtocol       = 0x00U,
    .bMaxPacketSize0       = USB_FS_EP0_MAX_LEN,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = USB_BCD_DEVICE,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};


const usbd_composite_desc_config_set usbd_composite_config_desc =
{
    // usb configuration descriptor
    .config =
    {
        .header =
         {
             .bLength         = USB_CFG_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = USBD_COMPOSITE_CONFIG_DESC_SIZE,
        .bNumInterfaces       = USBD_ITF_NUM_COMPOSITE,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = HID_BUS_POWERED | HID_REMOTEWAKEUP,
        .bMaxPower            = HID_MAXPOWER(500)
    },

    // interface descriptor
    .kb_inf =
    {
        .header =
        {
            .bLength         = USB_ITF_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_ITF
        },
        .bInterfaceNumber     = USBD_INF_KB,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = USB_HID_SUBCLASS_BOOT_ITF,
        .bInterfaceProtocol   = USB_HID_PROTOCOL_KEYBOARD,
        .iInterface           = 0x00U
    },

    // hid descriptor
    .kb_hid =
    {
        .header =
        {
            .bLength         = USB_HID_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_HID
        },
        .bcdHID               = HID_CD,
        .bCountryCode         = HID_COUNTRYCODE,
        .bNumDescriptors      = 0x01U,
        .bDescriptorType      = USB_DESCTYPE_REPORT,
        .wDescriptorLength    = USBD_REPORT_DESC_SIZE_KB,
    },

    // endpoint descriptor
    .kb_epin =
    {
        .header =
        {
            .bLength         = USB_EP_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = USBD_EP_IN_KB,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_KB_IN_PACKET,
        .bInterval            = 0x01U
    },

    .kb_epout =
    {
        .header =
        {
            .bLength         = USB_EP_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = USBD_EP_OUT_KB,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_KB_OUT_PACKET,
        .bInterval            = 0x01U
    },

    // interface descriptor
    .cntlr_inf =
    {
        .header =
         {
             .bLength         = USB_ITF_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = USBD_INF_CNTLR,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = USB_HID_SUBCLASS_BOOT_ITF,
        .bInterfaceProtocol   = USB_HID_PROTOCOL_CNTLR,
        .iInterface           = 0x00U
    },

    .cntlr_hid =
    {
        .header =
         {
             .bLength         = USB_HID_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_HID
         },
        .bcdHID               = HID_CD,
        .bCountryCode         = HID_COUNTRYCODE,
        .bNumDescriptors      = 0x01U,
        .bDescriptorType      = USB_DESCTYPE_REPORT,
        .wDescriptorLength    = USBD_REPORT_DESC_SIZE_CNTLR,
    },

    .cntlr_epin =
    {
        .header =
         {
             .bLength         = USB_EP_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = USBD_EP_IN_CNTLR,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_CNTLR_IN_PACKET,
        .bInterval            = 0x01U
    },

    .cntlr_epout =
    {
        .header =
         {
             .bLength         = USB_EP_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = USBD_EP_OUT_CNTLR,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_CNTLR_OUT_PACKET,
        .bInterval            = 0x01U
    },

    // interface descriptor
    .mouse_inf =
    {
        .header =
         {
             .bLength         = USB_ITF_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = USBD_INF_MOUSE,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = USB_HID_SUBCLASS_BOOT_ITF,
        .bInterfaceProtocol   = USB_HID_PROTOCOL_MOUSE,
        .iInterface           = 0x00U
    },

    .mouse_hid =
    {
        .header =
         {
             .bLength         = USB_HID_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_HID
         },
        .bcdHID               = HID_CD,
        .bCountryCode         = HID_COUNTRYCODE,
        .bNumDescriptors      = 0x01U,
        .bDescriptorType      = USB_DESCTYPE_REPORT,
        .wDescriptorLength    = HID_MOUSE_REPORT_DESC_SIZE,
    },

    .mouse_epin =
    {
        .header =
         {
             .bLength         = USB_EP_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = USBD_EP_IN_MOUSE,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_MOUSE_IN_PACKET,
        .bInterval            = 0x01U
    },

    .mouse_epout =
    {
        .header =
         {
             .bLength         = USB_EP_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = USBD_EP_OUT_MOUSE,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = HID_MOUSE_OUT_PACKET,
        .bInterval            = 0x01U
    }
};

/* USB language ID Descriptor */
const usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR
     },
    .wLANGID              = ENG_LANGID
};

/* USB manufacture string */
const usb_desc_str manufacturer_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(8U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'c', 'h', 'u', 'l', 'a', 'i', 'n', 'e'}
};

/* USB product string */
const usb_desc_str product_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(13U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'f', 'e', 'r', 'c', 'u', 's', '-', 'd', 'o', 'n', 'g', 'l', 'e'}
};

/* USBD serial string */
const usb_desc_str serial_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

//void *const usbd_composite_strings[] =
//{
//    [STR_IDX_LANGID]  = (uint8_t *)&usbd_language_id_desc,
//    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
//    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
//    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
//};

//usb_desc usb_composite_desc = {
//    .dev_desc    = (uint8_t *)&usbd_composite_dev_desc,
//    .config_desc = (uint8_t *)&usbd_composite_config_desc,
//    .strings     = usbd_hid_composite_strings
//};

/* local function prototypes ('static') */
//static uint8_t usb_composite_init (usb_dev *udev, uint8_t config_index);
//static uint8_t usb_composite_deinit (usb_dev *udev, uint8_t config_index);
//static uint8_t usb_composite_req_handler (usb_dev *udev, usb_req *req);
////static uint8_t usb_composite_ctlx_out (usb_dev *udev);
//static uint8_t usb_composite_data_in (usb_dev *udev, uint8_t ep_num);
//static uint8_t usb_composite_data_out (usb_dev *udev, uint8_t ep_num);
//
//usb_class_core usb_composite_cb = {
//    .command   = NO_CMD,
//    .alter_set = 0U,
//
//    .init      = usb_composite_init,
//    .deinit    = usb_composite_deinit,
//
//    .req_proc  = usb_composite_req_handler,
////    .ctlx_out  = usb_composite_ctlx_out,
//
//    .data_in   = usb_composite_data_in,
//    .data_out  = usb_composite_data_out,
//};
//
///*!
//    \brief      register HID interface operation functions
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  hid_fop: HID operation functions structure
//    \param[out] none
//    \retval     USB device operation status
//*/
//uint8_t hid_composite_itfop_register (usb_dev *udev, hid_composite_fop_handler *hid_fop)
//{
//    if (NULL != hid_fop) {
//        udev->dev.user_data = (void *)hid_fop;
//
//        return USBD_OK;
//    }
//
//    return USBD_FAIL;
//}
//
//
///*!
//    \brief      initialize the HID/printer device
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  config_index: configuration index
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t usb_composite_init (usb_dev *udev, uint8_t config_index)
//{
//    /* HID initialization */
//    hid_kb_cb.init(udev, config_index);
//    hid_mouse_cb.init(udev, config_index);
//    hid_cntlr_cb.init(udev, config_index);
//
//    return USBD_OK;
//}
//
///*!
//    \brief      de-initialize the HID/printer device
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  config_index: configuration index
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t usb_composite_deinit (usb_dev *udev, uint8_t config_index)
//{
//    /* HID De-initialization */
//    hid_kb_cb.deinit (udev, config_index);
//    hid_mouse_cb.deinit (udev, config_index);
//    hid_cntlr_cb.deinit (udev, config_index);
//
//    return USBD_OK;
//}
//
///*!
//    \brief      handle the custom HID/printer class-specific request
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  req: device class request
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t usb_composite_req_handler (usb_dev *udev, usb_req *req)
//{
//    switch (req->wIndex & 0xFF) {
//        case USBD_INF_KB:
//            return hid_kb_cb.req_proc(udev, req);
//        case USBD_INF_MOUSE:
//            return hid_mouse_cb.req_proc(udev, req);
//        case USBD_INF_CNTLR:
//            return hid_cntlr_cb.req_proc(udev, req);
//        default:
//            break;
//    }
//}

/*!
    \brief      handle data IN stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
//static uint8_t usb_composite_data_in (usb_dev *udev, uint8_t ep_num)
//{
//    switch (ep_num) {
////        case USBD_EP_IN_KB & 0x7F:
//        case EP_ID(USBD_EP_IN_KB):
//            return hid_kb_cb.data_in(udev, ep_num);
////        case USBD_EP_IN_MOUSE & 0x7F:
//        case EP_ID(USBD_EP_IN_MOUSE):
//            return hid_mouse_cb.data_in(udev, ep_num);
////        case USBD_EP_IN_CNTLR & 0x7F:
//        case EP_ID(USBD_EP_IN_CNTLR):
//            return hid_cntlr_cb.data_in(udev, ep_num);
//        default:
//            break;
//    }
//}

/*!
    \brief      handle data OUT stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     USB device operation status
*/
//static uint8_t usb_composite_data_out (usb_dev *udev, uint8_t ep_num)
//{
//    switch (ep_num) {
////        case USBD_EP_OUT_KB & 0x7F:
//        case EP_ID(USBD_EP_IN_KB):
//            return hid_kb_cb.data_out(udev, ep_num);
////        case USBD_EP_OUT_MOUSE & 0x7F:
//        case EP_ID(USBD_EP_IN_MOUSE):
//            return hid_mouse_cb.data_out(udev, ep_num);
////        case USBD_EP_OUT_CNTLR & 0x7F:
//        case EP_ID(USBD_EP_IN_CNTLR):
//            return hid_cntlr_cb.data_out(udev, ep_num);
//        default:
//            break;
//    }
//}