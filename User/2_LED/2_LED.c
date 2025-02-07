/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

const Color_t Colors[] = { { 0, 0, 0 },    // ���֧�ߧ��
        { 20, 20, 20 }, // ���֧ݧ��
        { 20, 0, 0 },   // ����ѧ�ߧ��
        { 0, 20, 0 },   // ���֧ݧ֧ߧ��
        { 0, 0, 20 },   // ���ڧߧڧ�
        { 20, 20, 0 },  // ���֧ݧ���
        { 20, 0, 20 },  // ��������ߧ��
        { 0, 20, 20 },  // ���ڧ��٧�ӧ��
        { 20, 10, 0 }   // ����ѧߧا֧ӧ��
};

static void Delay_us(uint16_t us) {
    for (volatile uint16_t i = 0; i < us * 8; i++) {
        __asm__("nop");
    }
}

// ���ߧڧ�ڧѧݧڧ٧ѧ�ڧ� GPIO PC7 (�� ���֧��� ��֧ާѧ��)
void SK6812_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// ������ѧӧܧ� ��էߧ�ԧ� �ҧڧ�� (T0H/T1H)
static void SK6812_SendBit(uint8_t bit) {
    if (bit) {
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
        Delay_us(T1H_DELAY);
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    } else {
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
        Delay_us(T0H_DELAY);
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    }
    Delay_us(T0H_DELAY); // ���ѧӧ֧��֧ߧڧ� �ҧڧ��
}

// ������ѧӧܧ� ��էߧ�ԧ� ��ӧ֧�� (24 �ҧڧ��)
void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = ((uint32_t) g << 16) | ((uint32_t) r << 8) | b;

    for (int i = 23; i >= 0; i--) {
        SK6812_SendBit((color >> i) & 1);
    }
}

// ������ѧӧܧ� �էѧߧߧ�� �էݧ� �ӧ�֧� ��ӧ֧��էڧ�է��
void SK6812_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        SK6812_SendColor(color.r, color.g, color.b);
    }
}

// ���ѧӧ֧��ѧ��ڧ� ��ҧ���
void SK6812_Show(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    Delay_us(T_RESET * 1000); // 50 �ާܧ�
}
