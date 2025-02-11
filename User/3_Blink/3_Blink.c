/*
 * 3_Blink.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "3_Blink.h"
#include "GPIO/GPIO.h"


void Blink_On(void) {
    GPIO_SetBits(GPIOC, LED_PIN);  // HIGH - turn on the LED
}

void Blink_Off(void) {
    GPIO_ResetBits(GPIOC, LED_PIN);  // LOW - turn off the LED
}

void Blinking(void) {
    Blink_On();    // 150 ms ON
    Delay_Ms(150);
    Blink_Off();   // 150 ms OFF
    Delay_Ms(150);
    Blink_On();    // 500 ms ON
    Delay_Ms(500);
    Blink_Off();
}
