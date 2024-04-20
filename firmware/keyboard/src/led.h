#ifndef FIRMWARE_LED_H
#define FIRMWARE_LED_H

#define LED_R_PORT GPIOB
#define LED_R_PIN GPIO_Pin_3
#define LED_G_PORT GPIOB
#define LED_G_PIN GPIO_Pin_4
#define LED_B_PORT GPIOB
#define LED_B_PIN GPIO_Pin_5

#include "ch32v20x.h"

void led_gpio_init();
void led_tim_init(u16 arr, u16 psc, u16 ccp, TIM_TypeDef *tim);
void led_red_on();
void led_red_off();
void led_green_on();
void led_green_off();
void led_blue_on();
void led_blue_off();

#endif//FIRMWARE_LED_H
