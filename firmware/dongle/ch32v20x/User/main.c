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
#include "HAL.h"
#include "RF_PHY.h"
#include "config.h"
#include "tmos-usb.h"
//#include "hiddev.h"
//#include "hidkbd.h"
//#include "rf_dev.h"
//#include "rf_dongle.h"
//#include "rf_sync.h"

/* Global define */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation(void)
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
    PRINT("%s\n", VER_LIB);
//    printf("SystemClk:%d\r\n",SystemCoreClock);
//        printf("USBD Keyboard&Mouse Demo\r\n");

//    Set_USBConfig();
//    USB_Init();
//    USB_Interrupts_Config();
    //    if( bDeviceState == CONFIGURED ) {
    //        kb_usb = KB_USBD_DEVICE;

    /* Initialize USBFS host */
//    #if DEF_USBFS_PORT_EN
//        DUG_PRINTF("USBFS Host Init\r\n");
//        USBFS_RCC_Init();
//        USBFS_Host_Init(ENABLE);
//        memset(&RootHubDev.bStatus, 0, sizeof(ROOT_HUB_DEVICE));
//        memset(&HostCtl[DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL].InterfaceNum, 0, sizeof(HOST_CTL));
//    #endif
    //    } else {
    //        /* Initialize USBHD interface to communicate with the host  */
    //        USBFS_RCC_Init( );
    //        USBFS_Device_Init( ENABLE );
//            USB_Sleep_Wakeup_CFG( );
    //        if (USBFS_DevEnumStatus) {
    //            kb_usb = KB_USBFS_DEVICE;
    //        }
    //    }

    WCHBLE_Init();
    HAL_Init();

    USB_Task_Init();

//    GAPRole_PeripheralInit();
    //    ble
//    HidDev_Init();
//    HidEmu_Init();

    //    rf
    RF_RoleInit();

    RF_Init();

//    rf_dongle_init();
//    rf_dev_init();

    Main_Circulation();
}