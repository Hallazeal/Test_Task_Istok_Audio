/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4 // ����ݧڧ�֧��ӧ� ��ӧ֧��էڧ�է��
#define T0H_DELAY 350   // 0.35 �ާܧ�
#define T1H_DELAY 700   // 0.7 �ާܧ�
#define T_RESET 50      // 50 �ާܧ� (�� �ާڧݧݧڧ�֧ܧ�ߧէѧ�)

// �����֧է֧ݧ֧ߧڧ� ��ӧ֧���
typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern const Color_t Colors[]; // ����֧է���֧է֧ݧ֧ߧߧ�� ��ӧ֧��

void SK6812_Init(void);
void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b);
void SK6812_SetAll(Color_t color);
void SK6812_Show(void);

#endif /* USER_2_LED_H_ */
