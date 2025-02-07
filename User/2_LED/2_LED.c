/*
 * 2_LED.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "2_LED.h"

const Color_t Colors[] = { { 0, 0, 0 },    // §¹§Ö§â§ß§í§Û
        { 20, 20, 20 }, // §¢§Ö§Ý§í§Û
        { 20, 0, 0 },   // §¬§â§Ñ§ã§ß§í§Û
        { 0, 20, 0 },   // §©§Ö§Ý§Ö§ß§í§Û
        { 0, 0, 20 },   // §³§Ú§ß§Ú§Û
        { 20, 20, 0 },  // §¨§Ö§Ý§ä§í§Û
        { 20, 0, 20 },  // §±§å§â§á§å§â§ß§í§Û
        { 0, 20, 20 },  // §¢§Ú§â§ð§Ù§à§Ó§í§Û
        { 20, 10, 0 }   // §°§â§Ñ§ß§Ø§Ö§Ó§í§Û
};

static void Delay_us(uint16_t us) {
    for (volatile uint16_t i = 0; i < us * 8; i++) {
        __asm__("nop");
    }
}

// §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ GPIO PC7 (§ã §å§é§Ö§ä§à§Þ §â§Ö§Þ§Ñ§á§Ñ)
void SK6812_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// §°§ä§á§â§Ñ§Ó§Ü§Ñ §à§Õ§ß§à§Ô§à §Ò§Ú§ä§Ñ (T0H/T1H)
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
    Delay_us(T0H_DELAY); // §©§Ñ§Ó§Ö§â§ê§Ö§ß§Ú§Ö §Ò§Ú§ä§Ñ
}

// §°§ä§á§â§Ñ§Ó§Ü§Ñ §à§Õ§ß§à§Ô§à §è§Ó§Ö§ä§Ñ (24 §Ò§Ú§ä§Ñ)
void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = ((uint32_t) g << 16) | ((uint32_t) r << 8) | b;

    for (int i = 23; i >= 0; i--) {
        SK6812_SendBit((color >> i) & 1);
    }
}

// §°§ä§á§â§Ñ§Ó§Ü§Ñ §Õ§Ñ§ß§ß§í§ç §Õ§Ý§ñ §Ó§ã§Ö§ç §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ§à§Ó
void SK6812_SetAll(Color_t color) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        SK6812_SendColor(color.r, color.g, color.b);
    }
}

// §©§Ñ§Ó§Ö§â§ê§Ñ§ð§ë§Ú§Û §ã§Ò§â§à§ã
void SK6812_Show(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
    Delay_us(T_RESET * 1000); // 50 §Þ§Ü§ã
}
