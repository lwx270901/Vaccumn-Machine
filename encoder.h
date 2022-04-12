#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "stm32f10x.h"

#define STATE_00		0
#define STATE_01		1
#define STATE_11		2
#define STATE_10		3

#define ENC1_A_GPIO             		GPIOB
#define ENC1_A_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define ENC1_A_Pin           		    GPIO_Pin_4

#define ENC1_B_GPIO             		GPIOB
#define ENC1_B_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define ENC1_B_Pin           		    GPIO_Pin_15

#define ENC2_A_GPIO             		GPIOA
#define ENC2_A_GPIO_CLK         		RCC_APB2Periph_GPIOA
#define ENC2_A_Pin           		    GPIO_Pin_11

#define ENC2_B_GPIO             		GPIOA
#define ENC2_B_GPIO_CLK         		RCC_APB2Periph_GPIOA
#define ENC2_B_Pin           		    GPIO_Pin_12

extern int32_t encoderPulse[4];
extern int32_t pulseBase[4];

void init_encoder_2_wire(void);
void encoder_2_wire_isr(void);

void init_encoder_1_wire(void);
void encoder_1_wire_isr(void);

#endif
