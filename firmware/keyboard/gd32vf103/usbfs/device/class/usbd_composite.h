/*!
    \file    hid_printer_wrapper.h
    \brief   header file for the hid_printer_wrapper.c file

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

#ifndef USB_COMPOSITE_H
#define USB_COMPOSITE_H

#include "usbd_enum.h"
#include "usbd-hid-keyboard.h"
#include "usbd_hid_cntlr.h"
#include "usbd_hid_mouse.h"
#include "usbd-hid-compatibility.h"
#include "usbd-hid-simulation.h"
//#include "cdc_acm_core.h"

#define USBD_COMPOSITE_CONFIG_DESC_SIZE (USB_CFG_DESC_LEN + 4 * (USB_ITF_DESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN * 2))

typedef struct
{
    usb_desc_config config;

    usb_desc_itf kb_inf;
    usb_desc_hid kb_hid;
    usb_desc_ep kb_epin;
    usb_desc_ep kb_epout;

    usb_desc_itf cntlr_inf;
    usb_desc_hid cntlr_hid;
    usb_desc_ep cntlr_epin;
    usb_desc_ep cntlr_epout;

    usb_desc_itf mouse_inf;
    usb_desc_hid mouse_hid;
    usb_desc_ep mouse_epin;
    usb_desc_ep mouse_epout;

//    usb_desc_itf sim_inf;
//    usb_desc_hid sim_hid;
//    usb_desc_ep sim_epin;
//    usb_desc_ep sim_epout;
    
    usb_desc_itf comp_inf;
    usb_desc_hid comp_hid;
    usb_desc_ep comp_epin;
    usb_desc_ep comp_epout;
} usbd_composite_desc_config_set;

extern const usb_desc_dev usbd_composite_dev_desc;
extern const usbd_composite_desc_config_set usbd_composite_config_desc;

extern const usb_desc_LANGID usbd_language_id_desc;
extern const usb_desc_str manufacturer_string;
extern const usb_desc_str product_string;
extern const usb_desc_str serial_string;

//extern usb_desc usb_composite_desc;
//extern usb_class_core usb_composite_cb;

//extern usb_class_core hid_kb_cb;
//extern usb_class_core hid_mouse_cb;
//extern usb_class_core usb

//typedef struct {
//    uint32_t protocol;
//    uint32_t idle_state;
//
//    uint8_t data_in[HID_IN_PACKET];
//    uint8_t data_out[HID_OUT_PACKET];
//    __IO uint8_t prev_transfer_complete;
//} hid_composite_handler;

//typedef struct {
//    void (*hid_itf_config) (void);
//    void (*hid_itf_data_process) (usb_dev *udev);
//} hid_composite_fop_handler;

/* function declarations */
/* register HID interface operation functions */
//uint8_t hid_composite_itfop_register (usb_dev *udev, hid_composite_fop_handler *hid_fop);
/* send keyboard report */
//uint8_t hid_composite_report_send (usb_dev *pudev, uint8_t *report, uint32_t len);


#endif //USB_COMPOSITE_H
