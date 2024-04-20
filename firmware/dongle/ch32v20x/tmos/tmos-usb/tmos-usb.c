//#include "CH58x_common.h"
#include "tmos-usb.h"
#include "HAL.h"
#include "app.h"
#include "ch32v20x_usbfs_device.h"
//#include "ch32v20x_usbfs_host.h"
#include "RF_PHY.h"
#include "config.h"
#include "usbd-hid-keyboard.h"
//#include "device_config.h"
//#include "rf_config.h"
//#include "rf_port.h"
//#include "usbuser.h"

uint8_t USBTaskID = INVALID_TASK_ID;

static void USB_ProcessTMOSMsg(tmos_event_hdr_t *pMsg)
{

    switch (pMsg->event) {
    case KEY_MESSAGE: {
        SendMSG_t *msg = (SendMSG_t *)pMsg;
        msg->hdr.status?tmos_set_event(USBTaskID, USB_IN_EVT):0;
        break;
    }
    default:
        break;
    }
}

//void usb_send_release(void)
//{
//    const uint8_t key_normal_release[4 + 9] = {0};
//    const uint8_t key_consume_release[4 + 3] = {0, 0, 0, 0, CONSUME_ID};
//    const uint8_t key_bit_release[4 + 17] = {0, 0, 0, 0, KEYBIT_ID};
//    const uint8_t key_mouse_release[4 + 5] = {0, 0, 0, 0, MOUSE_ID};

//    lwrb_reset(&rf_ringbuf_data);

//    if (is_host_sleep()) {
//        return ;
//    }

//    PRINT("usb relese\n");
//    lwrb_write(&rf_ringbuf_data, key_normal_release, sizeof(key_normal_release));
//    lwrb_write(&rf_ringbuf_data, key_consume_release, sizeof(key_consume_release));
//    lwrb_write(&rf_ringbuf_data, key_bit_release, sizeof(key_bit_release));

    /* Add more if you need */

//    tmos_start_task(USBTaskID, USB_IN_EVT, MS1_TO_SYSTEM_TIME(100));
//}

uint16_t USB_ProcessEvent(uint8_t task_id, uint16_t events)
{

    if (events & SYS_EVENT_MSG) {
        uint8_t *pMsg;

        if ((pMsg = tmos_msg_receive(USBTaskID)) != NULL) {
            USB_ProcessTMOSMsg((tmos_event_hdr_t *) pMsg);
            // Release the TMOS message
            tmos_msg_deallocate(pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & USB_IN_EVT){
//        DevEPn_IN_Deal();
        usbfs_kb_report_send(kb_report_usbd);

        tmos_set_event(USBTaskID, USB_IN_EVT);
//        tmos_start_task(USBTaskID, USB_IN_EVT, 1);
        return (events ^ USB_IN_EVT);
    }

    if(events & USB_INIT_EVT){
//        USB_Init();
        USBFS_RCC_Init( );
        USBFS_Device_Init( ENABLE );
        USB_Sleep_Wakeup_CFG( );
        return (events ^ USB_INIT_EVT);
    }

    return 0;
}

#define CONFIG_RF_DG_PAIR_TO   1000

void USB_Task_Init(void)
{
    USBTaskID = TMOS_ProcessEventRegister(USB_ProcessEvent);
    tmos_start_task(USBTaskID, USB_INIT_EVT, MS1_TO_SYSTEM_TIME(CONFIG_RF_DG_PAIR_TO - 200));
//    USB_Init();

    /* just for test */
//    tmos_start_task(USBTaskID, USB_TEST_EVT, MS1_TO_SYSTEM_TIME(1000));
}

void USB_Task_deinit(void)
{
    USBTaskID = 0;
//    usb_disable();
}
