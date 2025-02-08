/*
 * 3_Blink.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "3_Blink.h"

// === §ª§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ GPIO §Õ§Ý§ñ §Ó§ã§á§í§ê§Ö§Ü ===
void Blink_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // §´§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö §á§à§â§ä§Ñ C

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // §£§í§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ (HIGH)
}

// === §£§Ü§Ý§ð§é§Ö§ß§Ú§Ö §Ó§ã§á§í§ê§Ö§Ü ===
void Blink_On(void) {
    GPIO_SetBits(GPIOC, GPIO_Pin_6);  // HIGH - §Ó§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ
}

// === §£§í§Ü§Ý§ð§é§Ö§ß§Ú§Ö §Ó§ã§á§í§ê§Ö§Ü ===
void Blink_Off(void) {
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LOW - §Ó§í§Ü§Ý§ð§é§Ñ§Ö§Þ §ã§Ó§Ö§ä§à§Õ§Ú§à§Õ
}

// === §©§Ñ§á§å§ã§Ü §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§Ú §Ó§ã§á§í§ê§Ö§Ü ===
void Blinking(void) {
    Blink_On();    // 150 §Þ§ã §£§¬§­
    Delay_Ms(150);
    Blink_Off();   // 150 §Þ§ã §£§½§¬§­
    Delay_Ms(150);
    Blink_On();    // 500 §Þ§ã §£§¬§­
    Delay_Ms(500);
    Blink_Off();   // §£§í§Ü§Ý§ð§é§Ú§ä§î §Õ§à §ã§Ý§Ö§Õ§å§ð§ë§Ö§Ô§à §Ù§Ñ§á§å§ã§Ü§Ñ
}
