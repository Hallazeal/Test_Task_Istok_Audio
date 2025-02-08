/*
 * 4_Links_All_Previous_Tasks.h
 *
 *  Created on: Feb 8, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_4_LINKS_ALL_PREVIOUS_TASKS_4_LINKS_ALL_PREVIOUS_TASKS_H_
#define USER_4_LINKS_ALL_PREVIOUS_TASKS_4_LINKS_ALL_PREVIOUS_TASKS_H_


extern volatile uint8_t blink_active;

void USART_Initial(void);
void USART_SendString(const char *str);
void Blink_Init(void);
void Blinking(void);
void Button_Control(void);

#endif /* USER_4_LINKS_ALL_PREVIOUS_TASKS_4_LINKS_ALL_PREVIOUS_TASKS_H_ */
