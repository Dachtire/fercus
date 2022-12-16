#ifndef __KEYBOARD_H
#define __KEYBOARD_H

//#include "usb_conf.h"
//#include "main.h"
//#include "gd32vf103_it.h"
//#include "gd32vf103.h"
#include "debug.h"
#include "usb_type.h"
#include "app.h"
#include "app_km.h"
//#include "usbd_hid_cntlr.h"
#include "usbd_composite.h"
//#include "usb.h"
//#include "usbd_conf.h"

#define KB_LYR_NUM 4
#define KB_ROW_NUM 6
#define KB_COL_NUM 7

#define KB_ROW_GPIO_PORT  GPIOA
#define KB_ROW_0_GPIO_PIN GPIO_Pin_0
#define KB_ROW_1_GPIO_PIN GPIO_Pin_1
#define KB_ROW_2_GPIO_PIN GPIO_Pin_2
#define KB_ROW_3_GPIO_PIN GPIO_Pin_3
#define KB_ROW_4_GPIO_PIN GPIO_Pin_4
#define KB_ROW_5_GPIO_PIN GPIO_Pin_5

#define KB_COL_0_GPIO_PIN GPIO_Pin_10
#define KB_COL_0_GPIO_PORT GPIOB
#define KB_COL_1_GPIO_PIN GPIO_Pin_11
#define KB_COL_1_GPIO_PORT GPIOB
#define KB_COL_2_GPIO_PIN GPIO_Pin_12
#define KB_COL_2_GPIO_PORT GPIOB
#define KB_COL_3_GPIO_PIN GPIO_Pin_13
#define KB_COL_3_GPIO_PORT GPIOB
#define KB_COL_4_GPIO_PIN GPIO_Pin_14
#define KB_COL_4_GPIO_PORT GPIOB
#define KB_COL_5_GPIO_PIN GPIO_Pin_15
#define KB_COL_5_GPIO_PORT GPIOB
#define KB_COL_6_GPIO_PIN GPIO_Pin_8
#define KB_COL_6_GPIO_PORT GPIOA

#define JS_AXIS_NUM 4
#define JS_NUM 2

#define JS0_A1_GPIO_PIN GPIO_Pin_6
#define JS0_A1_GPIO_PORT GPIOA
#define JS0_A2_GPIO_PIN GPIO_Pin_7
#define JS0_A2_GPIO_PORT GPIOA
#define JS1_A1_GPIO_PIN GPIO_Pin_0
#define JS1_A1_GPIO_PORT GPIOB
#define JS1_A2_GPIO_PIN GPIO_Pin_1
#define JS1_A2_GPIO_PORT GPIOB

#define JS0_SW_GPIO_PIN GPIO_Pin_13
#define JS0_SW_GPIO_PORT GPIOA
#define JS1_SW_GPIO_PIN GPIO_Pin_14
#define JS1_SW_GPIO_PORT GPIOA

const uint16_t KB_ROW_GPIO_PIN[KB_ROW_NUM], KB_COL_GPIO_PIN[KB_COL_NUM], JS_AXIS_GPIO_PIN[JS_AXIS_NUM];
GPIO_TypeDef* const KB_COL_GPIO_PORT[KB_COL_NUM];
GPIO_TypeDef* const JS_AXIS_GPIO_PORT[JS_AXIS_NUM];

#define KB_SIDE_LEFT 0
#define KB_SIDE_RIGHT 1
//#define KB_SIDE KB_SIDE_LEFT
#define KB_SIDE KB_SIDE_RIGHT
//#define KB_REPEAT_NONE
//#define KB_MODE_ADC
#define KB_REPEAT_SLOW_DELAY 2000
#define KB_REPEAT_SLOW_RATE 30

#define BIT(x)                       0x01U<<(x)

//#define KB_CTL_KEYBOARD BIT(1)
//#define KB_CTL_MOUSE BIT(2)
//#define KB_CTL_CNTLR BIT(3)
//#define KB_CTL_ADC BIT(4)

//#define KB_CTL_REPEAT BIT(8)
//#define KB_CTL_REPEAT_SLOW BIT(9)

//#define KB_CTL_LED BIT(1)
#define KB_CTL_USBD          BIT(2)
#define KB_CTL_HOST          BIT(3)
#define KB_CTL_USART BIT(4)
//#define KB_CTL_USBFS_D          BIT(20)
//#define KB_CTL_USBFS_H          BIT(21)

#define KB_RELESE ((bool)0)
#define KB_PRESS ((bool)1)

enum kb_fn_flag {
    kb_fn_none = (uint8_t)0,
    kb_fn_lyr,
    kb_fn_ctl,
    kb_fn_led,
    kb_fn_uart,
    kb_fn_ms,
    kb_fn_usb,
};

#define KB_FLAG_REPEAT BIT(1)
#define KB_FLAG_COUNT BIT(2)
#define KB_FLAG_FN BIT(3)
//#define KB_FLAG_REPEAT_SLOW BIT(2)
//#define KB_FLAG_DEBUG BIT(2)



void kb_remap(uint8_t lyr);
//void kb_usb_buf_handler();
void kb_usb_send();
void kb_fn_handler();
void kb_init_sync();
void kb_init();
void kb_enable_usbd();
void kb_polling(/*uint8_t col*/);
void kb_usart_polling();
void kb_it();
void kb_uart_init();
void kb_adc_it();
void kb_usart_debug();
void kb_usbd_test(uint8_t data, uint16_t length);
void kb_adc_time();
void kb_usbd_hid_test();
void kb_usbhd_combine();
void kb_row_adc_diff();
void kb_row_adc_trigger();

static uint8_t kb_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM], kb_cntlr_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM];

uint8_t *kb_usb_buf;
//extern *usb_hid_cntlr_buf;
uint8_t kb_report_usbd[USBD_REPORT_SIZE_KB], kb_report_usbhd[USBD_REPORT_SIZE_KB], kb_report_usbh[USBD_REPORT_SIZE_KB];
uint8_t kb_report_recev[USBD_KB_RECEV_SIZE], kb_report_empty[USBD_REPORT_SIZE_KB];
//struct cntlr_buf_type {
//    uint16_t button;
//    int8_t stick[4];
//};
//extern struct cntlr_buf_type cntlr_buf;
//uint8_t cntlr_report[USBD_REPORT_SIZE_CNTLR];
//uint8_t mouse_report[USBD_REPORT_SIZE_MOUSE];
uint8_t kb_col_num, kb_row_num;
uint8_t (*kb_layout)[KB_COL_NUM];
bool kb_key_state[KB_ROW_NUM][KB_COL_NUM];
uint32_t kb_flag;
extern uint8_t kb_key_count;
uint32_t kb_ctl;
uint8_t kb_repeat, kb_device, kb_usb;
uint16_t kb_row_adc[KB_ROW_NUM], js_axis_adc[JS_NUM];


#define KB_ADC_SIZE (1)
#define KB_ADC_LEN (KB_ADC_SIZE * 2)
uint16_t kb_adc_value[KB_ADC_SIZE];

enum kb_repeat {
    KB_REPEAT_NONE,
    KB_REPEAT_FAST,
    KB_REPEAT_SLOW
};

enum kb_device {
    KB_DEVICE_KEYBORAD,
    KB_DEVICE_MOUSE,
    KB_DEVICE_CNTLR,
    KB_DEVICE_COMPOSITE,
    KB_DEVICE_VENDOR,
    KB_DEVICE_KEYBOARD_ADC_DIFF,
    KB_DEVICE_KEYBOARD_ADC_TRIGGER
};

//enum kb_usb {
//    KB_USBD_DEVICE,
//    KB_USBFS_DEVICE
//};

enum kb_ctl_option {
    KB_CTL_LYR_0 = (uint8_t)0x80,
    KB_CTL_LYR_1,
    KB_CTL_LYR_2,
    KB_CTL_LYR_3,
    KB_CTL_KB_OFF = (uint8_t)0xc0,
    KB_CTL_KB_ON,
    KB_CTL_REPEAT_OFF = 0xe0,
    KB_CTL_REPEAT_ON,
    KB_CTL_ADC_OFF = 0x10,
    KB_CTL_ADC_ON = 0x11,
    KB_CTL_USBD_ON,
    KB_CTL_USBD_OFF,
    KB_CTL_SYSCLK
};

enum kb_led_report_hid {
    LED_NONE = (uint8_t)0x00,
    LED_NUM_LOCK,
    LED_CAPS_LOCK,
    LED_SCROLL_LOCK,
    LED_COMPOSE,
    LED_KANA,
    LED_POWER,
    LED_SHIFT,
};

#define MOUSE_REPORT_POS 10
enum usbd_repert_mouse_set {
    MOUSE_BUTTON_1 = (uint8_t) 0x00,
    MOUSE_BUTTON_2,
    MOUSE_BUTTON_3,
    MOUSE_BUTTON_4,
    MOUSE_BUTTON_5,
    MOUSE_BUTTON_6,
    MOUSE_BUTTON_7,
    MOUSE_BUTTON_8,

    MOUSE_X_NEG,
    MOUSE_X_POS,
    MOUSE_Y_NEG,
    MOUSE_Y_POS,

    MOUSE_WHEEL_NEG,
    MOUSE_WHEEL_POS,

    MOUSE_NONE = 0xff
};

#endif /* __KEYBOARD_H */