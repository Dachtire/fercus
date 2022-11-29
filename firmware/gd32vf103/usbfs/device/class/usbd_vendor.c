/*!
    \file    standard_hid_core.c
    \brief   HID class driver

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

#include "usbd_vendor.h"
//#include <string.h>
#include "main.h"
//#include "debug.h"
//#include "usb_prop.h"
//#include "usb_ch9_std.h"

#define USBD_VID                     0x1a86
#define USBD_PID 0x5537


/* Note:it should use the C99 standard when compiling the below codes */
/* USB device descriptor */
const usb_desc_dev USBD_VENDOR_DEV_DESC =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV
     },
    .bcdUSB                = USB_BCD_RELEASE,
    .bDeviceClass          = USB_CLASS_VENDOR,
    .bDeviceSubClass       = USB_VENDOR_SUBCLASS,
    .bDeviceProtocol       = USB_VENDOR_PROTOCOL,
    .bMaxPacketSize0       = USBD_VPC_EP0_MAX_PACKET,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = USB_BCD_DEVICE,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};


const usbd_vendor_desc_config_set USBD_VENDOR_CONFIG_DESC =
{
    // usb configuration descriptor
    .config =
    {
        .header =
         {
             .bLength         = USB_CFG_DESC_LEN,
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = USBD_VENDOR_CONFIG_DESC_SIZE,
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = HID_BUS_POWERED,
        .bMaxPower            = HID_MAXPOWER(500)
    },

    // interface descriptor
    .itf =
    {
        .header =
        {
            .bLength         = USB_ITF_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_ITF
        },
        .bInterfaceNumber     = USBD_VENDOR_INF,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_CLASS_VENDOR,
        .bInterfaceSubClass   = USB_VENDOR_SUBCLASS,
        .bInterfaceProtocol   = USB_VENDOR_PROTOCOL,
        .iInterface           = 0x00U
    },

    // endpoint descriptor
    .epin1 =
    {
        .header =
        {
            .bLength         = USB_EP_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = USBD_VENDOR_EP1_IN,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = USBD_VPC_IN_PACKET,
        .bInterval            = USBD_VPC_EP_INTERVAL
    },

    .epout1 =
    {
        .header =
        {
            .bLength         = USB_EP_DESC_LEN,
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = USBD_VENDOR_EP1_OUT,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = USBD_VPC_OUT_PACKET,
        .bInterval            = USBD_VPC_EP_INTERVAL
    },

//    .epin2 =
//    {
//        .header =
//        {
//            .bLength         = USB_EP_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_EP
//        },
//        .bEndpointAddress     = USBD_VENDOR_EP2_IN,
//        .bmAttributes         = USB_EP_ATTR_BULK,
//        .wMaxPacketSize       = USBD_VPC_IN_PACKET,
//        .bInterval            = USBD_VPC_EP_INTERVAL
//    },
//
//    .epout2 =
//    {
//        .header =
//        {
//            .bLength         = USB_EP_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_EP
//        },
//        .bEndpointAddress     = USBD_VENDOR_EP2_OUT,
//        .bmAttributes         = USB_EP_ATTR_BULK,
//        .wMaxPacketSize       = USBD_VPC_OUT_PACKET,
//        .bInterval            = USBD_VPC_EP_INTERVAL
//    }
};

/* USB language ID Descriptor */
//const usb_desc_LANGID usbd_kb_language_id_desc =
//{
//    .header =
//     {
//         .bLength         = sizeof(usb_desc_LANGID),
//         .bDescriptorType = USB_DESCTYPE_STR
//     },
//    .wLANGID              = ENG_LANGID
//};

/* USB manufacture string */
static const usb_desc_str manufacturer_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(10U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static const usb_desc_str product_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(5U),
         .bDescriptorType = USB_DESCTYPE_STR,
     },
     .unicode_string = {'S', 'O', 'K', '4', '2'}
};

/* USBD serial string */
static const usb_desc_str serial_string =
{
    .header =
     {
         .bLength         = USB_STRING_LEN(12U),
         .bDescriptorType = USB_DESCTYPE_STR,
     }
};

//void *const USBD_KB_STRINGS[] =
//{
//    [STR_IDX_LANGID]  = (uint8_t *)&usbd_kb_language_id_desc,
//    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
//    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
//    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
//};

//usb_desc USBD_KB_DESC = {
//    .dev_desc    = (uint8_t *)&USBD_KB_DEV_DESC,
//    .config_desc = (uint8_t *)&USBD_KB_CONFIG_DESC,
//    .strings     = USBD_KB_STRINGS
//};

/* report desc */
// bitmap
//const uint8_t USBD_KB_REPORT_DESC[USBD_KB_REPORT_DESC_SIZE] = {
//    USAGE_PAGE, USAGE_PAGE_GENERIC_DESKTOP,
//    USAGE, USAGE_GENERIC_DESKTOP_PAGE_KEYBOARD,
//    COLLECTION, COLLECTION_APPLICATION,
//        // modifier keys
//        USAGE_PAGE, USAGE_PAGE_KEYBOARD,
//        USAGE_MINIMUM, KB_PAGE_LEFTCONTROL,
//        USAGE_MAXIMUM, KB_PAGE_RIGHT_GUI,
//        LOGICAL_MINIMUM, 0x00,
//        LOGICAL_MAXIMUM, 0x01,
//        REPORT_SIZE, 0x01,
//        REPORT_COUNT, 0x08,
//        USAGE_TYPE_INPUT, USAGE_TYPE_DATA_DV,
//        // normal keys
//        USAGE_PAGE, USAGE_PAGE_KEYBOARD,
//        USAGE_MINIMUM, KB_PAGE_NONE,
//        USAGE_MAXIMUM, KB_PAGE_KEYPAD_PLUS,  // REPORT_COUNT - 1
//        LOGICAL_MINIMUM, 0x00,
//        LOGICAL_MAXIMUM, 0x01,
//        REPORT_SIZE, 0x01,
//        REPORT_COUNT, 0x58,
//        USAGE_TYPE_INPUT, USAGE_TYPE_DATA_DV,
//        // leds
//        USAGE_PAGE, USAGE_PAGE_LED,
//        USAGE_MINIMUM, LED_PAGE_UNDEFINED,
//        USAGE_MAXIMUM, LED_PAGE_SHIFT,
//        REPORT_SIZE, 0x01,
//        REPORT_COUNT, 0x08,
//        USAGE_TYPE_OUTPUT, USAGE_TYPE_DATA_DV,
//    END_COLECTION
//};


/* local function prototypes ('static') */
//static uint8_t hid_kb_init    (usb_dev *udev, uint8_t config_index);
//static uint8_t hid_kb_deinit  (usb_dev *udev, uint8_t config_index);
//static uint8_t hid_kb_req     (usb_dev *udev, usb_req *req);
//static uint8_t hid_kb_data_in (usb_dev *udev, uint8_t ep_num);
//static uint8_t hid_kb_data_out (usb_dev *udev, uint8_t ep_num);
//
//usb_class_core hid_kb_cb = {
//    .command         = NO_CMD,
//    .alter_set       = 0U,
//
//    .init            = hid_kb_init,
//    .deinit          = hid_kb_deinit,
//    .req_proc        = hid_kb_req,
//    .data_in         = hid_kb_data_in,
//    .data_out        = hid_kb_data_out
//};
//
///*!
//    \brief      check cdc acm is ready for data transfer
//    \param[in]  udev: pointer to USB device instance
//    \param[out] none
//    \retval     0 if cdc is ready, 5 else
//*/
//uint8_t hid_kb_check_send(usb_dev *udev)
//{
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    if (1U == hid->sent_flag) {
//        return USBD_OK;
//    }
//
//    return USBD_BUSY;
//}
//
//uint8_t hid_kb_check_recev(usb_dev *udev)
//{
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    if (1U == hid->receive_flag) {
//        return USBD_OK;
//    }
//
//    return USBD_BUSY;
//}
//
///*!
//    \brief      register HID interface operation functions
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  hid_fop: HID operation functions structure
//    \param[out] none
//    \retval     USB device operation status
//*/
//uint8_t hid_kb_itfop_register (usb_dev *udev, hid_kb_fop_handler *hid_fop)
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
///*!
//    \brief      send keyboard report
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  report: pointer to HID report
//    \param[in]  len: data length
//    \param[out] none
//    \retval     USB device operation status
//*/
//uint8_t hid_kb_report_send (usb_dev *udev, uint8_t *report, uint32_t len)
//{
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    hid->sent_flag = 0U;
//
//    usbd_ep_send(udev, HID_KB_IN_EP, report, USBD_KB_SEND_SIZE);
//
//    return USBD_OK;
//}
//
///*!
//    \brief      receive CDC ACM data
//    \param[in]  udev: pointer to USB device instance
//    \param[out] none
//    \retval     USB device operation status
//*/
//uint8_t hid_kb_report_receive (usb_dev *udev)
//{
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//    hid->receive_flag = 0U;
//    usbd_ep_recev(udev, CDC_DATA_OUT_EP, kb_buf_recev, USBD_KB_RECEV_SIZE);
//    return USBD_OK;
//}
//
///*!
//    \brief      initialize the HID device
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  config_index: configuration index
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t hid_kb_init (usb_dev *udev, uint8_t config_index)
//{
//    static hid_kb_handler hid_handler;
//
//    memset((void *)&hid_handler, 0U, sizeof(hid_kb_handler));
//
//     Initialize the data Tx endpoint
//    usbd_ep_setup (udev, &(hid_kb_config_desc.hid_epin));
//    usbd_ep_setup (udev, &(hid_kb_config_desc.hid_epout));
//
//    usbd_ep_recev (udev, HID_KB_OUT_EP, hid_handler.data_out, USBD_KB_RECEV_SIZE);
//
//    hid_handler.sent_flag = 1U;
//    hid_handler.receive_flag = 1U;
//
//    udev->dev.class_data[HID_KB_INF] = (void *)&hid_handler;
//
//    if (NULL != udev->dev.user_data) {
//        ((hid_kb_fop_handler *)udev->dev.user_data)->hid_itf_config();
//    }
//
//    return USBD_OK;
//}
//
///*!
//    \brief      de-initialize the HID device
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  config_index: configuration index
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t hid_kb_deinit (usb_dev *udev, uint8_t config_index)
//{
//     deinitialize HID endpoints
//    usbd_ep_clear(udev, HID_KB_IN_EP);
//    usbd_ep_clear(udev, HID_KB_OUT_EP);
//
//    return USBD_OK;
//}
//
///*!
//    \brief      handle the HID class-specific requests
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  req: device class-specific request
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t hid_kb_req (usb_dev *udev, usb_req *req)
//{
//    usb_transc *transc = &udev->dev.transc_in[0];
//
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    switch (req->bRequest) {
//        case GET_REPORT:
//             no use for this driver
//            break;
//
//        case GET_IDLE:
//            transc->xfer_buf = (uint8_t *)&hid->idle_state;
//
//            transc->remain_len = 1U;
//            break;
//
//        case GET_PROTOCOL:
//            transc->xfer_buf = (uint8_t *)&hid->protocol;
//
//            transc->remain_len = 1U;
//            break;
//
//        case SET_REPORT:
//             no use for this driver
//            break;
//
//        case SET_IDLE:
//            hid->idle_state = (uint8_t)(req->wValue >> 8U);
//            break;
//
//        case SET_PROTOCOL:
//            hid->protocol = (uint8_t)(req->wValue);
//            break;
//
//        case USB_GET_DESCRIPTOR:
//            if (USB_DESCTYPE_REPORT == (req->wValue >> 8U)) {
//                transc->remain_len = USB_MIN(USBD_KB_REPORT_DESC_SIZE, req->wLength);
//                transc->xfer_buf = (uint8_t *)USBD_KB_REPORT_DESC;
//
//                return REQ_SUPP;
//            }
//            break;
//
//        default:
//            break;
//    }
//
//    return USBD_OK;
//}
//
///*!
//    \brief      handle data stage
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  ep_num: endpoint identifier
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t hid_kb_data_in (usb_dev *udev, uint8_t ep_num)
//{
//
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    hid->sent_flag = 1U;
//
//    return USBD_OK;
//}
//
///*!
//    \brief      handle custom HID data
//    \param[in]  udev: pointer to USB device instance
//    \param[in]  ep_num: endpoint identifier
//    \param[out] none
//    \retval     USB device operation status
//*/
//static uint8_t hid_kb_data_out (usb_dev *udev, uint8_t ep_num)
//{
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
//
//    hid->receive_flag = 1U;
//
//    return USBD_OK;
//}

void usbd_vendor_send(uint8_t *data, uint16_t length, uint8_t ep_num)
{
    UserToPMABufferCopy(data, ENDP1_TXADDR, length);
    SetEPTxCount(ep_num, length);
    SetEPTxValid(ep_num);
    USBD_Endp1_Busy = TRUE;
}

uint16_t mult_length = 0;
uint8_t *mult_ptr = NULL;
void usbd_vendor_send_mult(uint8_t *data, uint16_t length, uint8_t ep_num)
{
    if (length > USBD_VPC_EP_MAX_PACKET) {
        mult_length = length - USBD_VPC_EP_MAX_PACKET;
        mult_ptr = data + USBD_VPC_EP_MAX_PACKET;
        UserToPMABufferCopy(data, ENDP1_TXADDR, USBD_VPC_EP_MAX_PACKET);
        SetEPTxCount(ep_num, USBD_VPC_EP_MAX_PACKET);
        SetEPTxValid(ep_num);
        USBD_Endp1_Busy = TRUE;
    } else {
        mult_length = 0;
        UserToPMABufferCopy(data, ENDP1_TXADDR, length);
        SetEPTxCount(ep_num, length);
        SetEPTxValid(ep_num);
        USBD_Endp1_Busy = TRUE;
    }
}

void usbd_vendor_receive(uint8_t *data, uint8_t ep_num)
{
    USB_SIL_Read(ep_num, data);

    static uint8_t tmp = 0xff;
    switch (data[0]) {
        case KB_CTL_ADC_ON:
            kb_enable_usbd();
//            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//            for (uint16_t i = 0; i < KB_ADC_SIZE; ++i) {
//                kb_adc_buf1[i] = 0xf0 + i;
//            }
//            usbd_vendor_send((uint8_t *) kb_adc_buf1, 10, ENDP1);

            break;
        case KB_CTL_ADC_OFF:
            KB_CTL &= ~KB_CTL_USBD;
//            ADC_SoftwareStartConvCmd(ADC1, DISABLE);
            break;
        case KB_CTL_SYSCLK:
            usbd_vendor_send((uint8_t *) &SystemCoreClock, 4, ep_num);
            break;
        default:
            usbd_vendor_send(&tmp, 1, ep_num);
            break;
    }

//    if (data[0] == KB_CTL_ADC_ON) {
//        kb_enable_usbd();
//    } else {
//        usbd_vendor_send((uint8_t *) 0xff, ep_num);
//    }
//    usbd_vendor_send(data, ep_num);
    SetEPRxValid(ep_num);
}

uint8_t usbd_vendor_check_send()
{
    if (USBD_Endp1_Busy == FALSE) {
        return USB_SUCCESS;
    } else {
        return USB_ERROR;
    }
}

uint8_t usbd_vendor_check_recev()
{
    //    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[HID_KB_INF];
    //
    //    if (1U == hid->receive_flag) {
    //        return USBD_OK;
    //    }
    //
//        return USBD_BUSY;
//    if (USBD_Endp1_Busy == FALSE) {
//        return USB_SUCCESS;
//    } else {
//        return USB_ERROR;
//    }
}