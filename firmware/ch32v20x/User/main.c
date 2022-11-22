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
/* Global define */

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
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init( 115200 );
//    printf("SystemClk:%d\r\n",SystemCoreClock);
//    printf("USBD Keyboard&Mouse Demo\r\n");

    /* Initialize USART2 for receiving the specified keyboard data */
//    USART2_Init( 115200 );
//    printf( "USART2 Init OK!\r\n" );

    /* Initialize GPIO for keyboard scan */
//    KB_Scan_Init( );
//    KB_Sleep_Wakeup_Cfg( );
//    printf( "KB Scan Init OK!\r\n" );


    /* Initialize GPIO for mouse scan */
//    MS_Scan_Init( );
//    MS_Sleep_Wakeup_Cfg( );
//    printf( "MS Scan Init OK!\r\n" );

    /* Initialize timer for Keyboard and mouse scan timing */
//    TIM3_Init( 1, 7199 );
//    printf( "TIM3 Init OK!\r\n" );

    kb_init();
    gpio_config();
    kb_init_sync();
    TIM1_Init();

    Set_USBConfig();
    USB_Init();
    USB_Interrupts_Config();
//    if( bDeviceState == CONFIGURED ) {
//        KB_USB = KB_USBD_DEVICE;

        /* Initialize TIM3 */
        TIM3_Init( 9, SystemCoreClock / 10000 - 1 );
        DUG_PRINTF( "TIM3 Init OK!\r\n" );

        /* Initialize USBFS host */
        #if DEF_USBFS_PORT_EN
                DUG_PRINTF( "USBFS Host Init\r\n" );
                USBFS_RCC_Init( );
                USBFS_Host_Init( ENABLE );
                memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
                memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
        #endif
//    } else {
//        /* Initialize USBHD interface to communicate with the host  */
//        USBFS_RCC_Init( );
//        USBFS_Device_Init( ENABLE );
//        USB_Sleep_Wakeup_CFG( );
//        if (USBFS_DevEnumStatus) {
//            KB_USB = KB_USBFS_DEVICE;
//        }
//    }

    kb_init_usbd();
//    kb_adc_test3();

    while(1)
    {
        USBH_MainDeal( );

//        if( bDeviceState == CONFIGURED )
//        {
//            /* Handle keyboard scan data */
//            KB_Scan_Handle(  );
//
//            /* Handle keyboard lighting */
//            KB_LED_Handle( );
//
//            /* Handle mouse scan data */
//            MS_Scan_Handle( );
//
//            /* Handle USART2 receiving data */
//            USART2_Receive_Handle( );
//        }
    }
}







