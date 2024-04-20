#include "led.h"
#include "ch32v20x.h"
#include "wchble.h"

void led_gpio_init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2 | GPIO_PartialRemap_TIM3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin = LED_B_PIN;
//    GPIO_Init(LED_B_PORT, &GPIO_InitStructure);
//    GPIO_ResetBits(LED_B_PORT, LED_B_PIN);
//
//    GPIO_InitStructure.GPIO_Pin = LED_G_PIN;
//    GPIO_Init(LED_G_PORT, &GPIO_InitStructure);
//    GPIO_ResetBits(LED_G_PORT, LED_G_PIN);
//
//    GPIO_InitStructure.GPIO_Pin = LED_R_PIN;
//    GPIO_Init(LED_R_PORT, &GPIO_InitStructure);
//    GPIO_ResetBits(LED_R_PORT, LED_R_PIN);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void led_tim_init(u16 arr, u16 psc, u16 ccp, TIM_TypeDef *tim)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(tim, &TIM_TimeBaseInitStructure);

    //    TIM_DMAConfig(tim, TIM_DMABase_CCR1, TIM_DMABurstLength_4Bytes);
//    TIM_DMACmd(tim, TIM_DMA_Update, ENABLE);

    TIM_CtrlPWMOutputs(tim, ENABLE);

    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    if (tim == TIM3) {
        TIM_OC1Init(tim, &TIM_OCInitStructure);
        TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);
    }
    TIM_OC2Init(tim, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(tim, TIM_OCPreload_Enable);

    //    TIM_OC3Init(tim, &TIM_OCInitStructure);
//    TIM_OC3PreloadConfig(tim, TIM_OCPreload_Enable);

//    TIM_OC4Init(tim, &TIM_OCInitStructure);
//    TIM_OC4PreloadConfig(tim, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(tim, ENABLE);

    TIM_Cmd(tim, ENABLE);
}

void ws2812b_dma_init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize) {
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitTypeDef          DMA_InitStructure={0};
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
}

void led_red_on() {
    TIM_SetCompare2(TIM2, 1);
}

void led_red_off() {
    TIM_SetCompare2(TIM2, 0);
}

void led_green_on() {
    TIM_SetCompare1(TIM3, 1);
}

void led_green_off() {
    TIM_SetCompare1(TIM3, 0);
}

void led_blue_on() {
    TIM_SetCompare2(TIM3, 1);
}

void led_blue_off() {
    TIM_SetCompare2(TIM3, 0);
}

void led_ctl(uint8_t color, uint8_t status){
    if (status == TRUE) {
        switch (color) {
            default:
                break;
            case 0:
                GPIO_ResetBits(LED_R_PORT,LED_R_PIN);
                break;
            case 1:
                GPIO_ResetBits(LED_G_PORT,LED_G_PIN);
                break;
            case 2:
                GPIO_ResetBits(LED_B_PORT,LED_B_PIN);
                break;
        }
    } else {
        switch (color) {
            default:
                break;
            case 0:
                GPIO_SetBits(LED_R_PORT,LED_R_PIN);
                break;
            case 1:
                GPIO_SetBits(LED_G_PORT,LED_G_PIN);
                break;
            case 2:
                GPIO_SetBits(LED_B_PORT,LED_B_PIN);
                break;
        }
    }
}