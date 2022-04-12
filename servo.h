#ifndef __SERVO_H_
#define __SERVO_H_

#include "stm32f10x.h"

#define SERVO_1_GPIO             		GPIOB
#define SERVO_1_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define SERVO_1_Pin           		    GPIO_Pin_11

#define SERVO_2_GPIO             		GPIOB
#define SERVO_2_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define SERVO_2_Pin           		    GPIO_Pin_10

#define SERVO_1     0
#define SERVO_2     1


void init_servo(void);
void servo_angle(uint8_t servo, uint16_t angle);

#endif
