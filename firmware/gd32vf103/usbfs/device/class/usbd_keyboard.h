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

#define USBD_CONFIG_DESC_SIZE_KB (USB_CFG_DESC_LEN + USB_ITF_DESC_LEN + USB_HID_DESC_LEN + USB_EP_DESC_LEN * 2)
#define USBD_REPORT_DESC_SIZE_KB 0x33
#define USBD_REPORT_BYTE_KB 12
#define USBD_REPORT_4BYTE_KB (USBD_REPORT_BYTE_KB / 4)
#define USBD_REPORT_RECEV_SIZE_KB 12

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
const uint8_t USBD_KB_REPORT_DESC[USBD_REPORT_DESC_SIZE_KB];

uint8_t *kb_report;
uint32_t kb_report_usbd[USBD_REPORT_4BYTE_KB], kb_report_usbhd[USBD_REPORT_4BYTE_KB], kb_report_usbh[USBD_REPORT_4BYTE_KB], kb_report_empty[USBD_REPORT_4BYTE_KB];
uint8_t kb_report_recev[USBD_REPORT_RECEV_SIZE_KB];

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

enum kb_repert_map {
    KEY_LEFT_CONTROL = (uint8_t)0x00,
    KEY_LEFT_SHIFT,
    KEY_LEFT_ALT,
    KEY_LEFT_GUI,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_ALT,
    KEY_RIGHT_GUI,

    KEY_NONE,  // 0x08
    KEY_ERRORROLLOVER,
    KEY_POSTFAIL,
    KEY_ERRORUNDEFINED,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1_EXCLAMATION_MARK,
    KEY_2_AT,
    KEY_3_NUMBER_SIGN,
    KEY_4_DOLLAR,
    KEY_5_PERCENT,
    KEY_6_CARET,
    KEY_7_AMPERSAND,
    KEY_8_ASTERISK,
    KEY_9_OPARENTHESIS,
    KEY_0_CPARENTHESIS,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACEBAR,
    KEY_MINUS_UNDERSCORE,
    KEY_EQUAL_PLUS,
    KEY_OBRACKET_AND_OBRACE,
    KEY_CBRACKET_AND_CBRACE,
    KEY_BACKSLASH_VERTICAL_BAR,
    KEY_NONUS_NUMBER_SIGN_TILDE,
    KEY_SEMICOLON_COLON,
    KEY_SINGLE_AND_DOUBLE_QUOTE,
    KEY_GRAVE_ACCENT_AND_TILDE,
    KEY_COMMA_AND_LESS,
    KEY_DOT_GREATER,
    KEY_SLASH_QUESTION,
    KEY_CAPS_LOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINTSCREEN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGEDOWN,
    KEY_RIGHTARROW,
    KEY_LEFTARROW,
    KEY_DOWNARROW,
    KEY_UPARROW,  // 0x5a

    KEY_KEYPAD_NUM_LOCK_AND_CLEAR,
    KEY_KEYPAD_SLASH,
    KEY_KEYPAD_ASTERIKS,
    KEY_KEYPAD_MINUS,
    KEY_KEYPAD_PLUS,
    KEY_KEYPAD_ENTER,

    KEY_KEYPAD_1_END,
    KEY_KEYPAD_2_DOWN_ARROW,
    KEY_KEYPAD_3_PAGEDN,
    KEY_KEYPAD_4_LEFT_ARROW,
    KEY_KEYPAD_5,
    KEY_KEYPAD_6_RIGHT_ARROW,
    KEY_KEYPAD_7_HOME,
    KEY_KEYPAD_8_UP_ARROW,
    KEY_KEYPAD_9_PAGEUP,
    KEY_KEYPAD_0_INSERT,
    KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE,
    KEY_NONUS_BACK_SLASH_VERTICAL_BAR,
    KEY_APPLICATION,
    KEY_POWER,
    KEY_KEYPAD_EQUAL,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_EXECUTE,
    KEY_HELP,
    KEY_MENU,
    KEY_SELECT,
    KEY_STOP,
    KEY_AGAIN,
    KEY_UNDO,
    KEY_CUT,
    KEY_COPY,
    KEY_PASTE,
    KEY_FIND,
    KEY_MUTE,
    KEY_VOLUME_UP,
    KEY_VOLUME_DOWN,
    KEY_LOCKING_CAPS_LOCK,
    KEY_LOCKING_NUM_LOCK,
    KEY_LOCKING_SCROLL_LOCK,
    KEY_KEYPAD_COMMA,
    KEY_KEYPAD_EQUAL_SIGN,
    KEY_INTERNATIONAL1,
    KEY_INTERNATIONAL2,
    KEY_INTERNATIONAL3,
    KEY_INTERNATIONAL4,
    KEY_INTERNATIONAL5,
    KEY_INTERNATIONAL6,
    KEY_INTERNATIONAL7,
    KEY_INTERNATIONAL8,
    KEY_INTERNATIONAL9,
    KEY_LANG1,
    KEY_LANG2,
    KEY_LANG3,
    KEY_LANG4,
    KEY_LANG5,
    KEY_LANG6,
    KEY_LANG7,
    KEY_LANG8,
    KEY_LANG9,
    KEY_ALTERNATE_ERASE,
    KEY_SYSREQ,
    KEY_CANCEL,
    KEY_CLEAR,
    KEY_PRIOR,
    KEY_RETURN,
    KEY_SEPARATOR,
    KEY_OUT,
    KEY_OPER,
    KEY_CLEAR_AGAIN,
    KEY_CRSEL,
    KEY_EXSEL,
    KEY_KEYPAD_00,
    KEY_KEYPAD_000,
    KEY_THOUSANDS_SEPARATOR,
    KEY_DECIMAL_SEPARATOR,
    KEY_CURRENCY_UNIT,
    KEY_CURRENCY_SUB_UNIT,
    KEY_KEYPAD_OPARENTHESIS,
    KEY_KEYPAD_CPARENTHESIS,
    KEY_KEYPAD_OBRACE,
    KEY_KEYPAD_CBRACE,
    KEY_KEYPAD_TAB,
    KEY_KEYPAD_BACKSPACE,
    KEY_KEYPAD_A,
    KEY_KEYPAD_B,
    KEY_KEYPAD_C,
    KEY_KEYPAD_D,
    KEY_KEYPAD_E,
    KEY_KEYPAD_F,
    KEY_KEYPAD_XOR,
    KEY_KEYPAD_CARET,
    KEY_KEYPAD_PERCENT,
    KEY_KEYPAD_LESS,
    KEY_KEYPAD_GREATER,
    KEY_KEYPAD_AMPERSAND,
    KEY_KEYPAD_LOGICAL_AND,
    KEY_KEYPAD_VERTICAL_BAR,
    KEY_KEYPAD_LOGIACL_OR,
    KEY_KEYPAD_COLON,
    KEY_KEYPAD_NUMBER_SIGN,
    KEY_KEYPAD_SPACE,
    KEY_KEYPAD_AT,
    KEY_KEYPAD_EXCLAMATION_MARK,
    KEY_KEYPAD_MEMORY_STORE,
    KEY_KEYPAD_MEMORY_RECALL,
    KEY_KEYPAD_MEMORY_CLEAR,
    KEY_KEYPAD_MEMORY_ADD,
    KEY_KEYPAD_MEMORY_SUBTRACT,
    KEY_KEYPAD_MEMORY_MULTIPLY,
    KEY_KEYPAD_MEMORY_DIVIDE,
    KEY_KEYPAD_PLUSMINUS,
    KEY_KEYPAD_CLEAR,
    KEY_KEYPAD_CLEAR_ENTRY,
    KEY_KEYPAD_BINARY,
    KEY_KEYPAD_OCTAL,
    KEY_KEYPAD_DECIMAL,
    KEY_KEYPAD_HEXADECIMAL, // 0xd9

    KEY_FN = (uint8_t)0xFF,
};

enum led_report_map {
    LED_NONE = (uint8_t)0x00,
    LED_NUM_LOCK,
    LED_CAPS_LOCK,
    LED_SCROLL_LOCK,
    LED_COMPOSE,
    LED_KANA,
    LED_POWER,
    LED_SHIFT,
};

#endif /* __USBD_KEYBOARD_CORE_H */
