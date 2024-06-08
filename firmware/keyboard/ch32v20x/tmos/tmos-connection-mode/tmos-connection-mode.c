/*
 * Copyright (c) 2022 Nanjing Qinheng Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tmos-connection-mode.h"
#include "HAL.h"
//#include "device_config.h"
#include "app.h"
#include "ble-hid-keyboard.h"
#include "hiddev.h"
#include "rf-phy.h"
#include "tmos-keyboard.h"
#include "tmos-usb.h"

uint8_t tmos_connection_mode_taskid = 0;
static uint8_t connection_mode = 0;

uint16_t tmos_connection_mode_event(uint8_t task_id, uint16_t event)
{
    
    if (event & CONNCETION_MODE_SELECT_EVENT) {

        connection_mode_init(connection_mode);

        /* Must return 0 */
        return 0;
    }

    return 0;
}

void tmos_connection_mode_init(void)
{
    tmos_connection_mode_taskid = TMOS_ProcessEventRegister(tmos_connection_mode_event);
}

void tmos_connection_mode_select(uint8_t mod)
{
    connection_mode = mod;

    hid_emu_disconnet();

    /* Wait for ble disconnet */
    tmos_start_task(tmos_connection_mode_taskid, CONNCETION_MODE_SELECT_EVENT,
            MS1_TO_SYSTEM_TIME(500));
}

void connection_mode_init(uint8_t connection) {
    while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == KB_FN_PRESS);

    tmos_connection_mode_init();
    switch (connection) {
        default:
        case CONN_USB:
//            eta_gpio_init();
//            eta_dischrg_exti_init();

            kb_fn_gpio_init();
//            kb_fn_exti_init();

            kb_col_gpio_init();
            kb_row_gpio_init();

            Set_USBConfig();
            USB_Init();
            USB_Interrupts_Config();

            kb_digtal_analog_select();
//            TIM1_Init();
            kb_enable_usbd();
            break;

        case CONN_TMOS_USB:
            WCHBLE_Init();
            HAL_Init();
            USB_Task_Init();
            tmos_keyboard_init();
            kb_digtal_analog_select();
            kb_enable_usbd();
            break;

        case CONN_TMOS_USBFS:
            WCHBLE_Init();
            HAL_Init();
            USBFS_Task_Init();
            tmos_keyboard_init();
            kb_digtal_analog_select();
            kb_enable_usbd();
            break;

        case CONN_RF:
            PRINT("CONN_RF\n");
            WCHBLE_Init();
            HAL_Init();
            RF_RoleInit();
            RF_Init();
            tmos_keyboard_init();
            //            rf_dev_init();
            break;

        case CONN_BLE:
            PRINT("CONN_BLE\n");
            WCHBLE_Init();
            HAL_Init();
            GAPRole_PeripheralInit();
            HidDev_Init();
            HidEmu_Init();
            tmos_keyboard_init();
            break;

        case CONN_TSET:
            //            test_dtm_usb_init();
            break;
    }

//    GPIO_ResetBits(LED_G_PORT, LED_G_PIN);
//    Delay_Ms(500);
//    GPIO_SetBits(LED_G_PORT, LED_G_PIN);
}