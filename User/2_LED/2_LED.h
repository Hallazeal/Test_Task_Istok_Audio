/*
 * 2_LED.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_2_LED_H_
#define USER_2_LED_H_

#include "ch32v10x.h"

#define LED_COUNT 4 // §¬§à§Ý§Ú§é§Ö§ã§ä§Ó§à §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ§à§Ó
#define T0H_DELAY 350   // 0.35 §Þ§Ü§ã
#define T1H_DELAY 700   // 0.7 §Þ§Ü§ã
#define T_RESET 50      // 50 §Þ§Ü§ã (§Ó §Þ§Ú§Ý§Ý§Ú§ã§Ö§Ü§å§ß§Õ§Ñ§ç)

// §°§á§â§Ö§Õ§Ö§Ý§Ö§ß§Ú§Ö §è§Ó§Ö§ä§à§Ó
typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern const Color_t Colors[]; // §±§â§Ö§Õ§à§á§â§Ö§Õ§Ö§Ý§Ö§ß§ß§í§Ö §è§Ó§Ö§ä§Ñ

void SK6812_Init(void);
void SK6812_SendColor(uint8_t r, uint8_t g, uint8_t b);
void SK6812_SetAll(Color_t color);
void SK6812_Show(void);

#endif /* USER_2_LED_H_ */
