/*
 * 4_Links_All_Previous_Tasks.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "4_Links_All_Previous_Tasks.h"

volatile uint8_t blink_active = 0;  // §¶§Ý§Ñ§Ô §Ñ§Ü§ä§Ú§Ó§ß§à§ã§ä§Ú §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§Ú

// === §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ UART §Õ§Ý§ñ §Ý§à§Ô§Ú§â§à§Ó§Ñ§ß§Ú§ñ ===
void USART_Initial(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =
            USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void USART_SendString(const char *str) {
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

// === §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ GPIO §Õ§Ý§ñ §Ó§ã§á§í§ê§Ö§Ü §Ú §Ü§ß§à§á§à§Ü ===
void Blink_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE); // §´§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö §á§à§â§ä§Ñ C §Ú B

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // §£§í§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ (LOW)

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ PC5 §Ü§Ñ§Ü §Ó§ç§à§Õ §Õ§Ý§ñ §Ü§ß§à§á§Ü§Ú §Ó§í§Ü§Ý§ð§é§Ö§ß§Ú§ñ §Ó§ã§á§í§ê§Ü§Ú
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ PB12 §Ü§Ñ§Ü §Ó§ç§à§Õ §Õ§Ý§ñ §Ü§ß§à§á§Ü§Ú §Ó§Ü§Ý§ð§é§Ö§ß§Ú§ñ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§Ú §Ó§ã§á§í§ê§Ö§Ü
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// === §£§Ü§Ý§ð§é§Ö§ß§Ú§Ö §Ó§ã§á§í§ê§Ü§Ú ===
void Blink_On(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // HIGH - §Ó§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ
}

// === §£§í§Ü§Ý§ð§é§Ö§ß§Ú§Ö §Ó§ã§á§í§ê§Ü§Ú ===
void Blink_Off(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LOW - §Ó§í§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ
}

// === §©§Ñ§á§å§ã§Ü §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§Ú §Ó§ã§á§í§ê§Ö§Ü ===
void Blinking(void) {
    Blink_On();    // 150 §Þ§ã §£§¬§­
    Delay_Ms(150);
    Blink_Off();   // 150 §Þ§ã §£§½§¬§­
    Delay_Ms(150);
    Blink_On();    // 500 §Þ§ã §£§¬§­
    Delay_Ms(500);
    Blink_Off();   // §£§í§Ü§Ý§ð§é§Ú§ä§î §Õ§à §ã§Ý§Ö§Õ§å§ð§ë§Ö§Ô§à §Ù§Ñ§á§å§ã§Ü§Ñ
}

// === §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §ß§Ñ§Ø§Ñ§ä§Ú§ñ §Ü§ß§à§á§à§Ü ===
void Button_Control(void) {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0) {
        blink_active = 1;  // §¡§Ü§ä§Ú§Ó§Ú§â§å§Ö§Þ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§î
        USART_SendString("Blink started\r\n");
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0);
        // §°§Ø§Ú§Õ§Ñ§ß§Ú§Ö §à§ä§á§å§ã§Ü§Ñ§ß§Ú§ñ §Ü§ß§à§á§Ü§Ú
    }
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0) {
        blink_active = 0;  // §°§ä§Ü§Ý§ð§é§Ñ§Ö§Þ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§î
        Blink_Off();
        USART_SendString("Blink stopped\r\n");
        while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0);
        // §°§Ø§Ú§Õ§Ñ§ß§Ú§Ö §à§ä§á§å§ã§Ü§Ñ§ß§Ú§ñ §Ü§ß§à§á§Ü§Ú
    }
}
