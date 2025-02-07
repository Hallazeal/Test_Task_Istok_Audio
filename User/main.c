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
#include "1_Buttons/1_Buttons.h"

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

    UART_Init();           // ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� UART
    GPIO_Initial();           // ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� GPIO (�ܧߧ��ܧ�)
    Button_Init();         // ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� �ܧߧ����

    while(1)
    {
        Button_Process();  // ���ҧ�ѧҧ��ܧ� �������ߧڧ� �ܧߧ����
    }
}
