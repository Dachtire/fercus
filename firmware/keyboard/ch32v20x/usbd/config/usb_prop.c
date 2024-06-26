/********************************** (C) COPYRIGHT *******************************
* File Name          : usb_prop.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/08/20
* Description        : USB Processing
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "app.h"

//#include "usbd-hid-keyboard.h"
//#include "usbd_composite.h"
//#include "usbd_hid_cntlr.h"
//#include "usbd_hid_mouse.h"
//#include "usbd_vendor.h"

uint8_t Request = 0;

volatile uint8_t HIDReportOut[8] = {0};
volatile uint8_t USBD_Sleep_Status = 0x00;
volatile uint8_t HID_Idle_Value[8] = {0};
volatile uint8_t HID_Protocol_Value[8] = {0};

DEVICE Device_Table =
{
	EP_NUM,
	1
};

DEVICE_PROP Device_Property =
{
	USBD_init,
	USBD_Reset,
	USBD_Status_In,
	USBD_Status_Out,
	USBD_Data_Setup,
	USBD_NoData_Setup,
	USBD_Get_Interface_Setting,
	USBD_GetDeviceDescriptor,
	USBD_GetConfigDescriptor,
	USBD_GetStringDescriptor,
	0,
	DEF_USBD_UEP0_SIZE                                 
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
	USBD_GetConfiguration,
	USBD_SetConfiguration,
	USBD_GetInterface,
	USBD_SetInterface,
	USBD_GetStatus, 
	USBD_ClearFeature,
	USBD_SetEndPointFeature,
	USBD_SetDeviceFeature,
	USBD_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor = {
        (uint8_t*)&usbd_composite_dev_desc,
        USBD_SIZE_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor = {
        (uint8_t*)&usbd_composite_config_desc,
        USBD_COMPOSITE_CONFIG_DESC_SIZE
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
	{(uint8_t*) &usbd_language_id_desc, USBD_SIZE_STRING_LANGID},
	{(uint8_t*) &manufacturer_string, USBD_SIZE_STRING_VENDOR},
	{(uint8_t*) &product_string,USBD_SIZE_STRING_PRODUCT},
	{(uint8_t*) &serial_string, USBD_SIZE_STRING_SERIAL}
};

ONE_DESCRIPTOR Report_Descriptor[USBD_ITF_NUM_COMPOSITE] = {
    {(uint8_t*)usbd_kb_report_desc, USBD_REPORT_DESC_SIZE_KB},
    {(uint8_t*)usbd_report_desc_cntlr, USBD_REPORT_DESC_SIZE_CNTLR},
    {(uint8_t*)usbd_mouse_report_desc, HID_MOUSE_REPORT_DESC_SIZE},
//    {(uint8_t*)usbd_report_desc_sim, USBD_REPORT_DESC_SIZE_SIM},
    {(uint8_t*)usbd_hid_comp_report_desc, USBD_REPORT_DESC_SIZE_COMP}
};

ONE_DESCRIPTOR Hid_Descriptor[USBD_ITF_NUM_COMPOSITE] = {
    {(uint8_t*)&usbd_composite_config_desc.kb_inf.iInterface, 0x09},
    {(uint8_t*)&usbd_composite_config_desc.cntlr_inf.iInterface, 0x09},
    {(uint8_t*)&usbd_composite_config_desc.mouse_inf.iInterface, 0x09},
//    {(uint8_t*)&usbd_composite_config_desc.sim_inf.iInterface, 0x09},
    {(uint8_t*)&usbd_composite_config_desc.comp_inf.iInterface, 0x09}
};

/*********************************************************************
 * @fn      USBD_SetConfiguration.
 *
 * @brief     Update the device state to configured.
 *
 * @return    None.
 */
void USBD_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    bDeviceState = CONFIGURED;
  }
}

/*******************************************************************************
 * @fn         USBD_SetDeviceAddress.
 *
 * @brief      Update the device state to addressed.
 *
 * @return     None.
 */
void USBD_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}


/*********************************************************************
 * @fn      USBD_SetDeviceFeature.
 *
 * @brief   SetDeviceFeature Routine.
 *
 * @return  none
 */
void USBD_SetDeviceFeature (void)
{
  USBD_Sleep_Status |= 0x01;
}



/*********************************************************************
 * @fn      USBD_ClearFeature.
 *
 * @brief   ClearFeature Routine.
 *
 * @return  none
 */
void USBD_ClearFeature(void)
{
  USBD_Sleep_Status &= ~0x01;
}





/*********************************************************************
 * @fn      USBD_Status_In.
 *
 * @brief    USBD Status In Routine.
 *
 * @return   None.
 */
void USBD_Status_In(void)
{

}

/*******************************************************************************
 * @fn       USBD_Status_Out
 *
 * @brief    USBD Status OUT Routine.
 *
 * @return   None.
 */
void USBD_Status_Out(void)
{
    
}

/*******************************************************************************
 * @fn       USB_init.
 *
 * @brief    init routine.
 * 
 * @return   None.
 */
void USBD_init(void)
{
  uint8_t	i;
    
  pInformation->Current_Configuration = 0;
  PowerOn();
  for (i=0;i<8;i++) _SetENDPOINT(i,_GetENDPOINT(i) & 0x7F7F & EPREG_MASK);//all clear
  _SetISTR((uint16_t)0x00FF);//all clear
  USB_SIL_Init();
  bDeviceState = UNCONNECTED;
  
  USB_Port_Set(DISABLE, DISABLE);	
  Delay_Ms(20);
  USB_Port_Set(ENABLE, ENABLE);    
}

/*******************************************************************************
 * @fn      USBD_Reset
 *
 * @brief   Virtual_Com_Port Mouse reset routine
 *
 * @return  None.
 */
void USBD_Reset(void)
{
  pInformation->Current_Configuration = 0;
  pInformation->Current_Feature = usbd_composite_config_desc.config.bmAttributes;
  pInformation->Current_Interface = 0;

  SetBTABLE(BTABLE_ADDRESS);

  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_STALL);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);
  _ClearDTOG_RX(ENDP0);
  _ClearDTOG_TX(ENDP0);

    SetEPType(ENDP1, EP_INTERRUPT);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPRxAddr(ENDP1, ENDP1_RXADDR);
    SetEPRxCount(ENDP1, HID_KYBD_OUT_PACKET);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    ClearDTOG_RX(ENDP1);
    ClearDTOG_TX(ENDP1);

    SetEPType(ENDP2, EP_INTERRUPT);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxAddr(ENDP2, ENDP2_RXADDR);
    SetEPRxCount(ENDP2, HID_CNTLR_OUT_PACKET);
    SetEPRxStatus(ENDP2, EP_RX_VALID);
    SetEPTxStatus(ENDP2, EP_TX_NAK);
    ClearDTOG_RX(ENDP2);
    ClearDTOG_TX(ENDP2);

    SetEPType(ENDP3, EP_INTERRUPT);
    SetEPTxAddr(ENDP3, ENDP3_TXADDR);
    SetEPRxAddr(ENDP3, ENDP3_RXADDR);
    SetEPRxCount(ENDP3, HID_MOUSE_OUT_PACKET);
    SetEPRxStatus(ENDP3, EP_RX_VALID);
    SetEPTxStatus(ENDP3, EP_TX_NAK);
    ClearDTOG_RX(ENDP3);
    ClearDTOG_TX(ENDP3);
    
    SetEPType(ENDP4, EP_INTERRUPT);
    SetEPTxAddr(ENDP4, ENDP4_TXADDR);
    SetEPRxAddr(ENDP4, ENDP4_RXADDR);
    SetEPRxCount(ENDP4, HID_SIM_OUT_PACKET);
    SetEPRxStatus(ENDP4, EP_RX_VALID);
    SetEPTxStatus(ENDP4, EP_TX_NAK);
    ClearDTOG_RX(ENDP4);
    ClearDTOG_TX(ENDP4);

//    SetEPType(ENDP5, EP_INTERRUPT);
//    SetEPTxAddr(ENDP5, ENDP5_TXADDR);
//    SetEPRxAddr(ENDP5, ENDP5_RXADDR);
//    SetEPRxCount(ENDP5, HID_COMP_OUT_PACKET);
//    SetEPRxStatus(ENDP5, EP_RX_VALID);
//    SetEPTxStatus(ENDP5, EP_TX_NAK);
//    ClearDTOG_RX(ENDP5);
//    ClearDTOG_TX(ENDP5);

//          SetEPType(ENDP1, EP_BULK);
//          SetEPTxAddr(ENDP1, ENDP1_TXADDR);
//          SetEPRxAddr(ENDP1, ENDP1_RXADDR);
//          SetEPRxCount(ENDP1, ENDP1_OUT_SIZE);
//          SetEPRxStatus(ENDP1, EP_RX_VALID);
//          SetEPTxStatus(ENDP1, EP_TX_NAK);
//          ClearDTOG_RX(ENDP1);
//          ClearDTOG_TX(ENDP1);

    SetDeviceAddress(0);

    bDeviceState = ATTACHED;
}

/*******************************************************************************
 * @fn      USBD_GetDeviceDescriptor.
 *
 * @brief   Gets the device descriptor.
 *
 * @param   Length.
 *
 * @return  The address of the device descriptor.
 */
uint8_t *USBD_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
 * @fn       USBD_GetConfigDescriptor.
 *
 * @brief    get the configuration descriptor.
 *
 * @param    Length.
 *
 * @return   The address of the configuration descriptor.
 */
uint8_t *USBD_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
 * @fn        USBD_GetStringDescriptor
 *
 * @brief     Gets the string descriptors according to the needed index
 *
 * @param     Length.
 *
 * @return    The address of the string descriptors.
 */
uint8_t *USBD_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
	
//  if (wValue0 > 4)
//  {
//    return NULL;
//  }
//  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}

/*********************************************************************
 * @fn      USBD_GetReportDescriptor
 *
 * @brief   Gets the report descriptors according to the needed index
 *
 * @param   Length.
 *
 * @return  The address of the device descriptor.
 */
uint8_t *USBD_GetReportDescriptor(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
//  if (wIndex0 > 2)
//  {
//    return NULL;
//  }
//  else
  {
      return Standard_GetDescriptorData(Length, &Report_Descriptor[wIndex0]);
  }
}

/*********************************************************************
 * @fn      USBD_GetHidDescriptor
 *
 * @brief   Gets the report descriptors according to the needed index
 *
 * @param   Length.
 *
 * @return  The address of the device descriptor.
 */
uint8_t *USBD_GetHidDescriptor(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
//  if (wIndex0 > 2)
//  {
//    return NULL;
//  }
//  else
  {
      return Standard_GetDescriptorData(Length, &Hid_Descriptor[wIndex0]);
  }
}

/*********************************************************************
 * @fn      USBD_Get_Interface_Setting.
 *
 * @brief  test the interface and the alternate setting according to the
 *                  supported one.
 *
 * @param  Interface: interface number.
 *                  AlternateSetting: Alternate Setting number.
 *
 * @return USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 1)
  {
    return USB_UNSUPPORT;
  }
	
  return USB_SUCCESS;
}

/*******************************************************************************
 * @fn       USBD_Data_Setup
 *
 * @brief    handle the data class specific requests
 *
 * @param    Request Nb.
 *
 * @return   USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  uint32_t Request_No = pInformation->USBbRequest;
  uint32_t wOffset;
  CopyRoutine = NULL;
  wOffset = 0;


  if (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
  {
    uint8_t wValue1 = pInformation->USBwValue1;

    if (wValue1 == HID_REPORT_DESCRIPTOR)
    {
      CopyRoutine = USBD_GetReportDescriptor;
    }
    else if (wValue1 == HID_DESCRIPTOR)
    {
      CopyRoutine = USBD_GetHidDescriptor;
    }
    if (CopyRoutine)
    {
      pInformation->Ctrl_Info.Usb_wOffset = wOffset;
      pInformation->Ctrl_Info.CopyData = CopyRoutine;
      (*CopyRoutine)(0);
    }
    else
    {
      return USB_UNSUPPORT;
    }

  }
  else if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT) )
  {
    if (Request_No == HID_GET_REPORT)
    {
      /* HID Get Report */
    }
    else if (Request_No == HID_GET_IDLE)
    {
      pInformation->Ctrl_Info.Usb_wLength = 1;
      pInformation->Ctrl_Info.CopyData = &HID_Get_Idle;
    }
    else if (Request_No == HID_GET_PROTOCOL)
    {
      pInformation->Ctrl_Info.Usb_wLength = 1;
      pInformation->Ctrl_Info.CopyData = &HID_Get_Protocol;
    }  
    else if (Request_No == HID_SET_REPORT)
    {
      if (pInformation->USBwLengths.w > 1)
      {
        return USB_UNSUPPORT;
      }
      else
      {
        pInformation->Ctrl_Info.Usb_wLength = pInformation->USBwLengths.w;
        pInformation->Ctrl_Info.CopyData = &HID_Set_Report;
        pInformation->ControlState = OUT_DATA;
      }
    }
    else
    {
      return USB_UNSUPPORT;
    }    
  }
  return USB_SUCCESS;
}

/*******************************************************************************
 * @fn      USBD_NoData_Setup.
 *
 * @brief   handle the no data class specific requests.
 *
 * @param   Request Nb.
 *
 * @return  USB_UNSUPPORT or USB_SUCCESS.
 */
RESULT USBD_NoData_Setup(uint8_t RequestNo)
{      
  uint32_t Request_No = pInformation->USBbRequest;
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
  {
    if (Request_No == HID_SET_IDLE)
    {
//      if (wIndex0 > 2)
//      {
//        return USB_UNSUPPORT;
//      }
//      else
      {
        HID_Idle_Value[wIndex0] = pInformation->USBwValues.bw.bb1;
      }
      
    }
    else if (Request_No == HID_SET_PROTOCOL)
    {
//      if (wIndex0 > 2)
//      {
//        return USB_UNSUPPORT;
//      }
//      else
      {
        HID_Protocol_Value[wIndex0] = pInformation->USBwValues.bw.bb0;
      }
    }
    else
    {
      return USB_UNSUPPORT;
    }    
  }             
  return USB_SUCCESS;
}


/*********************************************************************
 * @fn      HID_Set_Report.
 *
 * @brief   HID Set Report.
 *
 * @param   
 *
 * @return  HIDReportOut.
 */
uint8_t *HID_Set_Report(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
//  if (wIndex0 > 1)
//  {
//    return NULL;
//  }
//  else
  {
    return (uint8_t *)&KB_LED_Cur_Status;
  }
}

/*********************************************************************
 * @fn      HID_Get_Idle.
 *
 * @brief   HID Save Report Data.
 *
 * @param   
 *
 * @return  HIDReportOut.
 */
uint8_t *HID_Get_Idle(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
//  if (wIndex0 > 2)
//  {
//    return NULL;
//  }
//  else
  {
    return (uint8_t*)&HID_Idle_Value[wIndex0];
  }
}
/*********************************************************************
 * @fn      HID_Get_Protocol.
 *
 * @brief   HID Save Report Data.
 *
 * @param   
 *
 * @return  HIDReportOut.
 */
uint8_t *HID_Get_Protocol(uint16_t Length)
{
  uint8_t wIndex0 = pInformation->USBwIndexs.bw.bb0;
//  if (wIndex0 > 2)
//  {
//    return NULL;
//  }
//  else
  {
    return (uint8_t*)&HID_Protocol_Value[wIndex0];
  }
}
