#include "joystick.h"
#include "ch32v20x.h"
#include "app.h"

uint16_t js_axis_adc[JS_NUM];

void joystick_gpio_init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // axis
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = JS_A1_GPIO_PIN | JS_A2_GPIO_PIN;
    GPIO_Init(JS_A1_GPIO_PORT, &GPIO_InitStructure);
    // switch
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = JS_SW_GPIO_PIN;
    GPIO_Init(JS_SW_GPIO_PORT, &GPIO_InitStructure);
}

void joystick_adc_dma_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);
    ADC_InitTypeDef ADC_InitStructure = {0};
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_NbrOfChannel = JS_NUM;

//    switch (kb_device) {
//        default:
//        case KB_DEVICE_KEYBOARD_ADC_DIFF:
//        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//        case KB_DEVICE_CNTLR_ADC:
//            //            ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//            ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//            ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//            ADC_InitStructure.ADC_NbrOfChannel = KB_ROW_NUM;
//            break;

            //        case KB_DEVICE_COMPOSITE:
//        case KB_DEVICE_KEYBORAD:
//            break ;

//        case KB_DEVICE_VENDOR:
//            ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//            ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//            ADC_InitStructure.ADC_NbrOfChannel = 1;
//            break;
//    }

    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_BufferCmd(ADC1, DISABLE); //disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    s16 Calibrattion_Val = 0;
    Calibrattion_Val = Get_CalibrationValue(ADC1);
    ADC_BufferCmd(ADC1, ENABLE); //enable buffer

    DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)js_axis_adc, JS_NUM);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_71Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_71Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//void joystick_adc_dma_2() {
//    switch (kb_device) {
//        default:
//        case KB_DEVICE_KEYBORAD:
            //        case KB_DEVICE_COMPOSITE:

//joystick_adc_dma_init();
// t = 1 / 12Mhz
// longest 71Cycles5 = 7 * 6 us
//            break;

//        case KB_DEVICE_KEYBOARD_ADC_DIFF:
//        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
//        case KB_DEVICE_CNTLR_ADC:
//            DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)kb_row_adc, KB_ROW_NUM);
//            DMA_Cmd(DMA1_Channel1, ENABLE);
//
//            joystick_adc_dma_init();
//            // t = 1 / 12Mhz
//            // 71Cycles5 = 7 us
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

//        case KB_DEVICE_VENDOR:
//            DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)kb_adc_value, KB_ADC_SIZE);
//            DMA_Cmd(DMA1_Channel1, ENABLE);
//
//            joystick_adc_dma_init();
//            ADC_RegularChannelConfig(ADC1, 0, 1, ADC_SampleTime_1Cycles5);
//            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//            break;
//    }
//}

void joystick_scan() {
    static uint8_t js_sw_state;
    if (GPIO_ReadInputDataBit(JS_SW_GPIO_PORT, JS_SW_GPIO_PIN) == JS_SW_PRESS) {
        if (js_sw_state != JS_SW_PRESS) {
            js_sw_state = TRUE;
//            printf("js_sw: 1\n");
        }
    }  else if (js_sw_state == JS_SW_PRESS && GPIO_ReadInputDataBit(JS_SW_GPIO_PORT, JS_SW_GPIO_PIN) != JS_SW_PRESS) {
        js_sw_state = FALSE;
//        printf("js_sw: 0\n");
    }
//    printf("a1:%d\n", js_axis_adc[0]);
//    printf("a2:%d\n", js_axis_adc[1]);
}