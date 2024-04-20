#ifndef FIRMWARE_ETA9184_H
#define FIRMWARE_ETA9184_H

#include "ch32v20x.h"

#define ETA_DISCHRG_PORT GPIOB
#define ETA_DISCHRG_PIN GPIO_Pin_9
#define ETA_DISCHRG_DISABLE 1
#define ETA_PULSE_PORT GPIOB
#define ETA_PULSE_PIN GPIO_Pin_8
#define ETA_BAT_PORT GPIOB
#define ETA_BAT_PIN GPIO_Pin_1
#define ETA_STAT_PORT GPIOA
#define ETA_STAT_PIN GPIO_Pin_10

//#define ETA9184_BOOST_VOLTAGE 3103 // 3196

#define USB_VBUS_PIN GPIO_Pin_15
#define USB_VBUS_PORT GPIOA

void eta9184_gpio_init();
void eta9184_pulse_it_deinit();
void eta9184_pulse_tim_init();
void eta9184_pulse_it_init();
void eta9184_dischrg_exti_init();
void eta9184_adc_init();
uint16_t eta9184_adc_get();

void eta9184_vbus_gpio_init();
void eta9184_vbus_exti_init();
void eta9184_vbus_exti_event_init();

#endif//FIRMWARE_ETA9184_H
