/*
 * Copyright (c) 2022 zerosensei
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tmos-power-manager.h"
#include "HAL.h"
#include "eta9184.h"
#include "keyboard.h"
#include "led.h"
#include "rf-phy.h"
#include "tmos-keyboard.h"
#include "tmos-usb.h"
#include <stdbool.h>
//#include "device_config.h"
//#include "keyscan.h"
//#include "USB_task/USB_kbd.h"
//#include "HAL.h"
//#include "hidkbd.h"

uint8_t tmos_pm_id = 0;
uint8_t pwr_mgr_trigger = PWR_MGR_TRIG_AUTO;

#define CONFIG_PM_DBG

#ifdef CONFIG_PM_DBG
#define PM_DBG  PRINT
#else
#define PM_DBG(...)
#endif

#if (defined (HAL_SLEEP)) && (HAL_SLEEP == TRUE)
u8 pm_is_idle = false;

static void pm_tmos_msg(tmos_event_hdr_t *pMsg)
{
    switch (pMsg->event) {

    default:
        break;
    }
}

u8 pm_is_in_idle(void)
{
    return pm_is_idle;
}

void pm_start_working(int working_timeout, int idle_timeout)
{
    //PM_DBG("Enter pm working\n");
    pm_is_idle = false;

    if(working_timeout >= 0) {
        tmos_start_task(tmos_pm_id, PM_ENTER_IDLE_EVENT, MS1_TO_SYSTEM_TIME(working_timeout));

        if(idle_timeout >=0) {
            tmos_start_task(tmos_pm_id, PM_ENTER_STANDBY_EVENT, MS1_TO_SYSTEM_TIME(idle_timeout));
        } else {
            //PM_DBG("Warning: invalid idle_time! \n");
        }
    }
}

void pm_goto_standby(void)
{
    PM_DBG("Enter PM standby!\n");
    DelayMs(10);

//    usb_disable();
    USB_Task_deinit();
    PFIC_EnableIRQ( GPIO_A_IRQn );
    RstAllPins();
    LowPower_Shutdown(0);
}

uint16_t pm_event(uint8_t task_id, uint16_t events)
{
    if (events & SYS_EVENT_MSG) {
        tmos_event_hdr_t *pMsg;

        if ((pMsg = (tmos_event_hdr_t *)tmos_msg_receive(tmos_pm_id)) != NULL) {
            pm_tmos_msg((tmos_event_hdr_t *) pMsg);
            // Release the TMOS message
            tmos_msg_deallocate((uint8_t *)pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & PM_ENTER_IDLE_EVENT) {
        PM_DBG("Enter pm idle\n");
        if(pm_is_idle==2){

        }else{
            pm_is_idle = true;
        }

        if(device_mode == CONN_BLE)
            OnBoard_SendMsg(hidEmuTaskId, RF_MS_STATE_CHANGE, PM_STATE_SLEEP, NULL);

        return (events ^ PM_ENTER_IDLE_EVENT);
    }

    if(events & PM_ENTER_STANDBY_EVENT) {
        pm_goto_standby();

        return (events ^ PM_ENTER_STANDBY_EVENT);
    }

    return 0;
}

void pm_task_init(void)
{
    tmos_pm_id = TMOS_ProcessEventRegister(pm_event);
    if(device_mode == CONN_USB || device_mode == CONN_TSET){
        pm_start_working(PM_TIMEOUT_FOREVER, PM_TIMEOUT_FOREVER);
    } else {
        pm_start_working(PM_WORKING_TIMEOUT, PM_IDLE_TIMEOUT);
    }
}
#else

static void tmos_power_manager_msg(tmos_event_hdr_t *pMsg)
{
    switch (pMsg->event) {
        case PM_ENTER_STANDBY_MSG: {
            SendMSG_t *msg = (SendMSG_t *)pMsg;
            msg->hdr.status?tmos_set_event(tmos_pm_id, PM_ENTER_STANDBY_EVENT):0;
            break;
        }

        default:
            break;
    }
}

uint16_t tmos_power_manager_event(uint8_t task_id, uint16_t events) {
    if (events & SYS_EVENT_MSG) {
        tmos_event_hdr_t *pMsg;

        if ((pMsg = (tmos_event_hdr_t *)tmos_msg_receive(tmos_pm_id)) != NULL) {
            tmos_power_manager_msg((tmos_event_hdr_t *) pMsg);
            // Release the TMOS message
            tmos_msg_deallocate((uint8_t *)pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & PM_ENTER_STANDBY_EVENT) {
        power_manager_enter_standby();
        return (events ^ PM_ENTER_STANDBY_EVENT);
    }

    return 0;
}

void pm_task_init(void)
{

}
u8 pm_is_in_idle(void)
{

    return false;
}

void pm_start_working(int working_timeout, int idle_timeout)
{

}

void power_manager_enter_standby(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

//    printf("enter power standby\n");

    led_red_on();
    Delay_Ms(500);
    led_red_off();

    rf_deinit();
    tmos_keyboard_deinit();

    GPIO_ALL_Init();
    eta9184_vbus_gpio_init();

    EXTI_DeInit();
//    if (pwr_mgr_trigger == PWR_MGR_TRIG_AUTO) {
        eta9184_vbus_exti_event_init();
//    } else {
        kb_fn_exti_event_init();
//    }

    PWR_EnterSTANDBYMode();
}

void tmos_power_manager() {

}

void tmos_power_manager_init() {
    tmos_pm_id = TMOS_ProcessEventRegister(tmos_power_manager_event);
//    if(connection_mode == CONN_USB || device_mode == CONN_TSET){
//        pm_start_working(PM_TIMEOUT_FOREVER, PM_TIMEOUT_FOREVER);
//    } else {
//        pm_start_working(PM_WORKING_TIMEOUT, PM_IDLE_TIMEOUT);
//    }
}

#endif /* HAL_SLEEP */
