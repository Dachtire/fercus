#ifndef FIRMWARE_JOYSTICK_H
#define FIRMWARE_JOYSTICK_H

#include "ch32v20x.h"

#define JS_AXIS_NUM 2
#define JS_NUM 2

#define JS_A1_GPIO_PIN GPIO_Pin_6
#define JS_A1_GPIO_PORT GPIOA
#define JS_A2_GPIO_PIN GPIO_Pin_7
#define JS_A2_GPIO_PORT GPIOA

#define JS_SW_GPIO_PIN GPIO_Pin_0
#define JS_SW_GPIO_PORT GPIOB

#define JS_SW_PRESS RESET
#define JS_SW_RELESE SET

extern uint16_t js_axis_adc[JS_NUM];

void joystick_gpio_init();
void joystick_adc_dma_init();
void joystick_scan();

#endif//FIRMWARE_JOYSTICK_H
