#include "delay.h"

volatile uint16_t delay_cnt = 0;

void delay_ms(unsigned int value)
{
	if (delay_cnt == 0) 
	{
		delay_cnt = value;
	}
	while (delay_cnt > 0);
}

void delay_counter(void)
{
    if(delay_cnt > 0)
	{
		delay_cnt --;
	}
}

void delay_us(unsigned int value)
{
	volatile unsigned int i,j;
	for(i=0;i<value;i++)
		for(j=0;j<5;j++);
}
