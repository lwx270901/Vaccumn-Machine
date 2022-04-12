#ifndef __SR04_H
#define __SR04_H 			   

#include "stm32f10x.h"

#define SR04_TRIGGER_GPIO             	GPIOB
#define SR04_TRIGGER_GPIO_CLK           RCC_APB2Periph_GPIOB
#define SR04_TRIGGER_Pin           		GPIO_Pin_5

#define SR04_ECHO_GPIO             		GPIOA
#define SR04_ECHO_GPIO_CLK         		RCC_APB2Periph_GPIOA
#define SR04_ECHO_Pin           		GPIO_Pin_8

extern uint16_t sr04_distance;
extern uint16_t sr04_timeout;

void init_sr04(void);
void trigger_pulse(void);
void sr04_countdown(void);
void GetDistance(void);
#endif
