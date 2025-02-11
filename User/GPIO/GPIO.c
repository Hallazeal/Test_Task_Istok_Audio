/*
 * GPIO.c
 *
 *  Created on: Feb 10, 2025
 *      Author: Nikita Danilov
 */


#include "ch32v10x.h"
#include "GPIO.h"

void GPIO_Initial(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(PORT_B | PORT_C, ENABLE);

    // PB12, PB13
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN_1 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // PC4, PC5
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN_3 | BUTTON_PIN_4;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
