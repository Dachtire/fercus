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
#include "HAL.h"
#include "SLEEP.h"
#include "config.h"
#include "eta9184.h"
#include "keyboard.h"
#include "led.h"
#include "rf-phy.h"
#include "tmos-keyboard.h"
#include "tmos-power-manager.h"

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
//        keyboard_scan_it();
//        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//    }
//}

void EXTI15_10_IRQHandler() {
//    if (EXTI_GetITStatus(EXTI_Line15) == SET) {
//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == SET) {
////            printf("usb in\n");
//        } else {
////            printf("usb out\n");
//            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
//        }
//        EXTI_ClearITPendingBit(EXTI_Line15);
//    }
//    if (EXTI_GetITStatus(EXTI_Line10) == SET) {
////        FIXME: bounce at usb out
//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == SET) {
//            printf("usb in\n");
//        } else {
//            printf("usb out\n");
//        }
//        EXTI_ClearITPendingBit(EXTI_Line10);
//    }

//    if (EXTI_GetITStatus(EXTI_Line10) == SET) {
//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == SET) {
//            GPIO_ResetBits(LED_G_PORT, LED_G_PIN);
//        } else {
//            GPIO_SetBits(LED_G_PORT, LED_G_PIN);
//        }
//        EXTI_ClearITPendingBit(EXTI_Line10);
//    }

//    if (EXTI_GetITStatus(EXTI_Line13) == SET) {
//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == KB_FN_PRESS) {
//            printf("fn1\n");
//
//            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == KB_FN_PRESS) {}
//
////            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
//
//            EXTI_ClearITPendingBit(EXTI_Line13);
//        }
//
//        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == KB_FN_PRESS) {
//            printf("fn3\n");
//
//            while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == KB_FN_PRESS) {}
//
//            //            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
//
//            EXTI_ClearITPendingBit(EXTI_Line13);
//        }
//    }

//    if (EXTI_GetITStatus(EXTI_Line14) == SET) {
//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == KB_FN_PRESS) {
//            printf("fn0 exti\n");
//
//            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == KB_FN_PRESS) {}
//
//            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
//
//            EXTI_ClearITPendingBit(EXTI_Line14);
//        }
//    }
}

//void EXTI2_IRQHandler(){
//    if (EXTI_GetITStatus(EXTI_Line2) == SET) {
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == KB_FN_PRESS) {
//            printf("fn2\n");
//            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == KB_FN_PRESS) {}
//
//            EXTI_ClearITPendingBit(EXTI_Line2);
//        }
//    }
//
////    if (EXTI_GetITStatus(EXTI_Line9) == SET) {
////        if (GPIO_ReadInputDataBit(KB_FN_1_GPIO_PORT, KB_FN_1_GPIO_PIN) == KB_FN_PRESS) {
////            printf("fn1\n");
////
////            while (GPIO_ReadInputDataBit(KB_FN_1_GPIO_PORT, KB_FN_1_GPIO_PIN) == KB_FN_PRESS) {}
////
////            GPIO_ResetBits(LED_B_PORT, LED_B_PIN);
////            Delay_Ms(500);
////            GPIO_SetBits(LED_B_PORT, LED_B_PIN);
////
////            EXTI_ClearITPendingBit(EXTI_Line9);
////        }
////    }
//}

//void TIM1_CC_IRQHandler(void)
//{
//    if( TIM_GetITStatus( TIM1, TIM_IT_CC1 ) != RESET )
//    {
//        printf( "CH1_Val:%d\r\n", TIM_GetCapture1( TIM1 ) );
//        TIM_SetCounter( TIM1, 0 );
//    }
//
//    if( TIM_GetITStatus( TIM1, TIM_IT_CC2 ) != RESET )
//    {
//        printf( "CH2_Val:%d\r\n", TIM_GetCapture2( TIM1 ) );
//    }
//
//    TIM_ClearITPendingBit( TIM1, TIM_IT_CC1 | TIM_IT_CC2 );
//}

//void PVD_IRQHandler(void)
//{
//    if(PWR_GetFlagStatus(PWR_FLAG_PVDO))
//    {
//        PWR_ClearFlag(PWR_FLAG_PVDO);
//    }
//    else {
//
//    }
//    EXTI_ClearITPendingBit(EXTI_Line16); /* Clear Flag */
//}

#define ETA9184_PULSE_RESET 5000
void TIM4_IRQHandler(void) {
    if( TIM_GetITStatus( TIM4, TIM_IT_CC3 ) != RESET ) {
        static uint8_t tim4_ic_count = 0;
        static uint8_t valid = FALSE;
        static uint16_t previous_ccr = 0;
        uint16_t curr_ccr = TIM_GetCapture3(TIM4);
        uint16_t diff_ccr = curr_ccr - previous_ccr;
        previous_ccr = curr_ccr;

        if (diff_ccr > ETA9184_PULSE_RESET && valid == FALSE) {
            valid = TRUE;
            tim4_ic_count = 0;
        } else if (diff_ccr > ETA9184_PULSE_RESET && valid == TRUE) {
            TIM_Cmd(TIM4, DISABLE);
            valid = FALSE;
            printf("t4c3_count:%d\n", tim4_ic_count);
        }

        if (valid == TRUE) {
            tim4_ic_count++;
//            printf("t4c3_cvr:%d\n", curr_ccr);
        } else {

        }

//        @10 kHz
//        before 4s, high to high: 23219-23224 = 2.3219 s. assume low is half, low to high: 20898 = 2.0898 s. between is 18575.
//        in 4s, 1 period high to low: 4644-4645-4646 = 0.4645 s
        TIM_ClearITPendingBit( TIM4, TIM_IT_CC3 );
    }

    if( TIM_GetITStatus( TIM4, TIM_IT_Update ) != RESET ) {
        printf("t4_ud\n");
//        static uint8_t tim4_ic_count = 0;
//        tim4_ic_count++;
//        printf( "t4c3_count:%d\n", tim4_ic_count);
//        printf( "t4c3_cvr:%d\n", TIM_GetCapture3( TIM4 ) );
        TIM_ClearITPendingBit( TIM4, TIM_IT_Update );
    }
}

#define ETA9184_PULSE_LED_TIME 8
void EXTI9_5_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line9) == SET) {
        rf_deinit();
        tmos_keyboard_deinit();
        EXTI_DeInit();

//        kb_fn_exti_event_init();

        PWR_EnterSTANDBYMode();
        EXTI_ClearITPendingBit(EXTI_Line9);
    }

    if (EXTI_GetITStatus(EXTI_Line8) == SET) {
        static uint8_t pulse_1 = 0, pulse_0 = 0;
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == SET) {
//            printf("pulse: 1\n");
            GPIO_SetBits(LED_R_PORT, LED_R_PIN);
            pulse_1++;
        } else {
            GPIO_ResetBits(LED_R_PORT, LED_R_PIN);
//            printf("pulse: 0\n");
            pulse_0++;
        }
        if (pulse_0 > ETA9184_PULSE_LED_TIME || pulse_1 > ETA9184_PULSE_LED_TIME) {
            eta9184_pulse_it_deinit();
//            printf("pulse: deinit\n");
            pulse_1 = 0;
            pulse_0 = 0;
            GPIO_ResetBits(LED_R_PORT, LED_R_PIN);
        }
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}

//void ADC1_2_IRQHandler(void) {
//    static uint8_t twice = 0;
//    if(ADC_GetITStatus(ADC1, ADC_IT_AWD)) {
////        while (ADC_GetConversionValue(ADC1) < 3100) {};
////        ADC_AnalogWatchdogThresholdsConfig(ADC1, 4000, 3100);
//        twice++;
////        printf("a%d\n", twice);
//        if (twice > 1) {
////            while (1);
//            rf_deinit();
//            tmos_keyboard_deinit();
//            EXTI_DeInit();
//
//            //        kb_fn_exti_event_init();
////
//            PWR_EnterSTANDBYMode();
//        }
//    }
//    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
//}
