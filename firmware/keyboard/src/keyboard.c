#include "keyboard.h"
#include "HAL.h"
#include "joystick.h"
#include "led.h"
#include "tmos-power-manager.h"


const uint16_t KB_COL_GPIO_PIN[KB_COL_NUM] = {
        KB_COL_0_GPIO_PIN, KB_COL_1_GPIO_PIN, KB_COL_2_GPIO_PIN,KB_COL_3_GPIO_PIN,
        KB_COL_4_GPIO_PIN, KB_COL_5_GPIO_PIN,KB_COL_6_GPIO_PIN};
GPIO_TypeDef* const KB_COL_GPIO_PORT[KB_COL_NUM] = {
        KB_COL_0_GPIO_PORT, KB_COL_1_GPIO_PORT, KB_COL_2_GPIO_PORT,KB_COL_3_GPIO_PORT,
        KB_COL_4_GPIO_PORT, KB_COL_5_GPIO_PORT, KB_COL_6_GPIO_PORT};

uint8_t kb_col_curr = 0, kb_row_curr = 0;
uint8_t (*kb_layout)[KB_COL_NUM] = kb_lyrs[0];
bool kb_key_state[KB_ROW_NUM][KB_COL_NUM] = {};
uint32_t kb_flag;
uint8_t kb_key_count = 0;

uint32_t kb_ctl = 0;

uint8_t kb_row_read = 0;
static uint16_t kb_adc_value[KB_ADC_SIZE] = {}, kb_adc_buf1[KB_ADC_SIZE] = {};


#if KB_SIDE == KB_SIDE_LEFT
    static uint8_t kb_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
        // dovrak debug
//        KEY_OBRACKET_AND_OBRACE, KEY_6_CARET, KEY_7_AMPERSAND, KEY_8_ASTERISK, KEY_9_OPARENTHESIS, KEY_0_CPARENTHESIS, KEY_CBRACKET_AND_CBRACE,
//        KEY_EQUAL_PLUS, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_BACKSLASH_VERTICAL_BAR,
//        KEY_TAB, KEY_SINGLE_AND_DOUBLE_QUOTE, KEY_COMMA_AND_LESS, KEY_DOT_GREATER, KEY_P, KEY_Y, KEY_PAGEUP,
//        KEY_ENTER, KEY_A, KEY_O, KEY_E, KEY_U, KEY_I, KEY_PAGEDOWN,
//        KEY_LEFT_SHIFT, KEY_SEMICOLON_COLON, KEY_Q, KEY_J, KEY_K, KEY_X, KEY_END,
//        KEY_EQUAL_PLUS, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_BACKSLASH_VERTICAL_BAR,

        // dovrak
        KEY_ESCAPE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_DELETE,
        KEY_GRAVE_ACCENT_AND_TILDE, KEY_1_EXCLAMATION_MARK, KEY_2_AT, KEY_3_NUMBER_SIGN, KEY_4_DOLLAR, KEY_5_PERCENT, KEY_HOME,
        KEY_TAB, KEY_SINGLE_AND_DOUBLE_QUOTE, KEY_COMMA_AND_LESS, KEY_DOT_GREATER, KEY_P, KEY_Y, KEY_PAGEUP,
        KEY_ENTER, KEY_A, KEY_O, KEY_E, KEY_U, KEY_I, KEY_PAGEDOWN,
        KEY_LEFT_SHIFT, KEY_SEMICOLON_COLON, KEY_Q, KEY_J, KEY_K, KEY_X, KEY_END,
        KEY_UPARROW, KEY_DOWNARROW, KEY_LEFTARROW, KEY_RIGHTARROW, KEY_LEFT_CONTROL, KEY_SPACEBAR, KEY_LEFT_ALT,

        // qwert game, shift instead of alt
        KEY_ESCAPE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_DELETE,
        KEY_GRAVE_ACCENT_AND_TILDE, KEY_1_EXCLAMATION_MARK, KEY_2_AT, KEY_3_NUMBER_SIGN, KEY_4_DOLLAR, KEY_5_PERCENT, KEY_HOME,
        KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_PAGEUP,
        KEY_ENTER, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_PAGEDOWN,
        KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_END,
        KEY_UPARROW, KEY_DOWNARROW, KEY_LEFTARROW, KEY_RIGHTARROW, KEY_LEFT_CONTROL, KEY_SPACEBAR, KEY_LEFT_SHIFT,

        // qwert
        KEY_ESCAPE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_DELETE,
        KEY_GRAVE_ACCENT_AND_TILDE, KEY_1_EXCLAMATION_MARK, KEY_2_AT, KEY_3_NUMBER_SIGN, KEY_4_DOLLAR, KEY_5_PERCENT, KEY_HOME,
        KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_PAGEUP,
        KEY_ENTER, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_PAGEDOWN,
        KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_END,
        KEY_UPARROW, KEY_DOWNARROW, KEY_LEFTARROW, KEY_RIGHTARROW, KEY_LEFT_CONTROL, KEY_SPACEBAR, KEY_LEFT_ALT,
    };

    static uint8_t kb_cntlr_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
        CNTLR_BACK, CNTLR_LEFT_STICK_BUTTON, CNTLR_LEFT_STICK_LEFT, CNTLR_LEFT_STICK_RIGHT, CNTLR_LEFT_STICK_UP, CNTLR_LEFT_STICK_DOWN, CNTLR_NONE,
        CNTLR_START, CNTLR_RIGHT_STICK_BUTTON, CNTLR_RIGHT_STICK_LEFT, CNTLR_RIGHT_STICK_RIGHT, CNTLR_RIGHT_STICK_UP, CNTLR_RIGHT_STICK_DOWN, CNTLR_NONE,
        CNTLR_RIGHT_BUMPER, CNTLR_RIGHT_TRIGGER, CNTLR_A, CNTLR_B, CNTLR_X, CNTLR_Y, CNTLR_NONE,
        CNTLR_LEFT_BUMPER, CNTLR_LEFT_TRIGGER, CNTLR_DPAD_LEFT, CNTLR_DPAD_RIGHT, CNTLR_DPAD_UP, CNTLR_DPAD_DOWN, CNTLR_NONE,
        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
    };

    static uint8_t mouse_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
            CNTLR_BUTTON_1, CNTLR_BUTTON_2, CNTLR_BUTTON_3, CNTLR_BUTTON_4, CNTLR_BUTTON_5, CNTLR_BUTTON_6, CNTLR_BUTTON_7,
            CNTLR_BUTTON_8, CNTLR_BUTTON_9, CNTLR_BUTTON_10, CNTLR_BUTTON_11, CNTLR_BUTTON_12, CNTLR_BUTTON_13, CNTLR_BUTTON_14,
            CNTLR_BUTTON_15, CNTLR_BUTTON_16, 0x10, 0x11, 0x12, 0x13, 0x14,
            0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b,
            0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
            0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,

            MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
            MOUSE_BUTTON_1, MOUSE_BUTTON_2, MOUSE_BUTTON_3, MOUSE_BUTTON_4, MOUSE_BUTTON_5, MOUSE_BUTTON_6, MOUSE_BUTTON_7,
            MOUSE_NONE, MOUSE_NONE, MOUSE_WHEEL_NEG, MOUSE_Y_POS, MOUSE_WHEEL_POS, MOUSE_NONE, MOUSE_NONE,
            MOUSE_NONE, MOUSE_NONE, MOUSE_X_NEG, MOUSE_Y_NEG, MOUSE_X_POS, MOUSE_BUTTON_8, MOUSE_NONE,
            MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
            MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
    };
#else
    static uint8_t kb_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
        KEY_F12, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11,
        KEY_OBRACKET_AND_OBRACE, KEY_6_CARET, KEY_7_AMPERSAND, KEY_8_ASTERISK, KEY_9_OPARENTHESIS, KEY_0_CPARENTHESIS, KEY_CBRACKET_AND_CBRACE,
        KEY_EQUAL_PLUS, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_BACKSLASH_VERTICAL_BAR,
        KEY_MINUS_UNDERSCORE, KEY_D, KEY_H, KEY_T, KEY_N, KEY_S, KEY_BACKSPACE,
        KEY_SLASH_QUESTION, KEY_B, KEY_M, KEY_W, KEY_V, KEY_Z, KEY_RIGHT_SHIFT,
        KEY_RIGHT_ALT, KEY_SPACEBAR, KEY_RIGHT_CONTROL, KEY_RIGHT_GUI, KEY_INSERT, KEY_PRINTSCREEN, KEY_FN,

        KEY_F12, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11,
        KEY_OBRACKET_AND_OBRACE, KEY_6_CARET, KEY_7_AMPERSAND, KEY_8_ASTERISK, KEY_9_OPARENTHESIS, KEY_0_CPARENTHESIS, KEY_CBRACKET_AND_CBRACE,
        KEY_EQUAL_PLUS, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BACKSLASH_VERTICAL_BAR,
        KEY_MINUS_UNDERSCORE, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON_COLON, KEY_BACKSPACE,
        KEY_SLASH_QUESTION, KEY_N, KEY_M, KEY_COMMA_AND_LESS, KEY_DOT_GREATER, KEY_SINGLE_AND_DOUBLE_QUOTE, KEY_RIGHT_SHIFT,
        KEY_RIGHT_ALT, KEY_SPACEBAR, KEY_RIGHT_CONTROL, KEY_RIGHT_GUI, KEY_CAPS_LOCK, KEY_PRINTSCREEN, KEY_FN,

};

    static uint8_t kb_cntlr_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
        CNTLR_BUTTON_1, CNTLR_BUTTON_2, CNTLR_BUTTON_3, CNTLR_BUTTON_4, CNTLR_BUTTON_5, CNTLR_BUTTON_6, CNTLR_BUTTON_7,
        CNTLR_BUTTON_8, CNTLR_BUTTON_9, CNTLR_BUTTON_10, CNTLR_BUTTON_11, CNTLR_BUTTON_12, CNTLR_BUTTON_13, CNTLR_BUTTON_14,
        CNTLR_BUTTON_15, CNTLR_BUTTON_16, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
        0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,

        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_RIGHT_STICK_UP, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
        CNTLR_NONE, CNTLR_NONE, CNTLR_RIGHT_STICK_LEFT, CNTLR_RIGHT_STICK_DOWN, CNTLR_RIGHT_STICK_RIGHT, CNTLR_Y, CNTLR_NONE,
        CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
        CNTLR_RIGHT_STICK_BUTTON, CNTLR_LEFT_TRIGGER, CNTLR_RIGHT_TRIGGER, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE, CNTLR_NONE,
    };

    static uint8_t mouse_lyrs[KB_LYR_NUM][KB_ROW_NUM][KB_COL_NUM] = {
        CNTLR_BUTTON_1, CNTLR_BUTTON_2, CNTLR_BUTTON_3, CNTLR_BUTTON_4, CNTLR_BUTTON_5, CNTLR_BUTTON_6, CNTLR_BUTTON_7,
        CNTLR_BUTTON_8, CNTLR_BUTTON_9, CNTLR_BUTTON_10, CNTLR_BUTTON_11, CNTLR_BUTTON_12, CNTLR_BUTTON_13, CNTLR_BUTTON_14,
        MOUSE_NONE, MOUSE_NONE, MOUSE_WHEEL_NEG, MOUSE_Y_POS, MOUSE_WHEEL_POS, MOUSE_NONE, MOUSE_NONE,
        MOUSE_NONE, MOUSE_NONE, MOUSE_X_NEG, MOUSE_Y_NEG, MOUSE_X_POS, MOUSE_BUTTON_8, MOUSE_NONE,
        0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
        0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,

        MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
        MOUSE_BUTTON_1, MOUSE_BUTTON_2, MOUSE_BUTTON_3, MOUSE_BUTTON_4, MOUSE_BUTTON_5, MOUSE_BUTTON_6, MOUSE_BUTTON_7,
        MOUSE_NONE, MOUSE_NONE, MOUSE_WHEEL_NEG, MOUSE_Y_POS, MOUSE_WHEEL_POS, MOUSE_NONE, MOUSE_NONE,
        MOUSE_NONE, MOUSE_NONE, MOUSE_X_NEG, MOUSE_Y_NEG, MOUSE_X_POS, MOUSE_BUTTON_8, MOUSE_NONE,
        MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
        MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE, MOUSE_NONE,
    };
#endif

void kb_col_gpio_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);

    //    for (int i = 0; i < KB_COL_NUM; ++i) {
    //        GPIO_InitStructure.GPIO_Pin   = KB_COL_GPIO_PIN[i];
    //        GPIO_Init(KB_COL_GPIO_PORT[i], &GPIO_InitStructure);
    //        GPIO_ResetBits(KB_COL_GPIO_PORT[i],KB_COL_GPIO_PIN[i]);
    //    }
}

void kb_row_gpio_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = KB_ROW_0_GPIO_PIN | KB_ROW_1_GPIO_PIN | KB_ROW_2_GPIO_PIN |
                                  KB_ROW_3_GPIO_PIN | KB_ROW_4_GPIO_PIN | KB_ROW_5_GPIO_PIN;
    GPIO_Init(KB_ROW_GPIO_PORT, &GPIO_InitStructure);
}

void kb_row_gpio_adc_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = KB_ROW_0_GPIO_PIN | KB_ROW_1_GPIO_PIN | KB_ROW_2_GPIO_PIN |
                                  KB_ROW_3_GPIO_PIN | KB_ROW_4_GPIO_PIN | KB_ROW_5_GPIO_PIN;
    GPIO_Init(KB_ROW_GPIO_PORT, &GPIO_InitStructure);
}

void kb_adc_dma_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(ADC1);
    ADC_InitTypeDef ADC_InitStructure = {0};
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_NbrOfChannel = KB_ROW_NUM;

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

    DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)kb_row_adc, KB_ROW_NUM);
    DMA_Cmd(DMA1_Channel1, ENABLE);

#define KEYBOARD_ADC_SampleTime ADC_SampleTime_71Cycles5
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, KEYBOARD_ADC_SampleTime);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, KEYBOARD_ADC_SampleTime);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, KEYBOARD_ADC_SampleTime);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, KEYBOARD_ADC_SampleTime);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, KEYBOARD_ADC_SampleTime);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, KEYBOARD_ADC_SampleTime);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void kb_fn_gpio_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}



//void TIM1_Init()
//{
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//
//    NVIC_EnableIRQ(TIM1_UP_IRQn);
//    SetVTFIRQ((u32)TIM1_UP_IRQHandler,TIM1_UP_IRQn,0,ENABLE);
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
//
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
//    TIM_TimeBaseInitStructure.TIM_Prescaler = 144 / 2 - 1;

////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 8 - 1;
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 25 - 1;  // test ok
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 40 - 1;  // 25 us ok
//            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 50 - 1;  // 20 us, ok
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 15 - 1;  // 15 us, no
////            TIM_TimeBaseInitStructure.TIM_Period = 2 * 1000 / 200 - 1;  // 5 us
////            break;

//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
//
//    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//    TIM_Cmd( TIM1, ENABLE );
//}

void kb_fn_exti_init() {
    //    fn0, fn1
    EXTI_InitTypeDef EXTI_InitStructure = { 0 };

    //    GPIO_EXTILineConfig( GPIO_PortSourceGPIOC, GPIO_PinSource13 );
    //    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    //    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    //    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //    EXTI_Init( &EXTI_InitStructure );
    //
    //    EXTI->INTENR |= EXTI_INTENR_MR13;
    //
    //    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource2 );
    //    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    //    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    //    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //    EXTI_Init( &EXTI_InitStructure );
    //
    //    EXTI->INTENR |= EXTI_INTENR_MR2;

    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    //    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    //    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    //    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //    NVIC_Init( &NVIC_InitStructure );

    //    fn2,
    //    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource13 );
    //    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    //    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    //    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //    EXTI_Init( &EXTI_InitStructure );
    //
    //    EXTI->INTENR |= EXTI_INTENR_MR13;

    //    fn3
    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource14 );
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init( &EXTI_InitStructure );

    EXTI->INTENR |= EXTI_INTENR_MR14;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );
}

void kb_fn_exti_event_init() {
    EXTI_InitTypeDef EXTI_InitStructure = { 0 };
    //    fn3
    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource14 );
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init( &EXTI_InitStructure );

    EXTI->INTENR |= EXTI_INTENR_MR14;

    NVIC_InitTypeDef NVIC_InitStructure = { 0 };
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );
}

void kb_digtal_analog_select() {
//    kb_device = KB_DEVICE_COMPOSITE;
    kb_device = KB_DEVICE_KEYBORAD;
//    kb_device = KB_DEVICE_VENDOR;
//    kb_device = KB_DEVICE_KEYBOARD_ADC_DIFF;
//    kb_device = KB_DEVICE_KEYBOARD_ADC_TRIGGER;
//    kb_device = KB_DEVICE_CNTLR_ADC;
//    kb_device = KB_DEVICE_CNTLR;

    if ((kb_ctl & KB_CTL_HOST) != 0) {
        kb_rep_send = kb_report_usbhd;
    } else {
        kb_rep_send = kb_report_usbd;
    }
//    printf("kb_ctl:%02lx\n", kb_ctl);
}

void kb_enable_usbd() {
    kb_ctl |= KB_CTL_USBD;
//    printf("kb_ctl:%02lx\n", kb_ctl);
    led_green_on();
    Delay_Ms(500);
    led_green_off();
}

void keyboard_scan_delay() {
    for (kb_col_curr = 0; kb_col_curr < KB_COL_NUM; ++kb_col_curr) {
        GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
        Delay_Us(KB_PHOTO_DELAY_US);

        keyboard_row_read();
//        keyboard_row_read_adc_trigger();
//        keyboard_row_read_adc_diff();
        GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);

        for (kb_row_curr = 0; kb_row_curr < KB_ROW_NUM; ++kb_row_curr) {
            keyboard_trigger_handler();
        }
    }
}

void keyboard_fn_scan() {
    static uint8_t fn_state[4];

    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14) == KB_FN_PRESS) {
        if (fn_state[0] != KB_FN_PRESS) {
            fn_state[0] = KB_FN_PRESS;
            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
        }
    }

    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == KB_FN_PRESS) {
        static uint8_t tmp_layer;
        if (fn_state[1] != KB_FN_PRESS) {
            fn_state[1] = KB_FN_PRESS;
            if (tmp_layer == 0) {
                tmp_layer = 1;
            } else {
                tmp_layer = 0;
            }
            keyboard_layer_select(tmp_layer);
        }
    } else if (fn_state[1] == KB_FN_PRESS && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) != KB_FN_PRESS) {
        fn_state[1] = KB_FN_RELESE;
    }

    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == KB_FN_PRESS) {
        if (fn_state[2] != KB_FN_PRESS) {
            fn_state[2] = KB_FN_PRESS;

            static uint8_t usb_vbus_state = 0;
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == SET) {
                printf("vbus: on\n");
                usb_vbus_state = 1;
            } else {
                printf("vbus: off\n");
                usb_vbus_state = 0;
            }

            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == RESET) {
                printf("stat: charging\n");
            } else {
                printf("stat: not charg, or charg finish\n");
            }

            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == RESET) {
                printf("discharg: discharging\n");
            } else {
                printf("discharg: not discharging\n");
            }

//            eta9184_pulse_it_init();
//            eta9184_pulse_tim_init();
//            uint16_t boost_adc = eta9184_adc_get();
//            printf("%d\n", boost_adc);
        }
    } else if (fn_state[2] == KB_FN_PRESS && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) != KB_FN_PRESS) {
        fn_state[2] = KB_FN_RELESE;
    }

    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == KB_FN_PRESS) {
        if (fn_state[3] != KB_FN_PRESS) {
            fn_state[3] = KB_FN_PRESS;
//            tmos_connection_mode()
//            if (kb_col_curr<KB_COL_NUM-1) {
//                GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
//                ++kb_col_curr;
//                GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
//            } else {
//                GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
//                kb_col_curr = 0;
//                GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
//            }
            led_blue_on();
        }
    } else if (fn_state[3] == KB_FN_PRESS && GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) != KB_FN_PRESS) {
        fn_state[3] = KB_FN_RELESE;
        led_blue_off();
    }

//    if (EXTI_GetITStatus(EXTI_Line15) == SET) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == SET) {
            //            printf("usb in\n");
        } else {
            //            printf("usb out\n");
            OnBoard_SendMsg(tmos_pm_id, PM_ENTER_STANDBY_MSG, 1, NULL);
        }
//        EXTI_ClearITPendingBit(EXTI_Line15);
//    }
}

void keyboard_scan_it() {
    static uint8_t kb_it_count = 0;
    switch (kb_it_count) {
        case KB_IT_CASE0:
            GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);

            keyboard_usb_send();

            ++kb_it_count;
            break;

        case KB_IT_CASE1:
        case KB_IT_CASE2:
        case KB_IT_CASE3:
        case KB_IT_CASE4:
        case KB_IT_CASE5:
        case KB_IT_CASE6:
            keyboard_row_read();

            GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
            GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr + 1], KB_COL_GPIO_PIN[kb_col_curr + 1]);

            keyboard_row_handler();

            ++kb_col_curr;
            ++kb_it_count;
            break;

        case KB_IT_CASE7:
            keyboard_row_read();

            GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);

            keyboard_row_handler();
//            kb_usbhd_combine();
//            keyboard_usb_send();

//            usbh_epin_time();
//            USBH_MainDeal();

            kb_it_count = 0;
            kb_col_curr = 0;
//            TIM_Cmd( TIM1, DISABLE );
            break;

        default:
            ++kb_it_count;
            break;
    }
}


void kb_scan_it_adc() {
    static uint8_t kb_it_count = 0;
    switch (kb_it_count) {
        case KB_IT_CASE0:
            GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
            keyboard_usb_send();
            ++kb_it_count;
            break;

            //        case KB_IT_CASE0 + KB_IT_TICK:
            //        case KB_IT_CASE1 + KB_IT_TICK:
            //        case KB_IT_CASE2 + KB_IT_TICK:
            //        case KB_IT_CASE3 + KB_IT_TICK:
            //        case KB_IT_CASE4 + KB_IT_TICK:
            //        case KB_IT_CASE5 + KB_IT_TICK:
            //        case KB_IT_CASE6 + KB_IT_TICK:
            //            joystick_adc_dma_2();
            //            break;
            //
        case KB_IT_CASE0 + KB_IT_TICK_ADC:
        case KB_IT_CASE1 + KB_IT_TICK_ADC:
        case KB_IT_CASE2 + KB_IT_TICK_ADC:
        case KB_IT_CASE3 + KB_IT_TICK_ADC:
        case KB_IT_CASE4 + KB_IT_TICK_ADC:
        case KB_IT_CASE5 + KB_IT_TICK_ADC:
        case KB_IT_CASE6 + KB_IT_TICK_ADC:
            keyboard_row_read();

            GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);
            GPIO_SetBits(KB_COL_GPIO_PORT[kb_col_curr + 1], KB_COL_GPIO_PIN[kb_col_curr + 1]);

            keyboard_row_handler();

            ++kb_col_curr;
            ++kb_it_count;
            break;

        case KB_IT_CASE7:
            keyboard_row_read();

            GPIO_ResetBits(KB_COL_GPIO_PORT[kb_col_curr], KB_COL_GPIO_PIN[kb_col_curr]);

            keyboard_row_handler();
            //            kb_usbhd_combine();
            //            keyboard_usb_send();

            //            usbh_epin_time();
            //            USBH_MainDeal();

            kb_it_count = 0;
            kb_col_curr = 0;
            //            TIM_Cmd( TIM1, DISABLE );
            break;

        default:
            ++kb_it_count;
            break;
    }
}

void keyboard_layer_select(uint8_t lyr) {
    kb_layout = kb_lyrs[lyr];
}

void keyboard_fn_handler() {
//    static uint8_t kb_fn = 0;
//    bool key_status = kb_key_state[kb_row_curr][kb_col_curr];
//    if (kb_layout[kb_row_curr][kb_col_curr] == KEY_FN) {
//        if (KB_PRESS == key_status) {
//            kb_ctl |= KB_FLAG_FN;
//            kb_ctl &= ~KB_CTL_USBD;
//            kb_flag &= ~KB_FLAG_COUNT;
//        } else {
//            kb_ctl &= ~KB_FLAG_FN;
//            kb_ctl |= KB_CTL_USBD;
//            kb_flag &= ~KB_FLAG_COUNT;
//        }
//    } else {
//        if (key_status == KB_PRESS) {
        switch (kb_layout[kb_row_curr][kb_col_curr]) {
            default:
                break;

            case KEY_F1:
            case KEY_F6: {
                static uint8_t lyr;
                if (lyr == 0) {
                    lyr = 1;
                    keyboard_layer_select(lyr);
                } else {
                    lyr = 0;
                    keyboard_layer_select(lyr);
                }
//                kb_flag &= ~KB_FLAG_FN;
                break;
            }

            case KEY_F2:
            case KEY_F7: {
                switch (kb_device) {
                    default:
                        kb_device = KB_DEVICE_KEYBORAD;
//                        printf("KB_DEVICE_COMPOSITE: %d\n", kb_device);
                        break;

                    case KB_DEVICE_KEYBORAD:
                        kb_device = KB_DEVICE_CNTLR;
//                        printf("KB_DEVICE_CNTLR: %d\n", kb_device);
                        break;

                    case KB_DEVICE_CNTLR:
                        kb_device = KB_DEVICE_MOUSE;
//                        printf("KB_DEVICE_MOUSE: %d\n", kb_device);
                        break;

                    case KB_DEVICE_MOUSE:
                        kb_device = KB_DEVICE_KEYBORAD;
//                        printf("KB_DEVICE_COMPOSITE: %d\n", kb_device);
                        break;
                }
                break;
            }

            case KEY_F3:
            case KEY_F8:
                //                    kb_fn = kb_fn_usb;
                //                if (kb_ctl & KB_CTL_USBD) {
                //                    kb_ctl &= ~KB_CTL_USBD;
                //                } else {
                //                    kb_ctl |= KB_CTL_USBD;
                //                }
                break;

//            case KEY_F4:
//            case KEY_F9:
//                if (kb_repeat == KB_REPEAT_SLOW) {
//                    kb_repeat = KB_REPEAT_NONE;
//                    printf("KB_REPEAT_NONE\n");
//                } else {
//                    kb_repeat = KB_REPEAT_SLOW;
//                    printf("KB_REPEAT_SLOW\n");
//                }
//                break;


//            case KEY_F5:
//            case KEY_F10:
////                    kb_fn = kb_fn_lyr;
//                if (kb_repeat == KB_REPEAT_FAST) {
////                    kb_ctl &= ~KB_CTL_REPEAT;
//                    kb_repeat = KB_REPEAT_NONE;
//                    printf("KB_REPEAT_NONE: %d\n", kb_repeat);
//                } else {
//                    kb_repeat = KB_REPEAT_FAST;
//                    printf("KB_REPEAT_FAST: %d\n", kb_repeat);
//                }
////                kb_flag &= ~KB_FLAG_FN;
//                break;
       }
//        }
//        if (kb_row_curr == 0) {
//            if (key_status == KB_PRESS) {
//                switch (kb_layout[kb_row_curr][kb_col_curr]) {
//                    case KEY_F1:
//                    case KEY_F6:
//                        kb_fn = kb_fn_lyr;
//                        break;
//                    case KEY_F2:
//                    case KEY_F7:
////                        kb_fn = kb_fn_led;
//                        kb_fn = kb_fn_ctl;
//                        break;
//                    case KEY_F3:
//                    case KEY_F8:
//                        kb_fn = kb_fn_uart;
//                        break;
//                    case KEY_F4:
//                    case KEY_F9:
//                        kb_fn = kb_fn_ms;
//                        break;
//                    case KEY_F5:
//                    case KEY_F10:
//                        kb_fn = kb_fn_usb;
//                        break;
//                    default:
//                        break;
//                }
//            } else {
//                kb_fn = kb_fn_none;
//            }
//        } else if ((kb_row_curr == 1) && (key_status == KB_PRESS)) {
//            switch (kb_layout[kb_row_curr][kb_col_curr]) {
//                case KEY_1_EXCLAMATION_MARK:
//                case KEY_6_CARET:
//                    switch (kb_fn) {
//                        case kb_fn_lyr:
//                            keyboard_layer_select(0);
//                            break;
//                        case kb_fn_led:
////                            leds_off();
//                            break;
//                        case kb_fn_uart:
//                            kb_ctl &= ~KB_CTL_USART;
//                            kb_rep_send = kb_report_usbd;
//                            break;
//                        case kb_fn_ms:
//                            kb_ctl &= ~KB_CTL_HOST;
//                            break;
//                        case kb_fn_usb:
//                            kb_ctl &= ~KB_CTL_USBD;
//                            break;
//                        default:
//                            break;
//                    }
//                    break;
//
//                case KEY_2_AT:
//                case KEY_7_AMPERSAND:
//                    switch (kb_fn) {
//                        case kb_fn_lyr:
//                            keyboard_layer_select(1);
//                            break;
//                        case kb_fn_ctl:
//                        case kb_fn_led:
////                            leds_on();
//                            break;
//                        case kb_fn_uart:
//                            kb_ctl |= KB_CTL_USART;
//                            kb_rep_send = kb_report_usbhd;
//                            break;
//                        case kb_fn_ms:
//                            kb_ctl |= KB_CTL_HOST;
//                            break;
//                        case kb_fn_usb:
//                            kb_ctl |= KB_CTL_USBD;
//                            break;
//                        default:
//                            break;
//                    }
//                    break;
//
//                case KEY_3_NUMBER_SIGN:
//                case KEY_8_ASTERISK:
//                    switch (kb_fn) {
//                        case kb_fn_lyr:
//                            keyboard_layer_select(2);
//                            break;
//                        case kb_fn_led:
////                            leds_on();
//                            break;
//                        default:
//                            break;
//                    }
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
}

void keyboard_row_read() {
    kb_row_read = (uint8_t) (GPIO_ReadInputData(GPIOA) & 0x3F);
//    if (kb_row_read != 0) {
//        printf("c%d:%d\n", kb_col_curr, kb_row_read);
//    }
}

//uint16_t tmp1;
void keyboard_trigger_handler(){
//    static bool signal = 0;
//    signal = (bool) GPIO_ReadInputDataBit(GPIOA, KB_ROW_GPIO_PIN[kb_row_curr]);
//    bool signal = (bool) ((kb_row_read >> kb_row_curr) & 0x1);
    bool signal = (bool) ((kb_row_read >> (KB_ROW_NUM - 1 - kb_row_curr)) & 0x1);
    if (kb_key_state[kb_row_curr][kb_col_curr] != signal) {
        kb_key_state[kb_row_curr][kb_col_curr] = signal;
        kb_flag |= KB_FLAG_COUNT;

        if (kb_layout[kb_row_curr][kb_col_curr] == KEY_FN) {
            kb_flag &= ~KB_FLAG_COUNT;
            if (signal == KB_PRESS) {
                kb_flag |= KB_FLAG_FN;
//                printf("+KEY_FN\n");
//                kb_ctl &= ~KB_CTL_USBD;
//                keyboard_layer_select(1);
            } else {
                kb_flag &= ~KB_FLAG_FN;
//                printf("-KEY_FN\n");
//                kb_ctl |= KB_CTL_USBD;
//                keyboard_layer_select(0);
            }
        } else {
            if (kb_flag & KB_FLAG_FN) {
                if (signal == KB_PRESS) {
                    keyboard_fn_handler();
                }
//                kb_flag &= ~KB_FLAG_COUNT;
            }
        }

        switch (kb_device) {
            default:
            case KB_DEVICE_KEYBORAD: {
                uint8_t kb_buf_tmp, kb_buf_num;
//                kb_buf_num = kb_layout[kb_row_curr][kb_col_curr] / 8;
//                kb_buf_tmp = 1U << (kb_layout[kb_row_curr][kb_col_curr] % 8);
                kb_buf_num = kb_layout[kb_row_curr][kb_col_curr] >> 3;
                kb_buf_tmp = 1U << (kb_layout[kb_row_curr][kb_col_curr] & 7);
                if (signal == KB_PRESS) {
                    ++kb_key_count;
                    kb_report_usbd[kb_buf_num] |= kb_buf_tmp;
                } else {
                    --kb_key_count;
                    kb_report_usbd[kb_buf_num] &= ~kb_buf_tmp;
                }
                break;
            }

            case KB_DEVICE_CNTLR: {
//                if (kb_ctl & KB_CTL_CNTLR) {
//                }
                uint16_t kb_cntlr_buf_num, kb_cntlr_buf_tmp;
                switch (kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr]) {
                    default:
                        kb_cntlr_buf_num = kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr] / 16;
                        kb_cntlr_buf_tmp = 1U << kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr] % 16;
                        break;

                    case CNTLR_NONE:
                        break;


//                    #define CNTLR_LEFT_STICK1 0
//                    #define CNTLR_LEFT_STICK2 1
//                    case CNTLR_LEFT_STICK_LEFT: {
////                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON;
////                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        uint16_t tmp = CNTLR_AXIS_HALF * kb_row_adc[kb_row_curr] / 4095;
//                        cntlr_report.axis[CNTLR_LEFT_STICK1] = CNTLR_AXIS_HALF - tmp;
//                        break;
//                    }
//                    case CNTLR_LEFT_STICK_RIGHT: {
////                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON;
////                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        uint16_t tmp = CNTLR_AXIS_HALF * kb_row_adc[kb_row_curr] / 4095;
//                        cntlr_report.axis[CNTLR_LEFT_STICK1] = CNTLR_AXIS_HALF + tmp;
//                        break;
//                    }
//
//                    case CNTLR_LEFT_STICK_UP:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 1;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        break;
//                    case CNTLR_LEFT_STICK_DOWN:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 1;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        break;
//
//                    case CNTLR_RIGHT_STICK_LEFT:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 2;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        break;
//                    case CNTLR_RIGHT_STICK_RIGHT:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 2;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        break;
//
//                    case CNTLR_RIGHT_STICK_UP:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 3;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        break;
//                    case CNTLR_RIGHT_STICK_DOWN:
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 3;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        break;
                }

                if (signal == KB_PRESS) {
                    if (kb_cntlr_buf_num < USBD_REPORT_SIZE_CNTLR_BUTTON) {
                        cntlr_report.button[kb_cntlr_buf_num] |= kb_cntlr_buf_tmp;
                    } else {
//                        cntlr_report[kb_cntlr_buf_num] = kb_cntlr_buf_tmp;
                    }
                } else {
                    if (kb_cntlr_buf_num < USBD_REPORT_SIZE_CNTLR_BUTTON) {
                        cntlr_report.button[kb_cntlr_buf_num] &= ~kb_cntlr_buf_tmp;
                    } else {
//                        cntlr_report[kb_cntlr_buf_num] = 0;
                    }
                }
//                printf("buf_cntrl: %d\n", cntlr_report[kb_cntlr_buf_num]);
//                printf("KB_FLAG_COUNT: %lu\n", kb_flag);
                break;
            }

            case KB_DEVICE_MOUSE: {
                for (int i = 0; i < 3; ++i) {
                    mouse_report.axis[i] = MOUSE_AXIS_HALF;
                }
                uint16_t mouse_report_num, mouse_report_tmp;
                switch (mouse_lyrs[0][kb_row_curr][kb_col_curr]) {
                    default:
                        mouse_report_num = mouse_lyrs[0][kb_row_curr][kb_col_curr] / 16;
                        mouse_report_tmp = 1U << mouse_lyrs[0][kb_row_curr][kb_col_curr] % 16;

                        if (signal == KB_PRESS) {
                            if (mouse_report_num < USBD_REPORT_SIZE_MOUSE_BUTTON) {
                                mouse_report.button[mouse_report_num] |= mouse_report_tmp;
                            } else {
                                //                        mouse_report[mouse_report_num] = mouse_report_tmp;
                            }
                        } else {
                            if (mouse_report_num < USBD_REPORT_SIZE_MOUSE_BUTTON) {
                                mouse_report.button[mouse_report_num] &= ~mouse_report_tmp;
                            } else {
                                //                        mouse_report[mouse_report_num] = 0;
                            }
                        }
                        break;
                        
                    case MOUSE_NONE:
                        break;

                    case MOUSE_X_NEG:
//                        mouse_report_num = 1;
//                        mouse_report_tmp = CNTLR_AXIS_MIN;
                        mouse_report.axis[0] = MOUSE_AXIS_TEST_MIN;
                        break;
                    case MOUSE_X_POS:
//                        mouse_report_num = 1;
//                        mouse_report_tmp = CNTLR_AXIS_MAX;
                        mouse_report.axis[0] = MOUSE_AXIS_TEST_MAX;
                        break;

                    case MOUSE_Y_POS:
//                        mouse_report_num = 2;
//                        mouse_report_tmp = CNTLR_AXIS_MIN;
                        mouse_report.axis[1] = MOUSE_AXIS_TEST_MIN;
                        break;
                    case MOUSE_Y_NEG:
//                        mouse_report_num = 2;
//                        mouse_report_tmp = CNTLR_AXIS_MAX;
                        mouse_report.axis[1] = MOUSE_AXIS_TEST_MAX;
                        break;

                    case MOUSE_WHEEL_NEG:
//                        mouse_report_num = 3;
//                        mouse_report_tmp = CNTLR_AXIS_MIN;
                        mouse_report.axis[2] = MOUSE_AXIS_TEST_MIN;
                        break;
                    case MOUSE_WHEEL_POS:
//                        mouse_report_num = 3;
//                        mouse_report_tmp = CNTLR_AXIS_MAX;
                        mouse_report.axis[2] = MOUSE_AXIS_TEST_MAX;
                        break;
                }

//                if (signal == KB_PRESS) {
//                    if (mouse_report_num < USBD_REPORT_SIZE_MOUSE_BUTTON) {
//                        mouse_report.button[mouse_report_num] |= mouse_report_tmp;
//                    } else {
////                        mouse_report[mouse_report_num] = mouse_report_tmp;
//                    }
//                } else {
//                    if (mouse_report_num < USBD_REPORT_SIZE_MOUSE_BUTTON) {
//                        mouse_report.button[mouse_report_num] &= ~mouse_report_tmp;
//                    } else {
////                        mouse_report[mouse_report_num] = 0;
//                    }
//                }
//                printf("mouse_report: %d\n", mouse_report[mouse_report_num]);
//                printf("KB_FLAG_COUNT: %lu\n", kb_flag);
                break;
            }
        }
    }

    switch (kb_device) {
        default:
            break;

        case KB_DEVICE_CNTLR_ADC: {
//            for (int i = 0; i < KB_ROW_NUM; ++i) {
//                uint16_t tmp = CNTLR_AXIS_HALF * kb_row_adc[i] / 4095;
//                cntlr_report.axis[0] = tmp;
//            }
//            break;
//            case KB_DEVICE_CNTLR_ADC: {
                //                if (kb_ctl & KB_CTL_CNTLR) {
                //                }
//                uint16_t kb_cntlr_buf_num, kb_cntlr_buf_tmp;
                switch (kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr]) {
                    default:
//                        kb_cntlr_buf_num = kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr] / 16;
//                        kb_cntlr_buf_tmp = 1U << kb_cntlr_lyrs[0][kb_row_curr][kb_col_curr] % 16;
                        break;

//                    case CNTLR_NONE:
//                        break;

#define CNTLR_LEFT_STICK1 0
#define CNTLR_LEFT_STICK2 1
//                    case CNTLR_LEFT_STICK_LEFT: {
//                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON;
//                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        tmp1 = kb_row_adc[kb_row_curr];
//                        cntlr_report.axis[CNTLR_LEFT_STICK1] = CNTLR_AXIS_HALF * (1 + kb_row_adc[kb_row_curr] / 4095);
////                        kb_flag |= KB_FLAG_COUNT;
//                        break;
//                    }
//                    case CNTLR_LEFT_STICK_RIGHT: {
//                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON;
//                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        uint16_t tmp = kb_row_adc[kb_row_curr];
//                        cntlr_report.axis[CNTLR_LEFT_STICK1] = CNTLR_AXIS_HALF * (1 + (tmp - tmp1) / 4095);
////                        kb_flag |= KB_FLAG_COUNT;
//                        break;
//                    }

                    case CNTLR_LEFT_STICK_UP:{
                        uint16_t tmp = CNTLR_AXIS_HALF * kb_row_adc[kb_row_curr] / 4095;
                        cntlr_report.axis[CNTLR_LEFT_STICK2] = CNTLR_AXIS_HALF - tmp;
//                        kb_flag |= KB_FLAG_COUNT;
                        break;
                    }
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 1;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
//                        break;
//                    case CNTLR_LEFT_STICK_DOWN:{
//                        uint16_t tmp = CNTLR_AXIS_HALF * kb_row_adc[kb_row_curr] / 4095;
//                        cntlr_report.axis[CNTLR_LEFT_STICK2] = CNTLR_AXIS_HALF + tmp;
////                        kb_flag |= KB_FLAG_COUNT;
//                        break;
//                    }
//                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 1;
//                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
//                        break;
                        //
                        //                    case CNTLR_RIGHT_STICK_LEFT:
                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 2;
                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
                        //                        break;
                        //                    case CNTLR_RIGHT_STICK_RIGHT:
                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 2;
                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
                        //                        break;
                        //
                        //                    case CNTLR_RIGHT_STICK_UP:
                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 3;
                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MIN;
                        //                        break;
                        //                    case CNTLR_RIGHT_STICK_DOWN:
                        //                        kb_cntlr_buf_num = USBD_REPORT_SIZE_CNTLR_BUTTON + 3;
                        //                        kb_cntlr_buf_tmp = CNTLR_AXIS_MAX;
                        //                        break;
                }
//                kb_flag |= KB_FLAG_COUNT;
        }

        case KB_DEVICE_CNTLR: {
            static uint16_t js_adc_state[JS_NUM];
            static const uint16_t press_step = 8, release_step = 8;
            static uint16_t js_adc_mid[JS_NUM];
            static uint16_t js_adc_min_limit[JS_NUM] = {0, 0}, js_adc_max_limit[JS_NUM] = {4095, 4095};
            static uint16_t js_adc_min[JS_NUM] = {512, 512}, js_adc_max[JS_NUM] = {3584, 3584};

            //    kb_row_read = 0;
            static bool init;
            uint16_t js_adc_current[JS_NUM];
            for (int i = 0; i < JS_NUM; ++i) {
                js_adc_current[i] = js_axis_adc[i];
            }
             
            for (int i = 0; i < JS_NUM; ++i) {
                if (js_adc_state[i] == 0 && js_adc_current[i] != 0 && init == 0) {
                    js_adc_state[i] = js_adc_current[i];
                    js_adc_mid[i] = js_adc_state[i];
                    if (i == 1) {
                        init = 1;
                    }
                } else if (js_adc_current[i] < js_adc_min_limit[i]) {
                    //                    js_adc_state[i] = js_adc_min_limit[i];
                    uint16_t tmp = CNTLR_AXIS_HALF * (js_adc_mid[i] - js_adc_min_limit[i]) / (js_adc_mid[i] - js_adc_min[i]);
                    if (i == 0) {
                        cntlr_report.axis[i] = CNTLR_AXIS_HALF - tmp;
                    } else {
                        cntlr_report.axis[i] = CNTLR_AXIS_HALF + tmp;
                    }
                    kb_flag |= KB_FLAG_COUNT;
                } else if (js_adc_current[i] < js_adc_mid[i] && js_adc_current[i] > js_adc_min_limit[i]) {
                    if (js_adc_current[i] > (js_adc_state[i] + press_step) || js_adc_current[i] < (js_adc_state[i] - release_step)) {
                        js_adc_state[i] = js_adc_current[i];
                        if (js_adc_min[i] - release_step > js_adc_state[i] && js_adc_state[i] > js_adc_min_limit[i]) {
                            js_adc_min[i] = js_adc_state[i];
                            //                            printf("min%d:%d\n", i, js_adc_min[i]);
                        }
                        uint16_t tmp = CNTLR_AXIS_HALF * (js_adc_mid[i] - js_adc_state[i]) / (js_adc_mid[i] - js_adc_min[i]);
                        if (i == 0) {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF - tmp;
                        } else {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF + tmp;
                        }
                        kb_flag |= KB_FLAG_COUNT;
                        //                        printf("a%d:%d\n", i, js_adc_state[i]);
                        //                        printf("a%d:%d\n", i, cntlr_report[2 + i]);
                    }
                } else if (js_adc_current[i] > js_adc_mid[i] && js_adc_current[i] < js_adc_max_limit[i]) {
                    if (js_adc_current[i] > (js_adc_state[i] + press_step) || js_adc_current[i] < (js_adc_state[i] - release_step)) {
                        js_adc_state[i] = js_adc_current[i];
                        if (js_adc_max[i] + press_step < js_adc_state[i] && js_adc_state[i] < js_adc_max_limit[i]) {
                            js_adc_max[i] = js_adc_state[i];
//                            printf("max%d:%d\n", i, js_adc_max[i]);
                        }
                        uint16_t tmp = CNTLR_AXIS_HALF * (js_adc_state[i] - js_adc_mid[i]) / (js_adc_max[i] - js_adc_mid[i]);
                        if (i == 0) {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF + tmp;
                        } else {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF - tmp;
                        }
                        kb_flag |= KB_FLAG_COUNT;
//                        printf("a%d:%d\n", i, js_adc_state[i]);
//                        printf("a%d:%d\n", i, cntlr_report[2 + i]);
                    }
                } else if (js_adc_current[i] > js_adc_max_limit[i]) {
//                        js_adc_state[i] = js_adc_max_limit[i];
                        uint16_t tmp = CNTLR_AXIS_HALF * (js_adc_max_limit[i] - js_adc_mid[i]) / (js_adc_max[i] - js_adc_mid[i]);
                        if (i == 0) {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF + tmp;
                        } else {
                            cntlr_report.axis[i] = CNTLR_AXIS_HALF - tmp;
                        }
                        kb_flag |= KB_FLAG_COUNT;
                }
            }
        }
    }

}

void kb_polling() {
    switch (kb_device) {
        default:
        case KB_DEVICE_KEYBORAD:
            keyboard_row_read();
            break;

        case KB_DEVICE_KEYBOARD_ADC_DIFF:
            keyboard_row_read_adc_diff();
            break;

        case KB_DEVICE_KEYBOARD_ADC_TRIGGER:
        case KB_DEVICE_CNTLR_ADC:
            keyboard_row_read_adc_trigger();
            break;

//        case KB_DEVICE_CNTLR_ADC:
//            kb_row_adc_cntlr();
//            break;
    }
}

void keyboard_row_handler() {
    for (kb_row_curr = 0; kb_row_curr < KB_ROW_NUM; ++kb_row_curr) {
        keyboard_trigger_handler();
    }
}

void keyboard_usb_send() {
    if (kb_ctl & KB_CTL_USBD) {
        switch (kb_device) {
            default:
            case KB_DEVICE_KEYBORAD:
                switch (kb_repeat) {
                    default:
                    case KB_REPEAT_NONE:
                        if ((kb_flag & KB_FLAG_COUNT) && (usbd_kb_check_send() == USB_SUCCESS)) {
                            kb_flag &= ~KB_FLAG_COUNT;
                            usbd_kb_report_send(kb_rep_send);
                        }
                        break;

                    case KB_REPEAT_FAST:
                        if (kb_key_count != 0) {
                            if (!(kb_flag & KB_FLAG_REPEAT) && (usbd_kb_check_send() == USB_SUCCESS)) {
                                kb_flag |= KB_FLAG_REPEAT;
                                usbd_kb_report_send(kb_rep_send);
                            } else {
                                kb_flag &= ~KB_FLAG_REPEAT;
                                usbd_kb_report_send(kb_report_empty);
                            }
                        } else {
                            if ((kb_flag & KB_FLAG_COUNT) && (usbd_kb_check_send() == USB_SUCCESS)) {
                                if (!(kb_flag & KB_FLAG_REPEAT)) {
                                } else {
                                    kb_flag &= ~KB_FLAG_REPEAT;
                                }
                                kb_flag &= ~KB_FLAG_COUNT;
                                usbd_kb_report_send(kb_rep_send);
                            }
                        }
                        break;

                    case KB_REPEAT_SLOW: {
                        static uint16_t kb_repeat_delay = 0, kb_repeat_rate = 0;
                        static bool kb_repeat_first = 0;
                        if (kb_key_count != 0) {
                            if ((kb_repeat_delay == KB_REPEAT_SLOW_DELAY && kb_repeat_rate == KB_REPEAT_SLOW_RATE) || (kb_repeat_first == 0)) {
                                if (!(kb_flag & KB_FLAG_REPEAT) && (usbd_kb_check_send() == USB_SUCCESS)) {
                                    kb_flag |= KB_FLAG_REPEAT;
                                    usbd_kb_report_send(kb_rep_send);
    //                                kb_repeat_delay = 0;
                                    kb_repeat_rate = 0;
                                    kb_repeat_first = 1;
                                } else {
    //                                if (kb_repeat_rate == KB_REPEAT_SLOW_RATE) {
                                    kb_flag &= ~KB_FLAG_REPEAT;
                                    usbd_kb_report_send(kb_report_empty);
    //                                    kb_repeat_rate = 0;
    //                                }
                                }
                            } else {
                                if (kb_repeat_delay != KB_REPEAT_SLOW_DELAY) {
                                    ++kb_repeat_delay;
//                                    kb_repeat_rate = KB_REPEAT_SLOW_RATE;
                                } else {
                                    if (kb_repeat_rate != KB_REPEAT_SLOW_RATE)
                                        ++kb_repeat_rate;
                                }
                            }
                        } else {
                            if ((kb_flag & KB_FLAG_COUNT) && (usbd_kb_check_send() == USB_SUCCESS)) {
                                kb_flag &= ~KB_FLAG_REPEAT;
                                kb_flag &= ~KB_FLAG_COUNT;
                                usbd_kb_report_send(kb_rep_send);
                                kb_repeat_first = 0;
                                kb_repeat_delay = 0;
                                kb_repeat_rate = 0;
                            }
                        }
                        break;
                    }
                }
                break;

            case KB_DEVICE_CNTLR:
            case KB_DEVICE_CNTLR_ADC:
                if ((kb_flag & KB_FLAG_COUNT) && (usbd_cntlr_check_send() == USB_SUCCESS)) {
                    kb_flag &= ~KB_FLAG_COUNT;
                    usbd_cntlr_report_send((uint8_t *) &cntlr_report);

//                    printf("send: ");
//                    for (uint8_t i = 0; i < USBD_REPORT_SIZE_CNTLR; ++i) {
//                        printf("%02x ", cntlr_report[i]);
//                    }
//                    printf("\n");
                };
                break;

            case KB_DEVICE_MOUSE:
                if ((kb_flag & KB_FLAG_COUNT) && (usbd_mouse_check_send() == USB_SUCCESS)) {
                    kb_flag &= ~KB_FLAG_COUNT;
                    usbd_mouse_report_send((uint8_t *) &mouse_report);

//                    printf("send: ");
//                    for (uint8_t i = 0; i < USBD_REPORT_SIZE_MOUSE; ++i) {
//                        printf("%02x ", mouse_report[i]);
//                    }
//                    printf("\n");
                };
                break;
        }

//        if (kb_ctl & KB_CTL_CNTLR) {
//            hid_cntlr_report_send(cntlr_report, USBD_REPORT_SIZE_CNTLR);
//        }

//        if (kb_ctl & KB_CTL_MOUSE) {
//            hid_mouse_report_send(mouse_report, USBD_MICE_BUF_SIZE);
//        }
    }
}

void kb_usb_receive() {
    usbd_kb_report_receive();
    if (usbd_kb_check_recev() == USB_SUCCESS) {
/*        switch (kb_rep_recv[0]){
            case LED_NONE:
//            leds_off();
//            led_color_set(pwm, 0x00U, led_sys[0][r]);
//            led_color_set(pwm, 0x20U, led_sys[0][g]);
//            LED_FLAG |= LED_FLAG_CHANGE;
//            leds_dma();
                break;

            case 1U << LED_CAPS_LOCK:
//            leds_on();
//            led_color_set(pwm, 0x20U, led_sys[0][r]);
//            led_color_set(pwm, 0x00U, led_sys[0][g]);
                LED_FLAG |= LED_FLAG_CHANGE;
//            leds_dma();
                break;

            case 1U << LED_SHIFT:
//            led_color_set(pwm, 0x20U, led_sys[0][b]);
//            led_color_set(pwm, 0x00U, led_sys[0][g]);
                LED_FLAG |= LED_FLAG_CHANGE;
//            leds_dma();
                break;

            default:
                break;
        }

        switch (kb_rep_recv[1]) {
            case LED_OFF:
//            kb_ctl &= ~KB_CTL_LED;
//            led_effect = 0;
                led_effect = LED_NO;
                leds_off();
                break;

            case LED_ON:
//            kb_ctl |= KB_CTL_LED;
                leds_on();
                break;

            case LED_SPECTRUM:
//            leds_spectrum();
                led_effect = LED_SPECTRUM;
                break;

            case LED_NO:
                led_effect = LED_NO;
                break;

            default:
                break;
        }*/

        switch (kb_rep_recv[1]) {
            case KB_CTL_LYR_0:
                keyboard_layer_select(0);
                break;

            case KB_CTL_LYR_1:
                keyboard_layer_select(1);
                break;

            case KB_CTL_LYR_2:
                keyboard_layer_select(2);
                break;

            case KB_CTL_LYR_3:
                keyboard_layer_select(3);
                break;

            case KB_CTL_KB_OFF:
//                kb_ctl &= ~KB_CTL_KEYBOARD;
                break;

            case KB_CTL_KB_ON:
//                kb_ctl |= KB_CTL_KEYBOARD;
                break;

            case KB_CTL_REPEAT_OFF:
//                kb_ctl &= ~KB_CTL_REPEAT;
//            kb_repeat_flag = 0;
//            kb_flag &= KB_FLAG_REPEAT;
                break;

            case KB_CTL_REPEAT_ON:
//                kb_ctl |= KB_CTL_REPEAT;
//            kb_repeat_flag = 0;
//            kb_flag |= KB_FLAG_REPEAT;
                break;

            default:
                //keyboard_layer_select(hid->data_out[2]);
                break;
        }
    }
}

void kb_usbhd_combine() {
    if ((kb_flag & KB_FLAG_COUNT) && (kb_ctl & KB_CTL_HOST)) {
//        printf("usbhd: ");
        for (uint8_t i = 0; i < USBD_REPORT_4BYTE_KB; ++i) {
            kb_report_usbhd[i] = kb_report_usbd[i] | kb_report_usbh[i];
//            printf("%02x ", kb_rep_send[i]);
        }
//        printf("\n");
    }
}

void keyboard_row_read_adc_diff() {
    static uint16_t kb_sw_adc[KB_ROW_NUM][KB_COL_NUM];
    // 256 unstable < 5 keys
    // 128 most unstable
    static const uint16_t press_step = 512, release_step = 512;
    kb_row_read = 0;

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);

    for (int i = 0; i < KB_ROW_NUM; ++i) {
        if (kb_sw_adc[i][kb_col_curr] == 0) {
            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
        } else if (kb_row_adc[i] > (kb_sw_adc[i][kb_col_curr] + press_step)) {
            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
            kb_row_read |= 0x1 << i;
        } else if (kb_row_adc[i] < (kb_sw_adc[i][kb_col_curr] - release_step)) {
            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
            kb_row_read &= ~(0x1 << i);
        } else {
            if (kb_key_state[(KB_ROW_NUM - 1 - i)][kb_col_curr] != 0) {
                kb_row_read |= 0x1 << i;
            } else {
                kb_row_read &= ~(0x1 << i);
            }
        }
    }
//    printf("r[][%d]:%d\n", kb_col_curr, kb_row_read);
}

void keyboard_row_read_adc_trigger() {
    const static uint16_t max = 4096 * 0.7;
    const static uint16_t min = 4096 * 0.3;
    kb_row_read = 0;

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);

    for (int i = 0; i < KB_ROW_NUM; ++i) {
        if (kb_row_adc[i] > max) {
            kb_row_read |= 0x1 << i;
        } else if (kb_row_adc[i] < min) {
            kb_row_read &= ~(0x1 << i);
        }
    }
}

//void kb_row_adc_cntlr() {
//    static uint16_t kb_sw_adc[KB_ROW_NUM][KB_COL_NUM];
//    static const uint16_t press_step = 64, release_step = 256;
//
//    kb_row_read = 0;
//    for (int i = 0; i < KB_ROW_NUM; ++i) {
//        if (kb_sw_adc[i][kb_col_curr] == 0) {
//            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
//        } else if (kb_row_adc[i] > (kb_sw_adc[i][kb_col_curr] + press_step)) {
//            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
//            kb_row_read |= 0x1 << i;
//        } else if (kb_row_adc[i] < (kb_sw_adc[i][kb_col_curr] - release_step)) {
//            kb_sw_adc[i][kb_col_curr] = kb_row_adc[i];
//            kb_row_read &= ~(0x1 << i);
//        } else {
//            if (kb_key_state[i][kb_col_curr] != 0) {
//                kb_row_read |= 0x1 << i;
//            } else {
//                kb_row_read &= ~(0x1 << i);
//            }
//        }
//    }
//    //    printf("r[][%d]:%d\n", kb_col_curr, kb_row_read);
//}
