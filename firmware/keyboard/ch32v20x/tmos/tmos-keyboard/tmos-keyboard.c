/*
 * Copyright (c) 2022 Nanjing Qinheng Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tmos-keyboard.h"
#include "HAL.h"
#include "app.h"
#include "config.h"
//#include "device_config.h"
#include "ble-hid-keyboard.h"
//#include "keyscan.h"
#include "tmos-power-manager.h"
//#include "tmos-rf-transmitter.h"
#include "joystick.h"
#include "tmos-usb.h"

uint8_t tmos_keyboard_task_id = 0;
static uint8_t no_key_count;

int key_deal(void)
{
//    readKeyVal();
//    int ret = readKeyVal();

//    if(ret > 0) {
//        no_key_count = 0;
//
//        switch(device_mode){
//        case CONN_BLE:
//            pm_start_working(PM_WORKING_TIMEOUT, PM_IDLE_TIMEOUT);
//            OnBoard_SendMsg(hidEmuTaskId, RF_MS_STATE_CHANGE, PM_STATE_ACTIVE, NULL);
//            OnBoard_SendMsg(hidEmuTaskId, KEY_MESSAGE, 1, NULL);
//            break;
//
//        case CONN_RF:
//            pm_start_working(PM_WORKING_TIMEOUT, PM_IDLE_TIMEOUT);
//            OnBoard_SendMsg(tmos_rf_device_task_id, KEY_MESSAGE, 1, NULL);
//            break;
//
//        case CONN_USB:
//            /* USB don't sleep */
//            pm_start_working(PM_TIMEOUT_FOREVER, PM_TIMEOUT_FOREVER);
//            OnBoard_SendMsg(USBTaskID, KEY_MESSAGE, 1, NULL);
//            break;
//
//        default:
//            pm_start_working(PM_TIMEOUT_FOREVER, PM_TIMEOUT_FOREVER);
//            break;
//        }
//    } else if(ret == 0) {
//        /* no key */
//        no_key_count++;
//
//        if(no_key_count > 50) {
//            no_key_count = 50;
//
//            if(pm_is_in_idle())
//            {
//                //PRINT("keyscan pause\n");
//                tmos_stop_task(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT);
//                return 0;
//            }
//        }
//    } else {
//        //PRINT("read key error\n");
//        return -1;
//    }
    keyboard_scan_delay();
    tmos_start_task(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT, MS1_TO_SYSTEM_TIME(1));
    return 1;
}

static void tmos_keyboard_process_msg(tmos_event_hdr_t *pMsg)
{
    switch (pMsg->event) {
      case KEY_PRESSED:
        tmos_start_task(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT, 0);
      break;

    default:
        break;
    }
}

uint16_t tmos_keyboard_process_event(uint8_t task_id, uint16_t events)
{
    if (events & SYS_EVENT_MSG) {
        tmos_event_hdr_t *pMsg;

        if ((pMsg = (tmos_event_hdr_t *)tmos_msg_receive(tmos_keyboard_task_id)) != NULL) {
            tmos_keyboard_process_msg((tmos_event_hdr_t *) pMsg);
            // Release the TMOS message
            tmos_msg_deallocate((uint8_t *)pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & KEYBOARD_SCAN_EVENT) {
        
//        int ret =
//        key_deal();
//        TIM1_Init();
//        printf("TIM1_Init\n");
//        tmos_set_event(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT);
        //  no switch press
//        if(ret < 0) {
//        if (eta9184_adc_get() > ETA9184_BOOST_VOLTAGE) {
        keyboard_scan_delay();
//        }
        tmos_start_task(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT, KEYBOARD_SCAN_EVENT_INTERVAL);
//        }
 
        return (events ^ KEYBOARD_SCAN_EVENT);
    }

    if(events & KEYBOARD_FN_SCAN_EVENT) {
        keyboard_fn_scan();
        tmos_start_task(tmos_keyboard_task_id, KEYBOARD_FN_SCAN_EVENT, KEYBOARD_SCAN_EVENT_INTERVAL);

        return (events ^ KEYBOARD_FN_SCAN_EVENT);
    }

    if(events & KEYBOARD_JS_SCAN_EVENT) {
        joystick_scan();
        tmos_start_task(tmos_keyboard_task_id, KEYBOARD_JS_SCAN_EVENT, KEYBOARD_SCAN_EVENT_INTERVAL * 100);

        return (events ^ KEYBOARD_JS_SCAN_EVENT);
    }

    return 0;
}

void tmos_keyboard_init(void)
{
    tmos_keyboard_task_id = TMOS_ProcessEventRegister(tmos_keyboard_process_event);
    tmos_start_task(tmos_keyboard_task_id, KEYBOARD_SCAN_EVENT, MS1_TO_SYSTEM_TIME(10) );
    tmos_start_task(tmos_keyboard_task_id, KEYBOARD_FN_SCAN_EVENT, MS1_TO_SYSTEM_TIME(10) );
//    tmos_start_task(tmos_keyboard_task_id, KEYBOARD_JS_SCAN_EVENT, MS1_TO_SYSTEM_TIME(10) );
}

void tmos_keyboard_deinit() {
    tmos_keyboard_task_id = 0;
}