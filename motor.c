#include "motor.h"
#include "pwm.h"

/*
M1  M3
M2  M4
*/

void init_motor(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DIR_1_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = DIR_1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DIR_1_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(DIR_2_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = DIR_2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DIR_2_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(DIR_3_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = DIR_3_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DIR_3_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(DIR_4_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = DIR_4_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DIR_4_GPIO, &GPIO_InitStructure);
    
    SetSpeed(FRONT, 0, 0);
    SetSpeed(REAR, 0, 0);
}

void SetLeftDir(uint8_t position, uint8_t dir)
{
    if (position == FRONT)
    {
        if (dir == FORWARD)
            GPIO_ResetBits(DIR_1_GPIO, DIR_1_Pin);
        else
            GPIO_SetBits(DIR_1_GPIO, DIR_1_Pin);
    }
    else
    {
        if (dir == FORWARD)
            GPIO_ResetBits(DIR_2_GPIO, DIR_2_Pin);
        else
            GPIO_SetBits(DIR_2_GPIO, DIR_2_Pin);
    }       
}

void SetRightDir(uint8_t position, uint8_t dir)
{
    if (position == FRONT)
    {
        if (dir == FORWARD)
            GPIO_ResetBits(DIR_3_GPIO, DIR_3_Pin);
        else
            GPIO_SetBits(DIR_3_GPIO, DIR_3_Pin);            
    }
    else
    {
        if (dir == FORWARD)
            GPIO_ResetBits(DIR_4_GPIO, DIR_4_Pin);
        else
            GPIO_SetBits(DIR_4_GPIO, DIR_4_Pin);           
    }       
}

void SetSpeed(uint8_t position, int8_t left_speed, int8_t right_speed)
{
    if(left_speed >= 0)
		SetLeftDir(position, FORWARD);
    else
    {
		left_speed = - left_speed;
		SetLeftDir(position, BACKWARD);
	}
	if(right_speed >= 0)
		SetRightDir(position, FORWARD);
	else
    {
		right_speed = - right_speed;
		SetRightDir(position, BACKWARD);
	}
    
    if(left_speed > MAX_SPEED)  
        left_speed = MAX_SPEED;
	if(left_speed < MIN_SPEED)
        left_speed = 0;
	
	if(right_speed > MAX_SPEED)  
        right_speed = MAX_SPEED;
	if(right_speed < MIN_SPEED)  
        right_speed = 0;
    
    if (position == FRONT)
    {
        TIM3_PWM1(left_speed);
        TIM3_PWM3(right_speed);
    }
    else
    {
        TIM3_PWM2(left_speed);
        TIM3_PWM4(right_speed);
    }
}
