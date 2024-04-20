/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 

/*
 * @Note
 * Composite Keyboard and Mouse Example:
 * This example uses PA4-PA7 and PB12-PB15 to simulate mouse movement and keyboard
 * key pressing respectively, active low. At the same time, it also uses USART2
 * to receive data sent from the host to simulate keyboard key pressing and releasing.
 *
 */

#include "main.h"
#include "config.h"
#include "tmos-connection-mode.h"
#include "tmos-power-manager.h"
//#include "rf_sync.h"
//#include "device_config.h"

/* Global define */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

__attribute__((section(".highcode")))
__attribute__((noinline))
void tmos_Circulation(void)
{
    while(1)
    {
//        rf_sync();
        TMOS_SystemProcess();
    }
}
/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();

    #ifdef DEBUG
        USART_Printf_Init( 115200 );
    #endif
    PRINT("start.%s\n",__TIME__);
//    PRINT("%s\n", VER_LIB);
//    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
//    printf("SystemClk:%d\r\n",SystemCoreClock);

//    connection_mode_init(CONN_USB);
//    while (1) {}

    connection_mode = CONN_TMOS_USB;
    connection_mode_init(connection_mode);
    tmos_Circulation();
}