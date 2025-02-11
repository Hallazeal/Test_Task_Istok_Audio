/*
 * 1_Buttons.c
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#include "ch32v10x.h"
#include "1_Buttons.h"
#include "GPIO/GPIO.h"

static uint32_t buttonPressTime[BUTTON_COUNT] = { 0 };  // Button press time
static uint8_t buttonState[BUTTON_COUNT] = { 0 }; // Button state (0 - not pressed, 1 - pressed)


void Button_Initial(void) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttonPressTime[i] = 0;
        buttonState[i] = 0;
    }
}

void Button_Control(void) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        uint8_t currentButtonState = 0;

        // Reading the state of the buttons (0 - pressed, 1 - not pressed)
        if (i < 2)
                {
            currentButtonState = GPIO_ReadInputDataBit(GPIOB,
                    (i == 0) ? BUTTON_PIN_2 : BUTTON_PIN_1);
        } else
        {
            currentButtonState = GPIO_ReadInputDataBit(GPIOC,
                    (i == 2) ? BUTTON_PIN_4 : BUTTON_PIN_3);
        }

        // Handling the state of a button
        if (currentButtonState == 0 && buttonState[i] == 0) // The button has just been pressed
                {
            buttonState[i] = 1;
            buttonPressTime[i] = 0;
            Button_LogEvent("Press", i, 0);
        } else if (currentButtonState == 0 && buttonState[i] == 1) // The button is held down
                {
            buttonPressTime[i]++;
            if (buttonPressTime[i] % HOLD_THRESHOLD == 0) {
                Button_LogEvent("Hold", i, buttonPressTime[i]);
            }
        } else if (currentButtonState == 1 && buttonState[i] == 1) // The button is released
                {
            buttonState[i] = 0;
            Button_LogEvent("Release", i, 0);
        }
    }
}

void Button_LogEvent(const char* event, int button_id, int duration) {

    if (duration > 0) {
        printf("%s Button %d for %d ms\r\n", event, button_id + 1,
                duration);
    } else {
        printf("%s Button %d\r\n", event, button_id + 1);
    }
}
