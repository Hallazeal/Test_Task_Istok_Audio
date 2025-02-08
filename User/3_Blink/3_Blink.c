/*
 * 3_Blink.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "3_Blink.h"

// === ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� GPIO �էݧ� �ӧ����֧� ===
void Blink_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // ���ѧܧ�ڧ��ӧѧߧڧ� ������ C

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // ����ܧݧ��ѧ֧� ��ӧ֧��էڧ�� (HIGH)
}

// === ���ܧݧ��֧ߧڧ� �ӧ����֧� ===
void Blink_On(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // HIGH - �ӧܧݧ��ѧ֧� ��ӧ֧��էڧ��
}

// === ����ܧݧ��֧ߧڧ� �ӧ����֧� ===
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
