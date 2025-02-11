/*
 * GPIO.h
 *
 *  Created on: Feb 11, 2025
 *      Author: Nikita Danilov
 */

#ifndef USER_GPIO_GPIO_H_
#define USER_GPIO_GPIO_H_

#define PORT_C      RCC_APB2Periph_GPIOC

#define LED_PIN     GPIO_Pin_6

void GPIO_Initial(void);

#endif /* USER_GPIO_GPIO_H_ */
