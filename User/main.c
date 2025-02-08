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
//#include "1_Buttons/1_Buttons.h"
#include "2_LED/2_LED.h"
//#include "3_Strobe/3_Strobe.h"

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

    SK6812_Init();

    while(1)
    {
        SK6812_SetAll(Colors[1]); // ���֧ݧ��
        SK6812_Show();
        Delay_Ms(2000);

        SK6812_SetAll(Colors[2]);// ����ѧ�ߧ��
        SK6812_Show();
        Delay_Ms(2000);

        SK6812_SetAll(Colors[0]);// ����ܧݧ��֧ߧڧ�
        SK6812_Show();
        Delay_Ms(2000);
    }
}
