#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "debug.h"
#include "usb_type.h"
#include "app.h"
#include "app_km.h"
#include "usbd_composite.h"

#define KB_LYR_NUM 4
#define KB_ROW_NUM 6
#define KB_COL_NUM 7

#define KB_ROW_GPIO_PORT  GPIOA
#define KB_ROW_0_GPIO_PIN GPIO_Pin_5
#define KB_ROW_1_GPIO_PIN GPIO_Pin_4
#define KB_ROW_2_GPIO_PIN GPIO_Pin_3
#define KB_ROW_3_GPIO_PIN GPIO_Pin_2
#define KB_ROW_4_GPIO_PIN GPIO_Pin_1
#define KB_ROW_5_GPIO_PIN GPIO_Pin_0

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

#define KB_FN_0_GPIO_PIN GPIO_Pin_14
#define KB_FN_0_GPIO_PORT GPIOA
#define KB_FN_1_GPIO_PIN GPIO_Pin_13
#define KB_FN_1_GPIO_PORT GPIOA
#define KB_FN_3_GPIO_PIN GPIO_Pin_13
#define KB_FN_3_GPIO_PORT GPIOC
#define KB_FN_2_GPIO_PIN GPIO_Pin_2
#define KB_FN_2_GPIO_PORT GPIOB
#define KB_FN_NUM 3

#define KB_FN_RELESE 0
#define KB_FN_PRESS 1

extern const uint16_t KB_COL_GPIO_PIN[KB_COL_NUM];
extern GPIO_TypeDef* const KB_COL_GPIO_PORT[KB_COL_NUM];

#define KB_SIDE_LEFT 0
#define KB_SIDE_RIGHT 1
#define KB_SIDE KB_SIDE_LEFT
//#define KB_SIDE KB_SIDE_RIGHT

//#define KB_REPEAT_NONE
//#define KB_MODE_ADC
#define KB_REPEAT_SLOW_DELAY 2000
#define KB_REPEAT_SLOW_RATE 30

//#define BIT(x)                       0x01U<<(x)

//#define KB_CTL_KEYBOARD BIT(1)
//#define KB_CTL_MOUSE BIT(2)
//#define KB_CTL_CNTLR BIT(3)
//#define KB_CTL_ADC BIT(4)

//#define KB_CTL_REPEAT BIT(8)
//#define KB_CTL_REPEAT_SLOW BIT(9)

//#define KB_CTL_LED BIT(1)
#define KB_CTL_USBD          BIT(2)
#define KB_CTL_HOST          BIT(3)
//#define KB_CTL_USART BIT(4)
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

void kb_row_gpio_init();
void kb_row_gpio_adc_init();
void kb_adc_dma_init();
void kb_col_gpio_init();
void kb_fn_gpio_init();
void kb_fn_exti_init();
void kb_fn_exti_event_init();

void keyboard_layer_select(uint8_t lyr);
void keyboard_usb_send();
void keyboard_fn_handler();
void kb_digtal_analog_select();
void kb_enable_usbd();
void keyboard_scan_it();
void keyboard_scan_delay();
void keyboard_fn_scan();
void kb_usbhd_combine();
void keyboard_row_read_adc_diff();
void keyboard_row_read_adc_trigger();
void kb_row_adc_cntlr();

void keyboard_row_read();
void keyboard_row_handler();
void keyboard_trigger_handler();

static uint8_t kb_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM], kb_cntlr_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM];

extern uint8_t kb_col_curr, kb_row_curr;
extern uint8_t (*kb_layout)[KB_COL_NUM];
extern bool kb_key_state[KB_ROW_NUM][KB_COL_NUM];
extern uint32_t kb_flag;
extern uint8_t kb_key_count;
extern uint32_t kb_ctl;
static uint8_t kb_repeat, kb_device;
static uint16_t kb_row_adc[KB_ROW_NUM];

#define KB_ADC_SIZE (1)
//#define KB_ADC_LEN (KB_ADC_SIZE * 2)
static uint16_t kb_adc_value[KB_ADC_SIZE];

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
    KB_DEVICE_KEYBOARD_ADC_TRIGGER,
    KB_DEVICE_CNTLR_ADC,
};

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

//#define KB_IT_MULT 3
//#define KB_IT_MULT 5
//#define KB_IT_MULT 6
//#define KB_IT_MULT 1
//#define KB_IT_CASE0 (0 * KB_IT_MULT)
//#define KB_IT_CASE1 (1 * KB_IT_MULT - 1)
//#define KB_IT_CASE2 (2 * KB_IT_MULT - 1)
//#define KB_IT_CASE3 (3 * KB_IT_MULT - 1)
//#define KB_IT_CASE4 (4 * KB_IT_MULT - 1)
//#define KB_IT_CASE5 (5 * KB_IT_MULT - 1)
//#define KB_IT_CASE6 (6 * KB_IT_MULT - 1)
//#define KB_IT_CASE7 (7 * KB_IT_MULT - 1)
//#define KB_IT_CASE8 (8 * KB_IT_MULT - 1)
#define KB_IT_MULT 1
#define KB_IT_CASE0 (0 * KB_IT_MULT)
#define KB_IT_CASE1 (1 * KB_IT_MULT)
#define KB_IT_CASE2 (2 * KB_IT_MULT)
#define KB_IT_CASE3 (3 * KB_IT_MULT)
#define KB_IT_CASE4 (4 * KB_IT_MULT)
#define KB_IT_CASE5 (5 * KB_IT_MULT)
#define KB_IT_CASE6 (6 * KB_IT_MULT)
#define KB_IT_CASE7 (7 * KB_IT_MULT)
#define KB_IT_CASE8 (8 * KB_IT_MULT)

//#define KB_IT_TICK 1  // 5 us fail
//#define KB_IT_TICK 2  // 10 us ok unstable
//#define KB_IT_TICK 3  // 15 us stable
#define KB_IT_TICK 4  // 20 us safe
//#define KB_IT_TICK_ADC (KB_IT_TICK + 10)  // 50 us
#define KB_IT_TICK_ADC (KB_IT_TICK + 9)  // 45 us
//#define KB_IT_TICK_ADC (KB_IT_TICK + 7)  // 35 us min ok

#define KB_PHOTO_DELAY_US 18

#endif /* __KEYBOARD_H */