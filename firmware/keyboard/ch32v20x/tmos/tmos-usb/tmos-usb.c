//#include "CH58x_common.h"
#include "tmos-usb.h"
#include "HAL.h"
#include "config.h"
#include "hw_config.h"
#include "keyboard.h"
#include "usb_init.h"
//#include "device_config.h"

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
//        if(DevEPn_IN_Deal())
//        keyboard_usb_send();
//        tmos_set_event(USBTaskID, USB_IN_EVT);
//        usbd_kb_report_send(kb_report_usbd);
        keyboard_usb_send();
        tmos_start_task(USBTaskID, USB_IN_EVT, MS1_TO_SYSTEM_TIME(1));
        return (events ^ USB_IN_EVT);
    }

    if(events & USB_INIT_EVT){
        Set_USBConfig();
        USB_Init();
        USB_Interrupts_Config();
        USB_Sleep_Wakeup_CFG( );
        //    if( bDeviceState == CONFIGURED ) {
        //        kb_usb = KB_USBD_DEVICE;
        return (events ^ USB_INIT_EVT);
    }
    return 0;
}


void USB_Task_Init(void)
{
    USBTaskID = TMOS_ProcessEventRegister(USB_ProcessEvent);

    tmos_start_task(USBTaskID, USB_INIT_EVT, MS1_TO_SYSTEM_TIME(1000));
    tmos_start_task(USBTaskID, USB_IN_EVT, MS1_TO_SYSTEM_TIME(2000));
}

void USB_Task_deinit(void)
{
    USBTaskID = 0;
//    usb_disable();
}

uint16_t USBFS_ProcessEvent(uint8_t task_id, uint16_t events)
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
        //        if(DevEPn_IN_Deal())
        //        keyboard_usb_send();
        //        tmos_set_event(USBTaskID, USB_IN_EVT);
        //        usbd_kb_report_send(kb_report_usbd);
        keyboard_usb_send();
        tmos_start_task(USBTaskID, USB_IN_EVT, MS1_TO_SYSTEM_TIME(1));

        return (events ^ USB_IN_EVT);
    }

    if(events & USB_INIT_EVT){
        /* Initialize USBHD interface to communicate with the host  */
        //        USBFS_RCC_Init( );
        //        USBFS_Device_Init( ENABLE );
        //        USB_Sleep_Wakeup_CFG( );
        //        if (USBFS_DevEnumStatus) {
        //            kb_usb = KB_USBFS_DEVICE;
        //        }

/* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
        DUG_PRINTF("USBFS Host Init\r\n");
        USBFS_RCC_Init();
        USBFS_Host_Init(ENABLE);
        memset(&RootHubDev.bStatus, 0, sizeof(ROOT_HUB_DEVICE));
        memset(&HostCtl[DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL].InterfaceNum, 0, sizeof(HOST_CTL));
#endif

        return (events ^ USB_INIT_EVT);
    }
    return 0;
}

void USBFS_Task_Init(void)
{
    USBTaskID = TMOS_ProcessEventRegister(USB_ProcessEvent);

    tmos_start_task(USBTaskID, USB_INIT_EVT, MS1_TO_SYSTEM_TIME(1000));
    tmos_start_task(USBTaskID, USB_IN_EVT, MS1_TO_SYSTEM_TIME(2000));
}