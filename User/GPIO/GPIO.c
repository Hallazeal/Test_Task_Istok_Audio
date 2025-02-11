/*
 * GPIO.c
 *
 *  Created on: Feb 11, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "GPIO.h"

void GPIO_Initial(void) {
    RCC_APB2PeriphClockCmd(PORT_C | PORT_B, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // PC5
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // PB12
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
