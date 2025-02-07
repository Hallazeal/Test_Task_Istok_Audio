/*
 * 1_Buttons.h
 *
 *  Created on: Feb 7, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_1_BUTTONS_H_
#define USER_1_BUTTONS_H_

#define BUTTON_COUNT 4
#define HOLD_THRESHOLD 100  // ������� ��է֧�اѧߧڧ� �ܧߧ��ܧ� (100 ms)

void Button_Init(void);
void Button_Process(void);
void Button_LogEvent(const char* event, int button_id, int duration);
void UART_Init(void);
void GPIO_Initial(void);

#endif /* USER_1_BUTTONS_H_ */
