/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4          // Number of LEDs
#define BIT_COUNT (LED_COUNT * 24)  // 24 bits per LED

#define T0H 17   // 0.35 µs (17 cycles for 72 MHz)
#define T1H 34   // 0.7 µs (34 cycles)
#define RESET_PULSE 80 // tape reset delay (~50 µs)

// === Colors ===
typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern const Color_t BLACK, WHITE, RED, GREEN, BLUE, YELLOW, PURPLE, CYAN, ORANGE;

extern uint16_t pwm_buffer[BIT_COUNT + RESET_PULSE];

void LED_SetColor(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b);
void LED_SetAll(Color_t color);
void LED_Send(void);

#endif /* USER_2_LED_H_ */
