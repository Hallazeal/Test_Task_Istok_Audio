/*
 * 4_Links_All_Previous_Tasks.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "4_Links_All_Previous_Tasks.h"

volatile uint8_t blink_active = 0;  // ���ݧѧ� �ѧܧ�ڧӧߧ���� ����ݧ֧է�ӧѧ�֧ݧ�ߧ����

// === ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� GPIO �էݧ� �ӧ����֧� �� �ܧߧ���� ===
void Blink_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE); // ���ѧܧ�ڧ��ӧѧߧڧ� ������ C �� B

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // ����ܧݧ��ѧ֧� ��ӧ֧��էڧ�� (LOW)

    // ���ѧ����ۧܧ� PC5 �ܧѧ� �ӧ��� �էݧ� �ܧߧ��ܧ� �ӧ�ܧݧ��֧ߧڧ� �ӧ����ܧ�
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // ���ѧ����ۧܧ� PB12 �ܧѧ� �ӧ��� �էݧ� �ܧߧ��ܧ� �ӧܧݧ��֧ߧڧ� ����ݧ֧է�ӧѧ�֧ݧ�ߧ���� �ӧ����֧�
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// === ���ܧݧ��֧ߧڧ� �ӧ����ܧ� ===
void Blink_On(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // HIGH - �ӧܧݧ��ѧ֧� ��ӧ֧��էڧ��
}

// === ����ܧݧ��֧ߧڧ� �ӧ����ܧ� ===
void Blink_Off(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LOW - �ӧ�ܧݧ��ѧ֧� ��ӧ֧��էڧ��
}

// === ���ѧ���� ����ݧ֧է�ӧѧ�֧ݧ�ߧ���� �ӧ����֧� ===
void Blinking(void) {
    Blink_On();    // 150 �ާ� ������
    Delay_Ms(150);
    Blink_Off();   // 150 �ާ� ��������
    Delay_Ms(150);
    Blink_On();    // 500 �ާ� ������
    Delay_Ms(500);
    Blink_Off();   // ����ܧݧ��ڧ�� �է� ��ݧ֧է���֧ԧ� �٧ѧ���ܧ�
}

// === ���ҧ�ѧҧ��ܧ� �ߧѧاѧ�ڧ� �ܧߧ���� ===
void Button_Control(void) {
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0) {
        blink_active = 1;  // ���ܧ�ڧӧڧ��֧� ����ݧ֧է�ӧѧ�֧ݧ�ߧ����
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0);
        // ���اڧէѧߧڧ� ������ܧѧߧڧ� �ܧߧ��ܧ�
    }
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0) {
        blink_active = 0;  // ����ܧݧ��ѧ֧� ����ݧ֧է�ӧѧ�֧ݧ�ߧ����
        Blink_Off();
        while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0);
        // ���اڧէѧߧڧ� ������ܧѧߧڧ� �ܧߧ��ܧ�
    }
}
