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

//    PWM_TIM4_CH3_DMA_Init();

//    TIM2_IRQHandler();
//    TIM2_Init();

//    USART_Printf_Init(115200);

//    printf("SystemClk:%d\r\n", SystemCoreClock);
//    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
//    printf("This is printf example\r\n");

//    Button_Init();

    LED_Init(); // 2 method
//    SK6812_Init(); // 1 method

//    Flash_Init();
//    TIM3_Init();

    while(1)
    {
//        Button_Task();

        LED_SetAll(WHITE);// §¢§Ö§Ý§í§Û
        Delay_Ms(2000);
        LED_SetAll(RED);// §¬§â§Ñ§ã§ß§í§Û
        Delay_Ms(2000);
        LED_SetAll(BLACK);// §£§í§Ü§Ý§ð§é§Ö§ß§Ú§Ö
        Delay_Ms(2000);

//        SK6812_SetAll(Colors[1]);// §¢§Ö§Ý§í§Û
//        SK6812_Show();
//        Delay_Ms(1000);
//
//        SK6812_SetAll(Colors[2]);// §¬§â§Ñ§ã§ß§í§Û
//        SK6812_Show();
//        Delay_Ms(1000);
//
//        SK6812_SetAll(Colors[0]);// §£§í§Ü§Ý§ð§é§Ö§ß§Ú§Ö
//        SK6812_Show();
//        Delay_Ms(1000);

//        for(uint8_t i=0; i<SK6812_NUM_LEDS; i++)//§á§Ö§â§Ö§Ò§à§â §Õ§Ý§ñ §Ü§Ñ§Ø§Õ§à§Ô§à §Ú§Ù 2 §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ§à§Ó
//        {
//            SK6812_set(i, 20, 20, 20);
//        }
//        SK6812_send();
//        Flash_Sequence();// §©§Ñ§á§å§ã§Ü§Ñ§Ö§Þ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§î
//        Delay_Ms(5000);// §±§à§Ó§ä§à§â§ñ§Ö§Þ §â§Ñ§Ù §Ó 2 §ã§Ö§Ü§å§ß§Õ§í
    }
}
