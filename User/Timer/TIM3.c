/*
 * TIM3.c
 *
 *  Created on: Feb 11, 2025
 *      Author: Nikita Danilov
 */
#include "ch32v10x.h"

void TIM3_CH2_PWM_Initial(void){
// TIM3 for PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 89;  // PWM frequency 800 kHz (72MHz / 90)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // PWM (TIM3_CH2)
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    TIM_DMACmd(TIM3, TIM_DMA_CC2, ENABLE);

    TIM_Cmd(TIM3, ENABLE);
}
