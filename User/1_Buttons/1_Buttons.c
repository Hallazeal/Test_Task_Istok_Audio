/*
 * 1_Buttons.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "1_Buttons.h"

static uint32_t buttonPressTime[BUTTON_COUNT] = { 0 };  // §£§â§Ö§Þ§ñ §ß§Ñ§Ø§Ñ§ä§Ú§ñ §Ü§ß§à§á§à§Ü
static uint8_t buttonState[BUTTON_COUNT] = { 0 }; // §³§à§ã§ä§à§ñ§ß§Ú§Ö §Ü§ß§à§á§à§Ü (0 - §ß§Ö §ß§Ñ§Ø§Ñ§ä§Ñ, 1 - §ß§Ñ§Ø§Ñ§ä§Ñ)

void GPIO_Initial(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // §£§Ü§Ý§ð§é§Ñ§Ö§Þ §ä§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö §Õ§Ý§ñ §á§à§â§ä§à§Ó B §Ú C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    // §¯§Ñ§ã§ä§â§à§Ú§Þ §á§à§â§ä§í §Õ§Ý§ñ §Ü§ß§à§á§à§Ü (PB12, PB13, PC4, PC5) §Ü§Ñ§Ü §Ó§ç§à§Õ§í
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // §£§Ü§Ý§ð§é§Ñ§Ö§Þ §á§à§Õ§ä§ñ§Ø§Ü§å §Ü §á§Ú§ä§Ñ§ß§Ú§ð
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void UART_Init(void) {
    USART_InitTypeDef USART_InitStructure;

    // §£§Ü§Ý§ð§é§Ñ§Ö§Þ §ä§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö §Õ§Ý§ñ UART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,
            ENABLE);

    // §¯§Ñ§ã§ä§â§à§Ú§Þ §á§à§â§ä§í §Õ§Ý§ñ UART (PA9 - TX, PA10 - RX)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // §¡§Ý§î§ä§Ö§â§ß§Ñ§ä§Ú§Ó§ß§Ñ§ñ §æ§å§ß§Ü§è§Ú§ñ
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // §£§ç§à§Õ §Ò§Ö§Ù §á§à§Õ§ä§ñ§Ø§Ü§Ú
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ UART
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =
    USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void UART_SendString(const char* str) {
    while (*str)
    {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

void Button_Init(void) {
    // §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §ã§à§ã§ä§à§ñ§ß§Ú§Û §Ü§ß§à§á§à§Ü
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttonPressTime[i] = 0;
        buttonState[i] = 0;
    }
}

void Button_Process(void) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        uint8_t currentButtonState = 0;

        // §¹§ä§Ö§ß§Ú§Ö §ã§à§ã§ä§à§ñ§ß§Ú§ñ §Ü§ß§à§á§à§Ü (0 - §ß§Ñ§Ø§Ñ§ä§Ñ, 1 - §ß§Ö §ß§Ñ§Ø§Ñ§ä§Ñ)
        if (i < 2)  // §¥§Ý§ñ §Ü§ß§à§á§à§Ü §ß§Ñ §á§à§â§ä§å B
                {
            currentButtonState = GPIO_ReadInputDataBit(GPIOB,
                    (i == 0) ? GPIO_Pin_12 : GPIO_Pin_13);
        } else  // §¥§Ý§ñ §Ü§ß§à§á§à§Ü §ß§Ñ §á§à§â§ä§å C
        {
            currentButtonState = GPIO_ReadInputDataBit(GPIOC,
                    (i == 2) ? GPIO_Pin_4 : GPIO_Pin_5);
        }

        // §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §ã§à§ã§ä§à§ñ§ß§Ú§ñ §Ü§ß§à§á§Ü§Ú
        if (currentButtonState == 0 && buttonState[i] == 0) // §¬§ß§à§á§Ü§Ñ §ä§à§Ý§î§Ü§à §é§ä§à §ß§Ñ§Ø§Ñ§ä§Ñ
                {
            buttonState[i] = 1;
            buttonPressTime[i] = 0;
            Button_LogEvent("Press", i, 0);
        } else if (currentButtonState == 0 && buttonState[i] == 1) // §¬§ß§à§á§Ü§Ñ §å§Õ§Ö§â§Ø§Ú§Ó§Ñ§Ö§ä§ã§ñ
                {
            buttonPressTime[i]++;
            if (buttonPressTime[i] % HOLD_THRESHOLD == 0) {
                Button_LogEvent("Hold", i, buttonPressTime[i] / 10);
            }
        } else if (currentButtonState == 1 && buttonState[i] == 1) // §¬§ß§à§á§Ü§Ñ §à§ä§á§å§ë§Ö§ß§Ñ
                {
            buttonState[i] = 0;
            Button_LogEvent("Release", i, 0);
        }
    }
}

void Button_LogEvent(const char* event, int button_id, int duration) {
    char message[50];

    if (duration > 0) {
        sprintf(message, "%s Button %d for %d ms\r\n", event, button_id + 1,
                duration);
    } else {
        sprintf(message, "%s Button %d\r\n", event, button_id + 1);
    }

    UART_SendString(message);
}
