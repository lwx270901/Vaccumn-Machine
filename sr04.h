/*
 * sr04.h
 *
 *  Created on: Apr 9, 2022
 *      Author: ADMIN
 */

#ifndef INC_SR04_H_
#define INC_SR04_H_

#include "stm32f4xx.h"

#define SR04_TRIGGER_GPIO             	GPIOB
#define SR04_TRIGGER_Pin           		GPIO_PIN_5

#define SR04_ECHO_GPIO             		GPIOA
#define SR04_ECHO_Pin           		GPIO_PIN_10

extern uint16_t sr04_distance;
extern uint16_t sr04_timeout;

void init_sr04(void);
void trigger_pulse(void);
void sr04_countdown(void);
uint16_t GetDistance(void);

#endif /* INC_SR04_H_ */
