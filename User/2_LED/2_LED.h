/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4          // ����ݧڧ�֧��ӧ� ��ӧ֧��էڧ�է��
#define BIT_COUNT (LED_COUNT * 24)  // 24 �ҧڧ�� �ߧ� ��ӧ֧��էڧ��

#define T0H 17   // 0.35 �ާܧ� (17 ��ѧܧ��� �էݧ� 72 ������)
#define T1H 34   // 0.7 �ާܧ� (34 ��ѧܧ��)
#define RESET_PULSE 80 // ���ѧէ֧�اܧ� �էݧ� ��ҧ���� �ݧ֧ߧ�� (���ڧާ֧�ߧ� 50 �ާܧ�)

// === ���ӧ֧�� ===
typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern const Color_t BLACK, WHITE, RED, GREEN, BLUE, YELLOW, PURPLE, CYAN, ORANGE;

void LED_Init(void);
void LED_SetColor(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b);
void LED_SetAll(Color_t color);
void LED_Send(void);

#endif /* USER_2_LED_H_ */
