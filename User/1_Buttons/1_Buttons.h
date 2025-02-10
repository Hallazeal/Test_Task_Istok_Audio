/*
 * 1_Buttons.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_1_BUTTONS_H_
#define USER_1_BUTTONS_H_

#define BUTTON_COUNT 4
#define HOLD_THRESHOLD 100  // Button hold threshold (100 ms)

void Button_Initial(void);
void Button_Control(void);
void Button_LogEvent(const char* event, int button_id, int duration);


#endif /* USER_1_BUTTONS_H_ */
