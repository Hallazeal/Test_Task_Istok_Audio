/*
 * GPIO.h
 *
 *  Created on: Feb 11, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_GPIO_GPIO_H_
#define USER_GPIO_GPIO_H_

#define PORT_B           RCC_APB2Periph_GPIOB
#define PORT_C           RCC_APB2Periph_GPIOC

#define BUTTON_PIN_2            GPIO_Pin_12
#define BUTTON_PIN_3            GPIO_Pin_5
#define LED_PIN                 GPIO_Pin_6

void GPIO_Initial(void);

#endif /* USER_GPIO_GPIO_H_ */
