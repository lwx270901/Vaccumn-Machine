#include "sr04.h"
#include "delay.h"
#include "timer.h"

uint16_t sr04_distance = 0;
uint16_t sr04_timeout = 0;

#define SR04_SAMPLE     20
uint16_t sr04_distance_buffer[SR04_SAMPLE];
uint8_t sr04_index = 0;      


void init_sr04(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SR04_TRIGGER_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = SR04_TRIGGER_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SR04_TRIGGER_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(SR04_ECHO_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = SR04_ECHO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(SR04_ECHO_GPIO, &GPIO_InitStructure);
}

void trigger_pulse(void)
{
    sr04_index = 0;
    
    GPIO_ResetBits(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin);
    delay_us(2);
	GPIO_SetBits(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin);
	delay_us(10);	//delay 10us
	GPIO_ResetBits(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin);
}

void sr04_countdown(void)
{
    if (sr04_timeout > 0)
    {
        sr04_timeout = sr04_timeout - 1;
    }
}

void GetDistance(void)
{
    char i =0;
    static uint32_t time = 0;
    uint32_t sr04_sum = 0;
        
    trigger_pulse();
    time = 0;
    sr04_timeout = 5;
    while (GPIO_ReadInputDataBit(SR04_ECHO_GPIO, SR04_ECHO_Pin) == 0)
    {
        time++;
        //delay_us(1);
        if (time > 5000) 
            break;
        if (sr04_timeout == 0)
        {
            time = 5000;
            break;
        }
    }
    time = 0;
    sr04_timeout = 5;
    while (GPIO_ReadInputDataBit(SR04_ECHO_GPIO, SR04_ECHO_Pin) == 1)
    {
        time++;
        //delay_us(1);
        if (time > 5000) 
            break;
        if (sr04_timeout == 0)
        {
            time = 5000;
            break;
        }
    }
    
    sr04_distance_buffer[sr04_index] = time;
    sr04_index = (sr04_index + 1)%SR04_SAMPLE;
    
    sr04_sum = 0;
    for (i = 0; i < SR04_SAMPLE; i++)
    {
        sr04_sum = sr04_sum + sr04_distance_buffer[i];
    }
    sr04_distance = sr04_sum / SR04_SAMPLE;
    sr04_distance = sr04_distance * 20 / 50;
}

