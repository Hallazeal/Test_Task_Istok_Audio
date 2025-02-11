/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

const Color_t Colors[] = { { 0, 0, 0 },    // Black
        { 20, 20, 20 }, // White
        { 20, 0, 0 },   // Red
        { 0, 20, 0 },   // Green
        { 0, 0, 20 },   // Blue
        { 20, 20, 0 },  // Yellow
        { 20, 0, 20 },  // Purple
        { 0, 20, 20 },  // Aqua
        { 20, 10, 0 }   // Orange
};

static void Delay_us(uint16_t us) {
    for (volatile uint16_t i = 0; i < us * 8; i++) {
        __asm__("nop");
    }
}

// Sending one bit (T0H/T1H)
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
    Delay_us(T0H_DELAY); // End of the beat
}

// Sending one color (24 bit)
void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = ((uint32_t) g << 16) | ((uint32_t) r << 8) | b;

    for (int i = 23; i >= 0; i--) {
        SK6812_SendBit((color >> i) & 1);
    }
}

// Sending data to all LEDs
void SK6812_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        SK6812_SendColor(color.r, color.g, color.b);
    }
}

// Final Reset
void SK6812_Show(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    Delay_us(T_RESET * 1000); // 50 us
}
