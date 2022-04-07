#ifndef __MOTOR_H
#define __MOTOR_H 			   

#include "stm32f10x.h"

#define DIR_1_GPIO             		GPIOD
#define DIR_1_GPIO_CLK         		RCC_APB2Periph_GPIOD
#define DIR_1_Pin           		GPIO_Pin_0

#define DIR_2_GPIO             		GPIOD
#define DIR_2_GPIO_CLK         		RCC_APB2Periph_GPIOD
#define DIR_2_Pin           		GPIO_Pin_1

#define DIR_3_GPIO             		GPIOB
#define DIR_3_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define DIR_3_Pin           		GPIO_Pin_2

#define DIR_4_GPIO             		GPIOB
#define DIR_4_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define DIR_4_Pin           		GPIO_Pin_6

#define BACKWARD		0
#define FORWARD			1

#define FRONT           0
#define REAR            1

#define MAX_SPEED		100
#define MIN_SPEED		0

void init_motor(void);
void SetSpeed(uint8_t position, int8_t left_speed, int8_t right_speed);

#endif
