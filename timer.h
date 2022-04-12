#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f10x.h"

#define REAL_TIME_SYSTEM    20
extern volatile unsigned char flag_timer;

void init_timer(void);
void timer_isr(void);
void SetTimer_ms(unsigned int ms);
uint32_t get_systick(void);

#endif
