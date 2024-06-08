/*!
    \file    standard_hid_core.c
    \brief   HID class driver

    \version 2020-08-04, V1.1.0, firmware for GD32VF103
    \version 2022-06-30, V2.1.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

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

#include "usbd-hid-compatibility.h"
#include "ch32v20x_usbfs_device.h"
#include "usb_core.h"
#include "usb_lib.h"
#include "usbd_conf.h"
#include "usbd_enum.h"
#include "wchble.h"
#include "hid.h"

//#define USBD_VID                     0x28e9U
//#if KB_SIDE == KB_SIDE_LEFT
//    #define USBD_PID 0x038aU
//#else
//    #define USBD_PID 0x038bU
//#endif

//uint8_t kb_report_usbd[USBD_REPORT_BYTE_KB];
//uint8_t kb_report_usbh[USBD_REPORT_BYTE_KB];
//uint8_t *kb_rep_send;
//uint8_t kb_report_usbd[USBD_REPORT_BYTE_KB], kb_report_usbhd[USBD_REPORT_BYTE_KB], kb_report_usbh[USBD_REPORT_BYTE_KB], kb_report_empty[USBD_REPORT_BYTE_KB];
//uint8_t kb_rep_recv[USBD_REPORT_RECEV_SIZE_KB];

/* Note:it should use the C99 standard when compiling the below codes */
/* USB device descriptor */
//const usb_desc_dev hid_dev_desc =
//{
//    .header =
//     {
//         .bLength          = USB_DEV_DESC_LEN,
//         .bDescriptorType  = USB_DESCTYPE_DEV
//     },
//    .bcdUSB                = USB_BCD_RELEASE,
//    .bDeviceClass          = 0x00U,
//    .bDeviceSubClass       = 0x00U,
//    .bDeviceProtocol       = 0x00U,
//    .bMaxPacketSize0       = USB_FS_EP0_MAX_LEN,
//    .idVendor              = USBD_VID,
//    .idProduct             = USBD_PID,
//    .bcdDevice             = USB_BCD_DEVICE,
//    .iManufacturer         = STR_IDX_MFC,
//    .iProduct              = STR_IDX_PRODUCT,
//    .iSerialNumber         = STR_IDX_SERIAL,
//    .bNumberConfigurations = USBD_CFG_MAX_NUM
//};


//const usb_hid_desc_config_set usbd_kb_config_desc =
//{
//    // usb configuration descriptor
//    .config =
//    {
//        .header =
//         {
//             .bLength         = USB_CFG_DESC_LEN,
//             .bDescriptorType = USB_DESCTYPE_CONFIG
//         },
//        .wTotalLength         = USBD_CONFIG_DESC_SIZE_KB,
//        .bNumInterfaces       = 0x01U,
//        .bConfigurationValue  = 0x01U,
//        .iConfiguration       = 0x00U,
//        .bmAttributes         = HID_BUS_POWERED | HID_REMOTEWAKEUP,
//        .bMaxPower            = HID_MAXPOWER(500)
//    },
//
//    // interface descriptor
//    .itf =
//    {
//        .header =
//        {
//            .bLength         = USB_ITF_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_ITF
//        },
//        .bInterfaceNumber     = USBD_INF_KB,
//        .bAlternateSetting    = 0x00U,
//        .bNumEndpoints        = 0x02U,
//        .bInterfaceClass      = USB_HID_CLASS,
//        .bInterfaceSubClass   = USB_HID_SUBCLASS_BOOT_ITF,
//        .bInterfaceProtocol   = USB_HID_PROTOCOL_KEYBOARD,
//        .iInterface           = 0x00U
//    },
//
//    // hid descriptor
//    .hid =
//    {
//        .header =
//        {
//            .bLength         = USB_HID_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_HID
//        },
//        .bcdHID               = HID_CD,
//        .bCountryCode         = HID_COUNTRYCODE,
//        .bNumDescriptors      = 0x01U,
//        .bDescriptorType      = USB_DESCTYPE_REPORT,
//        .wDescriptorLength    = USBD_REPORT_DESC_SIZE_KB,
//    },
//
//    // endpoint descriptor
//    .epin =
//    {
//        .header =
//        {
//            .bLength         = USB_EP_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_EP
//        },
//        .bEndpointAddress     = USBD_EP_IN_KYBD,
//        .bmAttributes         = USB_EP_ATTR_INT,
//        .wMaxPacketSize       = HID_KYBD_IN_PACKET,
//        .bInterval            = 0x01U
//    },
//
//    .epout =
//    {
//        .header =
//        {
//            .bLength         = USB_EP_DESC_LEN,
//            .bDescriptorType = USB_DESCTYPE_EP
//        },
//        .bEndpointAddress     = USBD_EP_OUT_KYBD,
//        .bmAttributes         = USB_EP_ATTR_INT,
//        .wMaxPacketSize       = HID_KYBD_OUT_PACKET,
//        .bInterval            = 0x01U
//    }
//};

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
//static const usb_desc_str manufacturer_string =
//{
//    .header =
//     {
//         .bLength         = USB_STRING_LEN(8U),
//         .bDescriptorType = USB_DESCTYPE_STR,
//     },
//    .unicode_string = {'c', 'h', 'u', 'l', 'a', 'i', 'n', 'e'}
//};

/* USB product string */
//static const usb_desc_str product_string =
//{
//    .header =
//     {
//         .bLength         = USB_STRING_LEN(6U),
//         .bDescriptorType = USB_DESCTYPE_STR,
//     },
//     .unicode_string = {'f', 'e', 'r', 'c', 'u', 's'}
//};

/* USBD serial string */
//static const usb_desc_str serial_string =
//{
//    .header =
//     {
//         .bLength         = USB_STRING_LEN(12U),
//         .bDescriptorType = USB_DESCTYPE_STR,
//     }
//};

//void *const USBD_KB_STRINGS[] =
//{
//    [STR_IDX_LANGID]  = (uint8_t *)&usbd_kb_language_id_desc,
//    [STR_IDX_MFC]     = (uint8_t *)&manufacturer_string,
//    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
//    [STR_IDX_SERIAL]  = (uint8_t *)&serial_string
//};

//usb_desc USBD_KB_DESC = {
//    .dev_desc    = (uint8_t *)&USBD_KB_DEV_DESC,
//    .config_desc = (uint8_t *)&usbd_kb_config_desc,
//    .strings     = USBD_KB_STRINGS
//};

const uint8_t usbd_hid_comp_report_desc[USBD_REPORT_DESC_SIZE_COMP] = {
    HID_UsagePageVendor(HID_USAGE_PAGE_UNDEFINED),
    HID_Usage(HID_USAGE_GENERIC_POINTER),
    HID_Collection(HID_Application),
        HID_Usage(HID_USAGE_GENERIC_MOUSE),
        HID_LogicalMin(0x00),
        HID_LogicalMaxS(0xff),
        HID_ReportSize(0x08),
        HID_ReportCount(0x40),
        HID_Input(HID_Data|HID_Variable|HID_Relative),

        HID_Usage(HID_USAGE_GENERIC_MOUSE),
        HID_LogicalMin(0x00),
        HID_LogicalMaxS(0xff),
        HID_ReportSize(0x08),
        HID_ReportCount(0x40),
        HID_Output(HID_Data|HID_Variable|HID_Relative),
    HID_EndCollection
};


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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
//
//    hid->sent_flag = 0U;
//
//    usbd_ep_send(udev, USBD_EP_IN_KYBD, report, USBD_REPORT_BYTE_KB);
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
//    hid->receive_flag = 0U;
//    usbd_ep_recev(udev, CDC_DATA_OUT_EP, kb_rep_recv, USBD_REPORT_RECEV_SIZE_KB);
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
//    usbd_ep_setup (udev, &(hid_kb_config_desc.epin));
//    usbd_ep_setup (udev, &(hid_kb_config_desc.epout));
//
//    usbd_ep_recev (udev, USBD_EP_OUT_KYBD, hid_handler.data_out, USBD_REPORT_RECEV_SIZE_KB);
//
//    hid_handler.sent_flag = 1U;
//    hid_handler.receive_flag = 1U;
//
//    udev->dev.class_data[USBD_INF_KB] = (void *)&hid_handler;
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
//    usbd_ep_clear(udev, USBD_EP_IN_KYBD);
//    usbd_ep_clear(udev, USBD_EP_OUT_KYBD);
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
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
//                transc->remain_len = USB_MIN(USBD_REPORT_DESC_SIZE_KB, req->wLength);
//                transc->xfer_buf = (uint8_t *)usbd_kb_report_desc;
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
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
//    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
//
//    hid->receive_flag = 1U;
//
//    return USBD_OK;
//}

//void usbd_kb_report_send(uint8_t *report)
//{
//    UserToPMABufferCopy(report, ENDP1_TXADDR, USBD_REPORT_BYTE_KB);
//    SetEPTxCount(ENDP1, USBD_REPORT_BYTE_KB);
//    SetEPTxValid(ENDP1);
//    usbd_epin_busy[ENDP1] = TRUE;
//}

//void usbfs_kb_report_send(uint8_t *report)
//{
////    usbfs_epin_busy[ENDP1] = USBFS_Endp_DataUp( DEF_UEP1, report, USBD_REPORT_BYTE_KB, DEF_UEP_CPY_LOAD );
//    USBFS_Endp_DataUp( DEF_UEP1, report, USBD_REPORT_BYTE_KB, DEF_UEP_CPY_LOAD );
//}

//void usbd_kb_report_receive()
//{
//    //    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
//    //    hid->receive_flag = 0U;
//    //    usbd_ep_recev(udev, CDC_DATA_OUT_EP, kb_rep_recv, USBD_REPORT_RECEV_SIZE_KB);
//    //    return USBD_OK;
//
////    uint32_t DataLength = 0;
//
////    DataLength = GetEPRxCount(ENDP1_RXADDR & 0x7F);
//    PMAToUserBufferCopy(kb_rep_recv, ENDP1_RXADDR, USBD_REPORT_RECEV_SIZE_KB);
//    SetEPRxValid(ENDP1);
//
////    return DataLength;
//
////    PMAToUserBufferCopy(report, ENDP1_TXADDR, USBD_REPORT_BYTE_KB);
////    SetEPTxCount(ENDP1, USBD_REPORT_BYTE_KB);
////    SetEPTxValid(ENDP1);
////    usbd_epout_busy[ENDP1] = TRUE;
//}
//
//uint8_t usbd_kb_check_send()
//{
//    if (usbd_epin_busy[ENDP1] == FALSE) {
//        return USB_SUCCESS;
//    } else {
//        return USB_ERROR;
//    }
//}

//uint8_t usbfs_kb_check_send()
//{
//    if (USBFS_Endp_Busy[ENDP1] == FALSE) {
//        return USB_SUCCESS;
//    } else {
//        return USB_ERROR;
//    }
//}

//uint8_t usbd_kb_check_recev()
//{
//    //    hid_kb_handler *hid = (hid_kb_handler *)udev->dev.class_data[USBD_INF_KB];
//    //
//    //    if (1U == hid->receive_flag) {
//    //        return USBD_OK;
//    //    }
//    //
////        return USBD_BUSY;
////    if (Endp1Busy == FALSE) {
//        return USB_SUCCESS;
////    } else {
////        return USB_ERROR;
////    }
//}