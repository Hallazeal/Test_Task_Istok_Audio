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

    LED_Init(); // 2 method

    while(1)
    {
        LED_SetAll(WHITE);// §¢§Ö§Ý§í§Û
        Delay_Ms(2000);
//        LED_SetAll(RED);// §¬§â§Ñ§ã§ß§í§Û
//        Delay_Ms(2000);
//        LED_SetAll(BLACK);// §£§í§Ü§Ý§ð§é§Ö§ß§Ú§Ö
//        Delay_Ms(2000);
    }
}
