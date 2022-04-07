/*
 * sr04.c
 *
 *  Created on: Apr 1, 2022
 *      Author: ADMIN
 */


#include "sr04.h"
#include "delay.h"

uint16_t sr04_distance = 0;
uint16_t sr04_timeout = 0;

#define SR04_SAMPLE     20
uint16_t sr04_distance_buffer[SR04_SAMPLE];
uint8_t sr04_index = 0;


void init_sr04(void)
{

}

void trigger_pulse(void)
{
    sr04_index = 0;
    HAL_GPIO_WritePin(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin, GPIO_PIN_RESET);
    delay_us(2);
    HAL_GPIO_WritePin(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin, GPIO_PIN_SET);
	delay_us(10);	//delay 10us
	HAL_GPIO_WritePin(SR04_TRIGGER_GPIO, SR04_TRIGGER_Pin, GPIO_PIN_RESET);
}

void sr04_countdown(void)
{
    if (sr04_timeout > 0)
    {
        sr04_timeout = sr04_timeout - 1;
    }
}

uint16_t GetDistance(void)
{
    char i =0;
    static uint32_t time = 0;
    uint32_t sr04_sum = 0;

    trigger_pulse();
    time = 0;
    sr04_timeout = 5;
    while (HAL_GPIO_ReadPin(SR04_ECHO_GPIO, SR04_ECHO_Pin) == 0)
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
    while (HAL_GPIO_ReadPin(SR04_ECHO_GPIO, SR04_ECHO_Pin) == 1)
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
    return sr04_distance;
}

