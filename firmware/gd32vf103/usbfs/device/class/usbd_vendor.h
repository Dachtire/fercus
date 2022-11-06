/*!
    \file    standard_hid_core.h
    \brief   definitions for HID core

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

#ifndef __USBD_VENDOR_CORE_H
#define __USBD_VENDOR_CORE_H

//#include "usbd_enum.h"
#include "usb_hid.h"
#include "keyboard.h"
#include "usbd_conf.h"
//#include "ch32v20x.h"

#define USBD_VENDOR_CONFIG_DESC_SIZE (USB_CFG_DESC_LEN + USB_ITF_DESC_LEN + USB_EP_DESC_LEN * 2)
//#define USBD_VENDOR_REPORT_DESC_SIZE 0x33U

#define USB_VENDOR_SUBCLASS 0x80
#define USB_VENDOR_PROTOCOL 0x55
#define USBD_VPC_EP0_MAX_PACKET 0x40
#define USBD_VPC_EP_MAX_PACKET  0x40
#define USBD_VPC_IN_PACKET      USBD_VPC_EP_MAX_PACKET
#define USBD_VPC_OUT_PACKET     USBD_VPC_EP_MAX_PACKET
//#define USBD_VPC_MAX_PACKET  0x80
#define USBD_VPC_EP_INTERVAL 0x00

#define NO_CMD                           0xFFU

uint16_t mult_length;
uint8_t *mult_ptr;

typedef struct
{
    usb_desc_config         config;
    usb_desc_itf            itf;
    usb_desc_ep             epin1;
    usb_desc_ep             epout1;
//    usb_desc_ep             epin2;
//    usb_desc_ep             epout2;
}usbd_vendor_desc_config_set;

//typedef struct {
//    uint32_t protocol;
//    uint32_t idle_state;
//
//    uint8_t data_in[HID_KB_IN_PACKET];
//    uint8_t data_out[HID_KB_OUT_PACKET];
////    uint8_t prev_transfer_complete;
//    uint8_t sent_flag;
//    uint8_t receive_flag;
//} hid_kb_handler;

//typedef struct {
//    void (*hid_itf_config) (void);
//    void (*hid_itf_data_process) (usb_dev *udev);
//} hid_kb_fop_handler;
//
//hid_kb_fop_handler fop_handler = {
//    .hid_itf_config = key_config,
//    .hid_itf_data_process = hid_key_data_send
//};

//extern usb_desc hid_kb_desc;
//extern usb_class_core hid_kb_cb;

extern const usb_desc_dev USBD_VENDOR_DEV_DESC;
extern const usbd_vendor_desc_config_set USBD_VENDOR_CONFIG_DESC;

///* function declarations */
///* register HID interface operation functions */
//uint8_t hid_kb_itfop_register (usb_dev *udev, hid_kb_fop_handler *hid_fop);
///* send keyboard report */
//uint8_t hid_kb_report_send (usb_dev *pudev, uint8_t *report, uint32_t len);
//uint8_t hid_kb_report_receive (usb_dev *udev);
//uint8_t hid_kb_check_send(usb_dev *udev);
//uint8_t hid_kb_check_recev(usb_dev *udev);

//void usbd_kb_report_send(uint8_t *report/*, uint32_t len*/);
//uint8_t usbd_kb_report_receive();
//uint8_t usbd_kb_check_send();
//uint8_t usbd_kb_check_recev();


__attribute__((optimize("O0"))) void usbd_vendor_send(uint8_t *data, uint16_t length, uint8_t ep_num);
__attribute__((optimize("O0"))) void usbd_vendor_send_mult(uint8_t *data, uint16_t length, uint8_t ep_num);
__attribute__((optimize("O0"))) void usbd_vendor_receive(uint8_t *data, uint8_t ep_num);
__attribute__((optimize("O0"))) uint8_t usbd_vendor_check_send();
#endif /* __USBD_VENDOR_CORE_H */
