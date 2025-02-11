/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4
#define T0H_DELAY 350
#define T1H_DELAY 700
#define T_RESET 50

typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern const Color_t Colors[]; // Colors

void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b);
void SK6812_SetAll(Color_t color);
void SK6812_Show(void);

#endif /* USER_2_LED_H_ */
