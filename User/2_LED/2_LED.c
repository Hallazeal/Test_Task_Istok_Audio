/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

// Buffer for DMA data transfer
uint16_t pwm_buffer[BIT_COUNT + RESET_PULSE] = { 0 };

const Color_t BLACK = { 0, 0, 0 }, WHITE = { 20, 20, 20 }, RED = { 20, 0, 0 },
        GREEN = { 0, 20, 0 }, BLUE = { 0, 0, 20 }, YELLOW = { 20, 20, 0 },
        PURPLE = { 20, 0, 20 }, AQUA = { 0, 20, 20 }, ORANGE = { 20, 10, 0 };

// === Color encoding into PWM buffer ===
void LED_SetColor(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b) {
    uint16_t bit_index = led_index * 24;
    uint32_t color = (g << 16) | (r << 8) | b;

    for (int i = 0; i < 24; i++) {
        if (color & (1 << (23 - i))) {
            pwm_buffer[bit_index + i] = T1H;
        } else {
            pwm_buffer[bit_index + i] = T0H;
        }
    }
}

// === Sending data using DMA ===
void LED_Send(void) {
    for (int i = 0; i < RESET_PULSE; i++) {
        pwm_buffer[BIT_COUNT + i] = 0;  // Reset period
    }

    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3, BIT_COUNT + RESET_PULSE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
}

// === Setting the color for all LEDs ===
void LED_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        LED_SetColor(i, color.r, color.g, color.b);
    }
    LED_Send();
}
