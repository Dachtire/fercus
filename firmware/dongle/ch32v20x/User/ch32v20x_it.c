/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/06/16
 * Description        : Main Interrupt Service Routines.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "ch32v20x_it.h"
//#include "keyboard.h"
#include "config.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void BB_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
    while(1)
    {
    }
}

/*********************************************************************
 * @fn      BB_IRQHandler
 *
 * @brief   BB Interrupt for BLE.
 *
 * @return  None
 */
void BB_IRQHandler(void)
{
    BB_IRQLibHandler();
}

//void TIM1_UP_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
//        switch (kb_device) {
//            default:
//            case KB_DEVICE_KEYBORAD:
//            case KB_DEVICE_KEYBOARD_ADC_DIFF:
//            case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//            case KB_DEVICE_CNTLR_ADC:
//                kb_it();
////                printf("kb_it\n");
//                break;
//
//            case KB_DEVICE_VENDOR:
////                kb_adc_it();
//                kb_adc_time();
//                break;
//        }
//        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//    }
//}

//void EXTI15_10_IRQHandler() {
//    if (GPIO_ReadInputDataBit(KB_FN_3_GPIO_PORT, KB_FN_3_GPIO_PIN) == KB_FN_PRESS) {
//        printf("fn3\n");
//        EXTI_ClearITPendingBit(EXTI_Line14);
//    }
//
////        if (EXTI_GetITStatus(EXTI_Line13) == RESET) {
//    if (GPIO_ReadInputDataBit(ETA_DISCHRG_PORT, ETA_DISCHRG_PIN) == ETA_DISCHRG_DISABLE) {
//        TIM_Cmd(TIM1, DISABLE);
//        printf("eta_dischrg\n");
//        EXTI_ClearITPendingBit(EXTI_Line13);
//    }
//}

//void EXTI9_5_IRQHandler(){
//    if (GPIO_ReadInputDataBit(KB_FN_0_GPIO_PORT, KB_FN_0_GPIO_PIN) == KB_FN_PRESS) {
//        printf("fn0\n");
//        EXTI_ClearITPendingBit(EXTI_Line8);
//    }
//    if (GPIO_ReadInputDataBit(KB_FN_1_GPIO_PORT, KB_FN_1_GPIO_PIN) == KB_FN_PRESS) {
//        printf("fn1\n");
//        EXTI_ClearITPendingBit(EXTI_Line9);
//    }
//}

//void PVD_IRQHandler(void)
//{
////    kb_ctl &= ~KB_CTL_USBD;
//    if(PWR_GetFlagStatus(PWR_FLAG_PVDO))
//    {
//        PWR_ClearFlag(PWR_FLAG_PVDO);
//    }
//    else {
//
//    }
//    EXTI_ClearITPendingBit(EXTI_Line16); /* Clear Flag */
//}