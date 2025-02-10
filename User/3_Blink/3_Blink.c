/*
 * 3_Blink.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "3_Blink.h"

void Blink_Initial(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // Turn off the LED (LOW)
}

void Blink_On(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // HIGH - turn on the LED
}

void Blink_Off(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LOW - turn off the LED
}

void Blinking(void) {
    Blink_On();    // 150 ms ON
    Delay_Ms(150);
    Blink_Off();   // 150 ms OFF
    Delay_Ms(150);
    Blink_On();    // 500 ms ON
    Delay_Ms(500);
    Blink_Off();
}
