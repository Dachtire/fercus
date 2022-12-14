/********************************** (C) COPYRIGHT *******************************
 * File Name          : usbd_composite_km.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/07/04
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/


#ifndef __USBD_COMPOSITE_KM_H
#define __USBD_COMPOSITE_KM_H

/*******************************************************************************/
/* Included Header Files */
#include "debug.h"
#include "string.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_prop.h"
#include "usb_pwr.h"
/*******************************************************************************/
/* Keyboard Key Value Macro Definition */
#define DEF_KEY_CHAR_W              0x1A                                        /* "W" */
#define DEF_KEY_CHAR_A              0x04                                        /* "A" */
#define DEF_KEY_CHAR_S              0x16                                        /* "S" */
#define DEF_KEY_CHAR_D              0x07                                        /* "D" */

/*******************************************************************************/
/* Global Variable Declaration */
extern volatile uint8_t  KB_LED_Cur_Status;
/*******************************************************************************/
/* Function Declaration */
extern void TIM3_Init( uint16_t arr, uint16_t psc );
extern void USART2_Init( uint32_t baudrate );
extern void USART2_Receive_Handle( void );
extern void KB_Scan_Init( void );
extern void KB_Sleep_Wakeup_Cfg( void );
extern void KB_Scan( void );
extern void KB_Scan_Handle( void );
extern void MS_Scan_Init( void );
extern void MS_Sleep_Wakeup_Cfg( void );
extern void MS_Scan( void );
extern void MS_Scan_Handle( void );
extern void KB_LED_Handle( void );
extern void MCU_Sleep_Wakeup_Operate( void );
#endif
