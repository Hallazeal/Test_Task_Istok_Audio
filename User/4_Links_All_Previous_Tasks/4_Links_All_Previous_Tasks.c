/*
 * 4_Links_All_Previous_Tasks.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "GPIO/GPIO.h"
#include "4_Links_All_Previous_Tasks.h"

volatile uint8_t blink_active = 0;  // Sequence Activity Flag

void Delay_Ms_Check(uint32_t ms) {
    while (ms--) {
        if (GPIO_ReadInputDataBit(PORT_C, GPIO_Pin_5) == 0) { // If button is pressed
            blink_active = 0;
            Blink_Off();
            printf("Blink stopped\r\n");
            return;
        }
        Delay_Ms(1);
    }
}

void Blink_On(void) {
    GPIO_SetBits(PORT_C, LED_PIN_C);
}

void Blink_Off(void) {
    GPIO_ResetBits(PORT_C, LED_PIN_C);
}

void Blinking(void) {
    Blink_On();    // 150 ms ON
    Delay_Ms_Check(150);
    if (!blink_active)
        return;
    Blink_Off();   // 150 ms OFF
    Delay_Ms_Check(150);
    if (!blink_active)
        return;
    Blink_On();    // 500 ms ON
    Delay_Ms_Check(500);
    if (!blink_active)
        return;
    Blink_Off();
}

void Button_Control(void) {
    if (GPIO_ReadInputDataBit(PORT_B, BUTTON_PIN_B) == 0) {
        blink_active = 1;
        printf("Blink started\r\n");
        while (GPIO_ReadInputDataBit(PORT_B, BUTTON_PIN_B) == 0);
    }
}
