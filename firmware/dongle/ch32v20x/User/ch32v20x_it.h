/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_it.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains the headers of the interrupt handlers.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V20x_IT_H
#define __CH32V20x_IT_H

#include "debug.h"

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI15_10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void PVD_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#endif /* __CH32V20x_IT_H */


