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

#ifndef __USBD_KEYBOARD_CORE_H
#define __USBD_KEYBOARD_CORE_H

//#include "usbd_enum.h"
#include "usb_hid.h"
#include "keyboard.h"
#include "usbd_conf.h"
//#include "ch32v20x.h"

//#define USBD_KB_EP0_MAX_PACKET 0x40

#define USBD_KB_CONFIG_DESC_SIZE (USB_CFG_DESC_LEN + USB_ITF_DESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN * 2)
#define USBD_KB_REPORT_DESC_SIZE 0x33U

#define NO_CMD                           0xFFU

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

const usb_desc_dev USBD_KB_DEV_DESC;
const usb_hid_desc_config_set USBD_KB_CONFIG_DESC;
const uint8_t USBD_KB_REPORT_DESC[USBD_KB_REPORT_DESC_SIZE];

///* function declarations */
///* register HID interface operation functions */
//uint8_t hid_kb_itfop_register (usb_dev *udev, hid_kb_fop_handler *hid_fop);
///* send keyboard report */
//uint8_t hid_kb_report_send (usb_dev *pudev, uint8_t *report, uint32_t len);
//uint8_t hid_kb_report_receive (usb_dev *udev);
//uint8_t hid_kb_check_send(usb_dev *udev);
//uint8_t hid_kb_check_recev(usb_dev *udev);

__attribute__((optimize("O0"))) void usbd_kb_report_send(uint8_t *report/*, uint32_t len*/);
__attribute__((optimize("O0"))) uint8_t usbd_kb_report_receive();
__attribute__((optimize("O0"))) uint8_t usbd_kb_check_send();
__attribute__((optimize("O0"))) uint8_t usbd_kb_check_recev();

#endif /* __USBD_KEYBOARD_CORE_H */
