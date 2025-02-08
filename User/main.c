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
#include "4_Links_All_Previous_Tasks/4_Links_All_Previous_Tasks.h"

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
    SystemCoreClockUpdate();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    Delay_Init();

    USART_Initial();
    Blink_Init();

    while(1)
    {
        Button_Control();  // §°§Ò§â§Ñ§Ò§Ñ§ä§í§Ó§Ñ§Ö§Þ §ß§Ñ§Ø§Ñ§ä§Ú§ñ §Ü§ß§à§á§à§Ü
        if (blink_active) {
            Blinking();  // §©§Ñ§á§å§ã§Ü§Ñ§Ö§Þ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§î §â§Ñ§Ù §Ó 100 §Þ§Ú§Ý§Ý§Ú§ã§Ö§Ü§å§ß§Õ
            Delay_Ms(100);
        }
    }
}
