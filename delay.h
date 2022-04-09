

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stm32f4xx.h"

extern volatile uint16_t delay_cnt;

void delay_ms(unsigned int value);
void delay_us(unsigned int value);
void delay_counter(void);

#endif /* INC_DELAY_H_ */
