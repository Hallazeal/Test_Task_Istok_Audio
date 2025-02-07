/*
 * 1_Buttons.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "1_Buttons.h"

static uint32_t buttonPressTime[BUTTON_COUNT] = { 0 };  // ����֧ާ� �ߧѧاѧ�ڧ� �ܧߧ����
static uint8_t buttonState[BUTTON_COUNT] = { 0 }; // ��������ߧڧ� �ܧߧ���� (0 - �ߧ� �ߧѧاѧ��, 1 - �ߧѧاѧ��)

void GPIO_Initial(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // ���ܧݧ��ѧ֧� ��ѧܧ�ڧ��ӧѧߧڧ� �էݧ� ������� B �� C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    // ���ѧ����ڧ� ������ �էݧ� �ܧߧ���� (PB12, PB13, PC4, PC5) �ܧѧ� �ӧ��է�
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ���ܧݧ��ѧ֧� ���է��اܧ� �� ��ڧ�ѧߧڧ�
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void UART_Init(void) {
    USART_InitTypeDef USART_InitStructure;

    // ���ܧݧ��ѧ֧� ��ѧܧ�ڧ��ӧѧߧڧ� �էݧ� UART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,
            ENABLE);

    // ���ѧ����ڧ� ������ �էݧ� UART (PA9 - TX, PA10 - RX)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���ݧ��֧�ߧѧ�ڧӧߧѧ� ���ߧܧ�ڧ�
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // ������ �ҧ֧� ���է��اܧ�
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� UART
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
    // ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� �������ߧڧ� �ܧߧ����
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttonPressTime[i] = 0;
        buttonState[i] = 0;
    }
}

void Button_Process(void) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        uint8_t currentButtonState = 0;

        // ����֧ߧڧ� �������ߧڧ� �ܧߧ���� (0 - �ߧѧاѧ��, 1 - �ߧ� �ߧѧاѧ��)
        if (i < 2)  // ���ݧ� �ܧߧ���� �ߧ� ������ B
                {
            currentButtonState = GPIO_ReadInputDataBit(GPIOB,
                    (i == 0) ? GPIO_Pin_12 : GPIO_Pin_13);
        } else  // ���ݧ� �ܧߧ���� �ߧ� ������ C
        {
            currentButtonState = GPIO_ReadInputDataBit(GPIOC,
                    (i == 2) ? GPIO_Pin_4 : GPIO_Pin_5);
        }

        // ���ҧ�ѧҧ��ܧ� �������ߧڧ� �ܧߧ��ܧ�
        if (currentButtonState == 0 && buttonState[i] == 0) // ���ߧ��ܧ� ���ݧ�ܧ� ���� �ߧѧاѧ��
                {
            buttonState[i] = 1;
            buttonPressTime[i] = 0;
            Button_LogEvent("Press", i, 0);
        } else if (currentButtonState == 0 && buttonState[i] == 1) // ���ߧ��ܧ� ��է֧�اڧӧѧ֧���
                {
            buttonPressTime[i]++;
            if (buttonPressTime[i] % HOLD_THRESHOLD == 0) {
                Button_LogEvent("Hold", i, buttonPressTime[i] / 10);
            }
        } else if (currentButtonState == 1 && buttonState[i] == 1) // ���ߧ��ܧ� ������֧ߧ�
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
