/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

// �����֧� �էݧ� ��֧�֧էѧ�� �էѧߧߧ�� ��� DMA
uint16_t pwm_buffer[BIT_COUNT + RESET_PULSE] = { 0 };

const Color_t BLACK = { 0, 0, 0 }, WHITE = { 20, 20, 20 }, RED = { 20, 0, 0 },
        GREEN = { 0, 20, 0 }, BLUE = { 0, 0, 20 }, YELLOW = { 20, 20, 0 },
        PURPLE = { 20, 0, 20 }, CYAN = { 0, 20, 20 }, ORANGE = { 20, 10, 0 };

// === ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� GPIO, PWM �� DMA ===
void LED_Init(void) {
    // ���ܧݧ��ѧ֧� ��ѧܧ�ڧ��ӧѧߧڧ� GPIOC, TIM3 �� DMA1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    AFIO->PCFR1 |= AFIO_PCFR1_TIM3_REMAP_FULLREMAP; // ����ݧߧ�� ��֧ާѧ� TIM3: CH2 �� PC7

    // ���ѧ����ۧܧ� PC7 (TIM3_CH2) �� ��֧اڧ� �ѧݧ��֧�ߧѧ�ڧӧߧ�� ���ߧܧ�ڧ� Push-Pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_FullRemap_TIM3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // ���ѧ����ۧܧ� DMA
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

    // ����էܧݧ��ѧ֧� DMA �� TIM3_CH2
    TIM_DMACmd(TIM3, TIM_DMA_CC2, ENABLE);

    // ���ѧ����ۧܧ� ��ѧۧާ֧�� TIM3 �էݧ� PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 89;  // ���ѧ����� ������ 800 �ܧ��� (72MHz / 90)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // ���ѧ����ۧܧ� �ܧѧߧѧݧ� PWM (TIM3_CH2)
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    DMA_Cmd(DMA1_Channel3, ENABLE);  // ���ܧݧ��ѧ֧� DMA
    TIM_Cmd(TIM3, ENABLE);           // ���ܧݧ��ѧ֧� ��ѧۧާ֧�
}

// === ����էڧ��ӧѧߧڧ� ��ӧ֧�� �� PWM-�ҧ��֧� ===
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

// === ������ѧӧܧ� �էѧߧߧ�� ��� DMA ===
void LED_Send(void) {
    for (int i = 0; i < RESET_PULSE; i++) {
        pwm_buffer[BIT_COUNT + i] = 0;  // ���֧�ڧ�� ��ҧ����
    }

    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3, BIT_COUNT + RESET_PULSE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
}

// === �����ѧߧ�ӧܧ� ��ӧ֧�� �էݧ� �ӧ�֧� ��ӧ֧��էڧ�է�� ===
void LED_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        LED_SetColor(i, color.r, color.g, color.b);
    }
    LED_Send();
}
