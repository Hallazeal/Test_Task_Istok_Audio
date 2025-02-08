/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4          // §¬§à§Ý§Ú§é§Ö§ã§ä§Ó§à §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ§à§Ó
#define BIT_COUNT (LED_COUNT * 24)  // 24 §Ò§Ú§ä§Ñ §ß§Ñ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ

#define T0H 17   // 0.35 §Þ§Ü§ã (17 §ä§Ñ§Ü§ä§à§Ó §Õ§Ý§ñ 72 §®§¤§è)
#define T1H 34   // 0.7 §Þ§Ü§ã (34 §ä§Ñ§Ü§ä§Ñ)
#define RESET_PULSE 80 // §©§Ñ§Õ§Ö§â§Ø§Ü§Ñ §Õ§Ý§ñ §ã§Ò§â§à§ã§Ñ §Ý§Ö§ß§ä§í (§á§â§Ú§Þ§Ö§â§ß§à 50 §Þ§Ü§ã)

// === §¸§Ó§Ö§ä§Ñ ===
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
