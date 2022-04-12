#include "timer.h"
#include "delay.h"
#include "sr04.h"
#include "encoder.h"
#include "adc.h"

volatile unsigned int timer_value = 0;
volatile unsigned int timer_cnt = 0;
unsigned int timer_MUL = 0;
volatile unsigned char flag_timer = 0;

// 1ms
void init_timer(void)
{
	SysTick_Config(24000000/1000);
}
	
void timer_isr(void)
{
	timer_cnt++;
    if (timer_cnt >= timer_MUL)
    {
        timer_cnt = 0;
        flag_timer = 1;
    }
    
	delay_counter();
    sr04_countdown();
    encoder_1_wire_isr();
    adc_timeout_counter();
//    encoder_2_wire_isr();
}

void SetTimer_ms(unsigned int ms)
{
	timer_MUL = ms;
	timer_cnt = 0;
	flag_timer = 0;
}
