#include "servo.h"
#include "timer.h"
#include "pwm.h"

// 24M / (239 + 1) = 0.1M, so the time for a number is 10us. Timing period: (1999 + 1) * 10us = 20ms
#define SERVO_TIM_ARR  1999
#define SERVO_TIM_PSC  239

int16_t angle[2] = {0, 0};

void init_servo(void)
{
//    GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(SERVO_1_GPIO_CLK, ENABLE);	 	
//	GPIO_InitStructure.GPIO_Pin = SERVO_1_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(SERVO_1_GPIO, &GPIO_InitStructure);
//    
//    RCC_APB2PeriphClockCmd(SERVO_2_GPIO_CLK, ENABLE);	 	
//	GPIO_InitStructure.GPIO_Pin = SERVO_2_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(SERVO_2_GPIO, &GPIO_InitStructure);
//    
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    /* TIM2 counter enable */
    TIM_Cmd(TIM2, ENABLE);

    /* TIM2 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                              	


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = SERVO_TIM_ARR;
    TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM2,ENABLE);	

    TIM_Cmd(TIM2, ENABLE);
    
    TIM_SetCompare3(TIM2,150); //Return the servo to the middle position
    TIM_SetCompare4(TIM2,150); //Return the servo to the middle position
}

//0.5ms--0бу  2.5ms--180бу
void servo_angle(uint8_t servo, uint16_t angle)
{
    uint16_t pulse;
  
    // For the steering gear can be rotated angle limit
    if(angle <= 5)
    angle = 5;
    if(angle >= 175)
    angle = 175;
    // Convert the angle value to a pulse value  
    pulse = (uint16_t)(50 + angle * 100/90.0); //This conversion formula needs to be changed according to the arr and psc configuration of pwm
    
    if (servo == SERVO_1)
        TIM_SetCompare3(TIM2, pulse);
    else if (servo == SERVO_2)
        TIM_SetCompare4(TIM2, pulse);  
}

void SetServo(uint8_t servo, int16_t value)
{
    if (servo < 2)
        angle[servo] = value;
}

void ServoProcess(void)
{
    volatile uint16_t cnt_servo = 0;
    
    GPIO_SetBits(SERVO_1_GPIO, SERVO_1_Pin);
    for (cnt_servo = 0; cnt_servo <= 3600; cnt_servo++);
    for (cnt_servo = 0; cnt_servo <= angle[0]; cnt_servo++);
    GPIO_ResetBits(SERVO_1_GPIO, SERVO_1_Pin);
    
    GPIO_SetBits(SERVO_2_GPIO, SERVO_2_Pin);
    for (cnt_servo = 0; cnt_servo <= 3600; cnt_servo++);
    for (cnt_servo = 0; cnt_servo <= angle[1]; cnt_servo++);
    GPIO_ResetBits(SERVO_2_GPIO, SERVO_2_Pin);    
}
