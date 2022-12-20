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

#ifndef __HID_CNTLR_CORE_H
#define __HID_CNTLR_CORE_H

#include "usb_hid.h"
#include "usbd_conf.h"
#include "usb_lib.h"

//#define HID_CNTLR_CONFIG_DESC_LEN          USB_HID_CONFIG_DESC_LEN
#define USBD_REPORT_DESC_SIZE_CNTLR        0x2f
#define USBD_REPORT_SIZE_CNTLR 18

#define CNTLR_AXIS_MIN  0
#define CNTLR_AXIS_MAX  (1024 - 2)
#define CNTLR_AXIS_HALF (CNTLR_AXIS_MAX / 2)

#define NO_CMD                           0xFFU

const uint8_t USBD_REPORT_DESC_CNTLR[USBD_REPORT_DESC_SIZE_CNTLR];
//uint8_t cntlr_report[USBD_REPORT_SIZE_CNTLR];

//typedef struct {
//    uint32_t protocol;
//    uint32_t idle_state;
//
//    uint8_t data_in[HID_CNTLR_IN_PACKET];
//    uint8_t data_out[HID_CNTLR_IN_PACKET];
//    __IO uint8_t prev_transfer_complete;
//} hid_cntlr_handler;

//typedef struct {
//    void (*hid_itf_config) (void);
//    void (*hid_itf_data_process) (usb_dev *udev);
//} hid_cntlr_fop_handler;

//extern usb_desc hid_cntlr_desc;
//extern usb_class_core hid_cntlr_cb;

/* function declarations */
/* register HID interface operation functions */
//uint8_t hid_cntlr_itfop_register (usb_dev *udev, hid_cntlr_fop_handler *hid_fop);
/* send keyboard report */
//uint8_t hid_cntlr_report_send (usb_dev *udev, uint8_t *report, uint32_t len);

__attribute__((optimize("O0"))) void usbd_cntlr_report_send(uint8_t *report/*, uint32_t len*/);
__attribute__((optimize("O0"))) uint8_t usbd_cntlr_report_receive();
__attribute__((optimize("O0"))) uint8_t usbd_cntlr_check_send();
__attribute__((optimize("O0"))) uint8_t usbd_cntlr_check_recev();

#define USBD_REPORT_SIZE_CNTLR_BUTTON 5

struct _cntlr_report {
    uint16_t button[USBD_REPORT_SIZE_CNTLR_BUTTON];
    uint16_t axis[4];
}cntlr_report;

enum cntlr_report_map {
    CNTLR_BUTTON_1 = (uint8_t) 0x00,
    CNTLR_BUTTON_2,
    CNTLR_BUTTON_3,
    CNTLR_BUTTON_4,
    CNTLR_BUTTON_5,
    CNTLR_BUTTON_6,
    CNTLR_BUTTON_7,
    CNTLR_BUTTON_8,

    CNTLR_BUTTON_9,
    CNTLR_BUTTON_10,
    CNTLR_BUTTON_11,
    CNTLR_BUTTON_12,
    CNTLR_BUTTON_13,
    CNTLR_BUTTON_14,
    CNTLR_BUTTON_15,
    CNTLR_BUTTON_16,

    CNTLR_LEFT_STICK_X_NEG = 0x58,
    CNTLR_LEFT_STICK_X_POS,

    CNTLR_LEFT_STICK_Y_NEG,
    CNTLR_LEFT_STICK_Y_POS,

    CNTLR_RIGHT_STICK_X_NEG,
    CNTLR_RIGHT_STICK_X_POS,

    CNTLR_RIGHT_STICK_Y_NEG,
    CNTLR_RIGHT_STICK_Y_POS,

};

enum cntlr_report_xbox_map {
    CNTLR_A = (uint8_t) 0x00,
    CNTLR_B,
    CNTLR_X,
    CNTLR_Y,
    CNTLR_LEFT_BUMPER,
    CNTLR_RIGHT_BUMPER,
    CNTLR_LEFT_TRIGGER,
    CNTLR_RIGHT_TRIGGER,

    CNTLR_BACK,
    CNTLR_START,
    CNTLR_LEFT_STICK_BUTTON,
    CNTLR_RIGHT_STICK_BUTTON,
    CNTLR_DPAD_UP,
    CNTLR_DPAD_DOWN,
    CNTLR_DPAD_LEFT,
    CNTLR_DPAD_RIGHT,

    CNTLR_LEFT_STICK_LEFT,
    CNTLR_LEFT_STICK_RIGHT,
    CNTLR_LEFT_STICK_UP,
    CNTLR_LEFT_STICK_DOWN,
    CNTLR_RIGHT_STICK_LEFT,
    CNTLR_RIGHT_STICK_RIGHT,
    CNTLR_RIGHT_STICK_UP,
    CNTLR_RIGHT_STICK_DOWN,

    CNTLR_NONE = 0xff,
};

#endif /* __HID_CNTLR_CORE_H */
