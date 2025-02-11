/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH (Nikita Danilov)
 * Version            : V1.0.0
 * Date               : 2024/01/05
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *USART Print debugging routine:
 *USART1_Tx(PA9).
 *This example demonstrates using USART1(PA9) as a print debug port output.
 *
 */

#include "debug.h"
#include "2_LED/2_LED.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "Timer/TIM3.h"

/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    GPIO_Initial();
    DMA_Initial();
    TIM3_CH2_PWM_Initial();


    while(1)
    {
        LED_SetAll(WHITE);// White
        Delay_Ms(2000);
        LED_SetAll(RED);// Red
        Delay_Ms(2000);
        LED_SetAll(BLACK);// Off(Black)
        Delay_Ms(2000);
    }
}
