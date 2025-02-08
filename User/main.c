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
        Button_Control();  // ���ҧ�ѧҧѧ��ӧѧ֧� �ߧѧاѧ�ڧ� �ܧߧ����
        if (blink_active) {
            Blinking();  // ���ѧ���ܧѧ֧� ����ݧ֧է�ӧѧ�֧ݧ�ߧ���� ��ѧ� �� 100 �ާڧݧݧڧ�֧ܧ�ߧ�
            Delay_Ms(100);
        }
    }
}
