/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

// §¢§å§æ§Ö§â §Õ§Ý§ñ §á§Ö§â§Ö§Õ§Ñ§é§Ú §Õ§Ñ§ß§ß§í§ç §á§à DMA
uint16_t pwm_buffer[BIT_COUNT + RESET_PULSE] = { 0 };

const Color_t BLACK = { 0, 0, 0 }, WHITE = { 20, 20, 20 }, RED = { 20, 0, 0 },
        GREEN = { 0, 20, 0 }, BLUE = { 0, 0, 20 }, YELLOW = { 20, 20, 0 },
        PURPLE = { 20, 0, 20 }, CYAN = { 0, 20, 20 }, ORANGE = { 20, 10, 0 };

// === §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ GPIO, PWM §Ú DMA ===
void LED_Init(void) {
    // §£§Ü§Ý§ð§é§Ñ§Ö§Þ §ä§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö GPIOC, TIM3 §Ú DMA1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    AFIO->PCFR1 |= AFIO_PCFR1_TIM3_REMAP_FULLREMAP; // §±§à§Ý§ß§í§Û §â§Ö§Þ§Ñ§á TIM3: CH2 ¡ú PC7

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ PC7 (TIM3_CH2) §Ó §â§Ö§Ø§Ú§Þ §Ñ§Ý§î§ä§Ö§â§ß§Ñ§ä§Ú§Ó§ß§à§Û §æ§å§ß§Ü§è§Ú§Ú Push-Pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_FullRemap_TIM3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ DMA
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CH2CVR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) pwm_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = BIT_COUNT + RESET_PULSE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);

    // §±§à§Õ§Ü§Ý§ð§é§Ñ§Ö§Þ DMA §Ü TIM3_CH2
    TIM_DMACmd(TIM3, TIM_DMA_CC2, ENABLE);

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ §ä§Ñ§Û§Þ§Ö§â§Ñ TIM3 §Õ§Ý§ñ PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 89;  // §¹§Ñ§ã§ä§à§ä§Ñ §º§ª§® 800 §Ü§¤§è (72MHz / 90)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ §Ü§Ñ§ß§Ñ§Ý§Ñ PWM (TIM3_CH2)
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    DMA_Cmd(DMA1_Channel3, ENABLE);  // §£§Ü§Ý§ð§é§Ñ§Ö§Þ DMA
    TIM_Cmd(TIM3, ENABLE);           // §£§Ü§Ý§ð§é§Ñ§Ö§Þ §ä§Ñ§Û§Þ§Ö§â
}

// === §¬§à§Õ§Ú§â§à§Ó§Ñ§ß§Ú§Ö §è§Ó§Ö§ä§Ñ §Ó PWM-§Ò§å§æ§Ö§â ===
void LED_SetColor(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b) {
    uint16_t bit_index = led_index * 24;
    uint32_t color = (g << 16) | (r << 8) | b;

    for (int i = 0; i < 24; i++) {
        if (color & (1 << (23 - i))) {
            pwm_buffer[bit_index + i] = T1H;
        } else {
            pwm_buffer[bit_index + i] = T0H;
        }
    }
}

// === §°§ä§á§â§Ñ§Ó§Ü§Ñ §Õ§Ñ§ß§ß§í§ç §á§à DMA ===
void LED_Send(void) {
    for (int i = 0; i < RESET_PULSE; i++) {
        pwm_buffer[BIT_COUNT + i] = 0;  // §±§Ö§â§Ú§à§Õ §ã§Ò§â§à§ã§Ñ
    }

    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3, BIT_COUNT + RESET_PULSE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
}

// === §µ§ã§ä§Ñ§ß§à§Ó§Ü§Ñ §è§Ó§Ö§ä§Ñ §Õ§Ý§ñ §Ó§ã§Ö§ç §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ§à§Ó ===
void LED_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        LED_SetColor(i, color.r, color.g, color.b);
    }
    LED_Send();
}
