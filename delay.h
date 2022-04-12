#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f10x.h"

extern volatile uint16_t delay_cnt;

void delay_ms(unsigned int value);
void delay_us(unsigned int value);
void delay_counter(void);

#endif
