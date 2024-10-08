/********************************** (C) COPYRIGHT *******************************
 * File Name          : usbd_composite_km.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : USB keyboard and mouse processing.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/


/*******************************************************************************/
/* Header Files */
#include "app.h"
#include "ch32v20x_usbfs_device.h"

/*******************************************************************************/
/* Variable Definition */

/* Mouse */
//volatile uint8_t  MS_Scan_Done = 0x00;                                          // Mouse Movement Scan Done
//volatile uint16_t MS_Scan_Result = 0x00F0;                                      // Mouse Movement Scan Result
//uint8_t  MS_Data_Pack[ DEF_ENDP_SIZE_MS ] = { 0x00 };                           // Mouse IN Data Packet

/* Keyboard */
//volatile uint8_t  KB_Scan_Done = 0x00;                                          // Keyboard Keys Scan Done
//volatile uint16_t KB_Scan_Result = 0xF000;                                      // Keyboard Keys Current Scan Result
//volatile uint16_t KB_Scan_Last_Result = 0xF000;                                 // Keyboard Keys Last Scan Result
//uint8_t  KB_Data_Pack[ DEF_ENDP_SIZE_KB ] = { 0x00 };                           // Keyboard IN Data Packet
//volatile uint8_t  KB_LED_Last_Status = 0x00;                                    // Keyboard LED Last Result
//volatile uint8_t  KB_LED_Cur_Status = 0x00;                                     // Keyboard LED Current Result

/* USART */
//volatile uint8_t  USART_Recv_Dat = 0x00;
//volatile uint8_t  USART_Send_Flag = 0x00;
//volatile uint8_t  USART_Send_Cnt = 0x00;

//void kb_col_gpio_init() {
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//    for (int i = 0; i < KB_COL_NUM; ++i) {
//        GPIO_InitStructure.GPIO_Pin   = KB_COL_GPIO_PIN[i];
//        GPIO_Init(KB_COL_GPIO_PORT[i], &GPIO_InitStructure);
//        GPIO_ResetBits(KB_COL_GPIO_PORT[i],KB_COL_GPIO_PIN[i]);
//    }
//}

//void kb_row_gpio_init() {
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    switch (kb_device) {
//        default:
//        case KB_DEVICE_KEYBORAD:
//            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//            break;
//
//        case KB_DEVICE_VENDOR:
//        case KB_DEVICE_KEYBOARD_ADC_DIFF:
//        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//        case KB_DEVICE_CNTLR_ADC:
//            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
//            break;
//    }
//
//    for (int i = 0; i < KB_ROW_NUM; ++i) {
//        GPIO_InitStructure.GPIO_Pin = KB_ROW_GPIO_PIN[i];
//        GPIO_Init(KB_ROW_GPIO_PORT, &GPIO_InitStructure);
//    }
//}

//void kb_fn_gpio_init() {
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//
//    for (int i = 0; i < KB_FN_NUM - 1; ++i) {
//        GPIO_InitStructure.GPIO_Pin = KB_FN_GPIO_PIN[i];
//        GPIO_Init(KB_FN_GPIO_PORT[i], &GPIO_InitStructure);
//    }
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin = KB_FN_3_GPIO_PIN;
//    GPIO_Init(KB_FN_3_GPIO_PORT, &GPIO_InitStructure);
//}

//void cntlr_gpio_init(){
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////    js axis
//    for (int i = 0; i < JS_AXIS_NUM; ++i) {
//        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//        GPIO_InitStructure.GPIO_Pin = JS_AXIS_GPIO_PIN[i];
//        GPIO_Init(JS_AXIS_GPIO_PORT[i], &GPIO_InitStructure);
//    }
////    js switch
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin = JS_SW_GPIO_PIN;
//    GPIO_Init(JS_SW_GPIO_PORT, &GPIO_InitStructure);
//}

//void eta_gpio_init(){
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//    GPIO_InitStructure.GPIO_Pin = ETA_DISCHRG_PIN;
//    GPIO_Init(ETA_DISCHRG_PORT, &GPIO_InitStructure);
//}

//void eta_bat_gpio_init() {
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
//    GPIO_InitStructure.GPIO_Pin = ETA_BAT_PIN;
//    GPIO_Init(ETA_BAT_PORT, &GPIO_InitStructure);
//}

//void led_gpio_init(){
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin = LED_B_PIN;
//    GPIO_Init(LED_B_PORT, &GPIO_InitStructure);
//    GPIO_SetBits(LED_B_PORT, LED_B_PIN);
//
//    GPIO_InitStructure.GPIO_Pin = LED_G_PIN;
//    GPIO_Init(LED_G_PORT, &GPIO_InitStructure);
//    GPIO_SetBits(LED_G_PORT, LED_G_PIN);
//
//    GPIO_InitStructure.GPIO_Pin = LED_R_PIN;
//    GPIO_Init(LED_R_PORT, &GPIO_InitStructure);
//    GPIO_SetBits(LED_R_PORT, LED_R_PIN);
//
//}

//void led_ctl(uint8_t color, uint8_t status){
//    if (status == TRUE) {
//        switch (color) {
//            default:
//                break;
//            case 0:
//                GPIO_ResetBits(LED_R_PORT,LED_R_PIN);
//                break;
//            case 1:
//                GPIO_ResetBits(LED_G_PORT,LED_G_PIN);
//                break;
//            case 2:
//                GPIO_ResetBits(LED_B_PORT,LED_B_PIN);
//                break;
//        }
//    } else {
//        switch (color) {
//            default:
//                break;
//            case 0:
//                GPIO_SetBits(LED_R_PORT,LED_R_PIN);
//                break;
//            case 1:
//                GPIO_SetBits(LED_G_PORT,LED_G_PIN);
//                break;
//            case 2:
//                GPIO_SetBits(LED_B_PORT,LED_B_PIN);
//                break;
//        }
//    }
//}

//void adc_config() {
//    switch (kb_device) {
//        default:
//        case KB_DEVICE_KEYBORAD:
////        case KB_DEVICE_COMPOSITE:
//            DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)js_axis_adc, JS_NUM);
//            DMA_Cmd(DMA1_Channel1, ENABLE);
//
//            ADC_Function_Init();
//            // t = 1 / 12Mhz
//            // longest 71Cycles5 = 7 * 6 us
//            #if KB_SIDE == KB_SIDE_LEFT
//                ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_71Cycles5);
//                ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_71Cycles5);
//            #else
//                ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_71Cycles5);
//                ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_71Cycles5);
//            #endif
//            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//            break;
//
//        case KB_DEVICE_KEYBOARD_ADC_DIFF:
//        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//        case KB_DEVICE_CNTLR_ADC:
//            DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)kb_row_adc, KB_ROW_NUM);
//            DMA_Cmd(DMA1_Channel1, ENABLE);
//
//            ADC_Function_Init();
//            // t = 1 / 12Mhz
//            // 71Cycles5 = 7 * 6 us
//            // 2)单次扫描模式转换  // , 3)单次间断模式转换, 4)连续转换
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5);
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_71Cycles5);
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_71Cycles5);
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_71Cycles5);
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_71Cycles5);
//            ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_71Cycles5);
//
//            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//            break;
//
//        case KB_DEVICE_VENDOR:
//            DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)kb_adc_value, KB_ADC_SIZE);
//            DMA_Cmd(DMA1_Channel1, ENABLE);
//
//            ADC_Function_Init();
//            ADC_RegularChannelConfig(ADC1, 0, 1, ADC_SampleTime_1Cycles5);
//            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//            break;
//    }
//}

//void USART1_Init(u32 baudrate)
//{
//    //	GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//
//    /* USART1 GPIO Init */
//    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    //    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//    //    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
//    //    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    //
//    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    //    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    /* USART1 Init */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//    USART_InitStructure.USART_BaudRate = baudrate;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//    USART_Init(USART1, &USART_InitStructure);
//    USART_Cmd(USART1, ENABLE);
//    USART_ClearFlag(USART1,USART_IT_RXNE);
//}

//void TIM1_Init(uint32_t ms)
//{
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
////    NVIC_EnableIRQ(TIM1_UP_IRQn);
//
//    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
//    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init( &NVIC_InitStructure );
//
//    SetVTFIRQ((u32)TIM1_UP_IRQHandler,TIM1_UP_IRQn,0,ENABLE);
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
//
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
//    TIM_TimeBaseInitStructure.TIM_Prescaler = 144 / 2 - 1;
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 8 - 1;
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 25 - 1;  // test ok
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 40 - 1;  // 25 us ok
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 50 - 1;  // 20 us, ok
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 15 - 1;  // 15 us, no
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 200 - 1;  // 5 us
//    TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 * ms - 1;  // 1 ms
//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
//
//    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//    TIM_Cmd( TIM1, ENABLE );
//}

//u16 TxBuf[1024];
//s16 Calibrattion_Val = 0;

/*********************************************************************
 * @fn      DMA_Tx_Init
 *
 * @brief   Initializes the DMAy Channelx configuration.
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
//void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
//{
//    DMA_InitTypeDef DMA_InitStructure = {0};
//
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//    DMA_DeInit(DMA_CHx);
//    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
//    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//    DMA_InitStructure.DMA_BufferSize = bufsize;
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//    DMA_Init(DMA_CHx, &DMA_InitStructure);
//}

//void ADC_Function_Init(void)
//{
//    ADC_InitTypeDef  ADC_InitStructure = {0};
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
//
//    ADC_DeInit(ADC1);
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//
//    switch (kb_device) {
//        default:
//        case KB_DEVICE_KEYBOARD_ADC_DIFF:
//        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//        case KB_DEVICE_CNTLR_ADC:
////            ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//            ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//            ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//            ADC_InitStructure.ADC_NbrOfChannel = KB_ROW_NUM;
//            break;
//
////        case KB_DEVICE_COMPOSITE:
//        case KB_DEVICE_KEYBORAD:
//            ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//            ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//            ADC_InitStructure.ADC_NbrOfChannel = JS_NUM;
//            break ;
//
//        case KB_DEVICE_VENDOR:
//            ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//            ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//            ADC_InitStructure.ADC_NbrOfChannel = 1;
//            break;
//    }
//
//    ADC_Init(ADC1, &ADC_InitStructure);
//
//    ADC_DMACmd(ADC1, ENABLE);
//    ADC_Cmd(ADC1, ENABLE);
//
//    ADC_BufferCmd(ADC1, DISABLE); //disable buffer
//    ADC_ResetCalibration(ADC1);
//    while(ADC_GetResetCalibrationStatus(ADC1));
//    ADC_StartCalibration(ADC1);
//    while(ADC_GetCalibrationStatus(ADC1));
//    Calibrattion_Val = Get_CalibrationValue(ADC1);
//
//    ADC_BufferCmd(ADC1, ENABLE); //enable buffer
//}

/*******************************************************************************/
/* Interrupt Function Declaration */
//void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

//void eta_dischrg_exti_init() {
//    EXTI_InitTypeDef EXTI_InitStructure = { 0 };
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource13 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR13;
//
//    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init( &NVIC_InitStructure );
//}

//void kb_fn_exti_init() {
////    fn0, fn1
//    EXTI_InitTypeDef EXTI_InitStructure = { 0 };
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource8 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR8;
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource9 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR9;
//
//    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
//
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init( &NVIC_InitStructure );
//
////    fn2, fn3
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource14 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR14;
//}

//void PVD_Init(void)
//{
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
//    PWR_PVDLevelConfig(PWR_PVDLevel_2V9);
//    PWR_PVDCmd(ENABLE);
//}

//void PVD_NVIC_Config(void)
//{
//    EXTI_InitTypeDef EXTI_InitStructure = {0};
//    EXTI_InitStructure.EXTI_Line = EXTI_Line16;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//
//    NVIC_InitTypeDef NVIC_InitStructure = {0};
//    NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}

/*********************************************************************
 * @fn      TIM3_Init
 *
 * @brief   Initialize timer3 for keyboard and mouse scan.
 *
 * @param   arr - The specific period value
 *          psc - The specifies prescaler value
 *
 * @return  none
 */
//void TIM3_Init( uint16_t arr, uint16_t psc )
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = { 0 };
//    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
//
//    /* Enable Timer3 Clock */
//    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );
//
//    /* Initialize Timer3 */
//    TIM_TimeBaseStructure.TIM_Period = arr;
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );
//
//    TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );
//
//    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init( &NVIC_InitStructure );
//
//    /* Enable Timer3 */
//    TIM_Cmd( TIM3, ENABLE );
//}

/*********************************************************************
 * @fn      TIM3_IRQHandler
 *
 * @brief   This function handles TIM3 global interrupt request.
 *
 * @return  none
 */
//void TIM3_IRQHandler( void )
//{
//    if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
//    {
//        /* Clear interrupt flag */
//        TIM_ClearITPendingBit( TIM3, TIM_IT_Update );
//
//        /* Handle keyboard scan */
//        KB_Scan( );
//
//        /* Handle mouse scan */
//        MS_Scan( );
//
//        /* Start timing for uploading the key value received from USART2 */
//        if( USART_Send_Flag )
//        {
//            USART_Send_Cnt++;
//        }
//    }
//}

/*********************************************************************
 * @fn      USART2_Init
 *
 * @brief   Initialize UART2 to receive keyboard data sent through the
 *          PC serial software.
 *
 * @param   baudrate - Serial baud rate
 *
 * @return  none
 */
//void USART2_Init( uint32_t baudrate )
//{
//    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
//    USART_InitTypeDef USART_InitStructure = { 0 };
//    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
//
//    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init( GPIOA, &GPIO_InitStructure );
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init( GPIOA, &GPIO_InitStructure );
//
//    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init( &NVIC_InitStructure );
//
//    USART_InitStructure.USART_BaudRate = baudrate;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//
//    USART_Init( USART2, &USART_InitStructure );
//    USART_ITConfig( USART2, USART_IT_RXNE, ENABLE );
//    USART_Cmd( USART2, ENABLE );
//}

/*********************************************************************
 * @fn      USART2_IRQHandler
 *
 * @brief   This function handles USART2 global interrupt request.
 *
 * @return  none
 */
//void USART2_IRQHandler( void )
//{
//    if( USART_GetITStatus( USART2, USART_IT_RXNE) != RESET )
//    {
//        /* Save the key value received from USART2 */
//        USART_Recv_Dat = USART_ReceiveData( USART2 ) & 0xFF;
//    }
//}

/*********************************************************************
 * @fn      USART2_Receive_Handle
 *
 * @brief   This function handles the key value received from USART2.
 *
 * @return  none
 */
//void USART2_Receive_Handle( void )
//{
//    uint8_t status;
//    static uint8_t flag = 0x00;
//
//    if( flag == 0 )
//    {
//        /* Store the received specified key value into the keyboard data buffer */
//        if( ( USART_Recv_Dat == DEF_KEY_CHAR_A ) ||
//            ( USART_Recv_Dat == DEF_KEY_CHAR_W ) ||
//            ( USART_Recv_Dat == DEF_KEY_CHAR_S ) ||
//            ( USART_Recv_Dat == DEF_KEY_CHAR_D ) )
//        {
//            memset( KB_Data_Pack, 0x00, DEF_ENDP_SIZE_KB );
//            KB_Data_Pack[ 2 ] = USART_Recv_Dat;
//            flag = 1;
//        }
//    }
//    else if( flag == 1 )
//    {
//        /* Load keyboard data to endpoint 1 */
//        status = USBD_ENDPx_DataUp(ENDP1, KB_Data_Pack, DEF_ENDP_SIZE_KB);
//
//        if( status == USB_SUCCESS )
//        {
//            /* Enable timing for uploading the key value */
//            USART_Send_Cnt = 0;
//            USART_Send_Flag = 1;
//            flag = 2;
//        }
//    }
//    else if( flag == 2 )
//    {
//        /* Delay 10ms to ensure that the key value is successfully uploaded,
//         * and prepare the data packet indicating the key release.
//         */
//        if( USART_Send_Cnt >= 50 )
//        {
//            USART_Send_Flag = 0;
//            memset( KB_Data_Pack, 0x00, DEF_ENDP_SIZE_KB );
//            flag = 3;
//        }
//    }
//    else if( flag == 3 )
//    {
//        /* Load keyboard data to endpoint 1 */
//        status = USBD_ENDPx_DataUp(ENDP1, KB_Data_Pack, DEF_ENDP_SIZE_KB);
//        /* Clear variables for next reception */
//        if( status == USB_SUCCESS )
//        {
//            USART_Recv_Dat = 0;
//            flag = 0;
//        }
//    }
//}

/*********************************************************************
 * @fn      KB_Scan_Init
 *
 * @brief   Initialize IO for keyboard scan.
 *
 * @return  none
 */
//void KB_Scan_Init( void )
//{
//    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
//
//    /* Enable GPIOB clock */
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
//
//    /* Initialize GPIOB (Pin4-Pin7) for the keyboard scan */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init( GPIOB, &GPIO_InitStructure );
//}

/*********************************************************************
 * @fn      KB_Sleep_Wakeup_Cfg
 *
 * @brief   Configure keyboard wake up mode.
 *
 * @return  none
 */
//void KB_Sleep_Wakeup_Cfg( void )
//{
// EXTI_InitTypeDef EXTI_InitStructure = { 0 };
//
//    /* Enable GPIOB clock */
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource12 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource13 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource14 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource15 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line15;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR12 | EXTI_INTENR_MR13 | EXTI_INTENR_MR14 | EXTI_INTENR_MR15;
//}

/*********************************************************************
 * @fn      KB_Scan
 *
 * @brief   Perform keyboard scan.
 *
 * @return  none
 */
//void KB_Scan( void )
//{
//    static uint16_t scan_cnt = 0;
//    static uint16_t scan_result = 0;
//
//    scan_cnt++;
//    if( ( scan_cnt % 10 ) == 0 )
//    {
//        scan_cnt = 0;
//
//        /* Determine whether the two scan results are consistent */
//        if( scan_result == ( GPIO_ReadInputData( GPIOB ) & 0xF000 ) )
//        {
//            KB_Scan_Done = 1;
//            KB_Scan_Result = scan_result;
//        }
//    }
//    else if( ( scan_cnt % 5 ) == 0 )
//    {
//        /* Save the first scan result */
//        scan_result = ( GPIO_ReadInputData( GPIOB ) & 0xF000 );
//    }
//}

/*********************************************************************
 * @fn      KB_Scan_Handle
 *
 * @brief   Handle keyboard scan data.
 *
 * @return  none
 */
//void KB_Scan_Handle( void )
//{
//    uint8_t i, j;
//    uint8_t status;
//    static uint8_t key_cnt = 0x00;
//    static uint8_t flag = 0x00;
//    if( KB_Scan_Done )
//    {
//        KB_Scan_Done = 0;
//
//        if( KB_Scan_Result != KB_Scan_Last_Result )
//        {
//            for( i = 12; i < 16; i++ )
//            {
//                /* Determine that there is at least one key is pressed or released */
//                if( ( KB_Scan_Result & ( 1 << i ) ) != ( KB_Scan_Last_Result & ( 1 << i ) ) )
//                {
//                    if( ( KB_Scan_Result & ( 1 << i ) ) )           // Key press
//                    {
//                        if( i == 12 )
//                        {
//                            for( j = 2; j < 8; j++ )
//                            {
//                                if( KB_Data_Pack[ j ] == DEF_KEY_CHAR_W )
//                                {
//                                    break;
//                                }
//                            }
//                        }
//                        else if( i == 13 )
//                        {
//                            for( j = 2; j < 8; j++ )
//                            {
//                                if( KB_Data_Pack[ j ] == DEF_KEY_CHAR_A )
//                                {
//                                    break;
//                                }
//                            }
//                        }
//                        else if( i == 14 )
//                        {
//                            for( j = 2; j < 8; j++ )
//                            {
//                                if( KB_Data_Pack[ j ] == DEF_KEY_CHAR_S )
//                                {
//                                    break;
//                                }
//                            }
//                        }
//                        else if( i == 15 )
//                        {
//                            for( j = 2; j < 8; j++ )
//                            {
//                                if( KB_Data_Pack[ j ] == DEF_KEY_CHAR_D )
//                                {
//                                    break;
//                                }
//                            }
//                        }
//
//                        if( j == 8 )
//                        {
//                            KB_Data_Pack[ 5 ] = 0;
//                        }
//                        else
//                        {
//                            memcpy( &KB_Data_Pack[ j ], &KB_Data_Pack[ j + 1 ], ( 8 - j - 1 ) );
//                            KB_Data_Pack[ 7 ] = 0;
//                        }
//                        key_cnt--;
//                    }
//                    else                                            // Key release
//                    {
//                        if( i == 12 )
//                        {
//                            KB_Data_Pack[ 2 + key_cnt ] = DEF_KEY_CHAR_W;
//                        }
//                        else if( i == 13 )
//                        {
//                            KB_Data_Pack[ 2 + key_cnt ] = DEF_KEY_CHAR_A;
//                        }
//                        else if( i == 14 )
//                        {
//                            KB_Data_Pack[ 2 + key_cnt ] = DEF_KEY_CHAR_S;
//                        }
//                        else if( i == 15 )
//                        {
//                            KB_Data_Pack[ 2 + key_cnt ] = DEF_KEY_CHAR_D;
//                        }
//                        key_cnt++;
//                    }
//                }
//            }
//
//            /* Copy the keyboard data to the buffer of endpoint 1 and set the data uploading flag */
//            KB_Scan_Last_Result = KB_Scan_Result;
//            flag = 1;
//        }
//    }
//
//    if( flag )
//    {
//        /* Load keyboard data to endpoint 1 */
//        status = USBD_ENDPx_DataUp(ENDP1, KB_Data_Pack, DEF_ENDP_SIZE_KB);
//        if( status == USB_SUCCESS )
//        {
//            /* Clear flag after successful loading */
//            flag = 0;
//        }
//    }
//
//}


/*********************************************************************
 * @fn      KB_LED_Handle
 *
 * @brief   Handle keyboard lighting.
 *
 * @return  none
 */
//void KB_LED_Handle( void )
//{
//    if( KB_LED_Cur_Status != KB_LED_Last_Status )
//    {
//        if( ( KB_LED_Cur_Status & 0x01 ) != ( KB_LED_Last_Status & 0x01 ) )
//        {
//            if( KB_LED_Cur_Status & 0x01 )
//            {
//                printf("Turn on the NUM LED\r\n");
//            }
//            else
//            {
//                printf("Turn off the NUM LED\r\n");
//            }
//        }
//        if( ( KB_LED_Cur_Status & 0x02 ) != ( KB_LED_Last_Status & 0x02 ) )
//        {
//            if( KB_LED_Cur_Status & 0x02 )
//            {
//                printf("Turn on the CAPS LED\r\n");
//            }
//            else
//            {
//                printf("Turn off the CAPS LED\r\n");
//            }
//        }
//        if( ( KB_LED_Cur_Status & 0x04 ) != ( KB_LED_Last_Status & 0x04 ) )
//        {
//            if( KB_LED_Cur_Status & 0x04 )
//            {
//                printf("Turn on the SCROLL LED\r\n");
//            }
//            else
//            {
//                printf("Turn off the SCROLL LED\r\n");
//            }
//        }
//        KB_LED_Last_Status = KB_LED_Cur_Status;
//    }
//}


/*********************************************************************
 * @fn      MS_Scan_Init
 *
 * @brief   Initialize IO for mouse scan.
 *
 * @return  none
 */
//void MS_Scan_Init( void )
//{
//    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
//
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init( GPIOA, &GPIO_InitStructure );
//}

/*********************************************************************
 * @fn      MS_Sleep_Wakeup_Cfg
 *
 * @brief   Configure mouse wake up mode.
 *
 * @return  none
 */
//void MS_Sleep_Wakeup_Cfg( void )
//{
//    EXTI_InitTypeDef EXTI_InitStructure = { 0 };
//
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource4 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource5 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource6 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource7 );
//    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init( &EXTI_InitStructure );
//
//    EXTI->INTENR |= EXTI_INTENR_MR4 | EXTI_INTENR_MR5 | EXTI_INTENR_MR6 | EXTI_INTENR_MR7;
//}

/*********************************************************************
 * @fn      MS_Scan
 *
 * @brief   Perform mouse scan.
 *
 * @return  none
 */
//void MS_Scan( void )
//{
//    static uint16_t scan_cnt = 0;
//    static uint16_t scan_result = 0;
//
//    scan_cnt++;
//    if( scan_cnt >= 2 )
//    {
//        scan_cnt = 0;
//
//        /* Determine whether the two scan results are consistent */
//        if( scan_result == ( GPIO_ReadInputData( GPIOA ) & 0x00F0 ) )
//        {
//            MS_Scan_Result = scan_result;
//            MS_Scan_Done = 1;
//        }
//    }
//    else if( scan_cnt >= 1 )
//    {
//        /* Save the first scan result */
//        scan_result = ( GPIO_ReadInputData( GPIOA ) & 0x00F0 );
//    }
//}

/*********************************************************************
 * @fn      MS_Scan_Handle
 *
 * @brief   Handle mouse scan data.
 *
 * @return  none
 */
//void MS_Scan_Handle( void )
//{
//    uint8_t i;
//    uint8_t status;
//    static uint8_t flag = 0x00;
//
//    if( MS_Scan_Done )
//    {
//        MS_Scan_Done = 0;
//
//        memset( MS_Data_Pack, 0x00, DEF_ENDP_SIZE_MS );
//
//        for( i = 4; i < 8; i++ )
//        {
//            /* Determine that the mouse is moved */
//            if( ( MS_Scan_Result & ( 1 << i ) ) == 0 )
//            {
//                if( i == 4 )
//                {
//                    MS_Data_Pack[ 1 ] += 0x02;
//                }
//                else if( i == 5 )
//                {
//                    MS_Data_Pack[ 1 ] += 0xFE;
//                }
//                else if( i == 6 )
//                {
//                    MS_Data_Pack[ 2 ] += 0x02;
//                }
//                else if( i == 7 )
//                {
//                    MS_Data_Pack[ 2 ] += 0xFE;
//                }
//
//                /* Set the data uploading flag */
//                flag = 1;
//            }
//        }
//    }
//    if( flag )
//    {
//        /* Load mouse data to endpoint 2 */
//        status = USBD_ENDPx_DataUp(ENDP2, MS_Data_Pack, DEF_ENDP_SIZE_MS);
//        if( status == USB_SUCCESS )
//        {
//            /* Clear flag after successful loading */
//            flag = 0;
//        }
//    }
//}

/*********************************************************************
 * @fn      USB_Sleep_Wakeup_CFG
 *
 * @brief   Configure USB wake up mode
 *
 * @return  none
 */
void USB_Sleep_Wakeup_CFG( void )
{
    EXTI_InitTypeDef EXTI_InitStructure = { 0 };

    EXTI_InitStructure.EXTI_Line = EXTI_Line20;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init( &EXTI_InitStructure );
}

/*********************************************************************
 * @fn      MCU_Sleep_Wakeup_Operate
 *
 * @brief   Perform sleep operation
 *
 * @return  none
 */
void MCU_Sleep_Wakeup_Operate( void )
{
    EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
    EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );

//    printf( "Sleep\r\n" );
    __WFE( );

    if( EXTI_GetFlagStatus( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 ) != RESET  )
    {
        EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
        USBFS_Send_Resume( );
    }
    else if( EXTI_GetFlagStatus( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 ) != RESET )
    {
        EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );
        USBFS_Send_Resume( );
    }
//    printf( "Wake\r\n" );
}



