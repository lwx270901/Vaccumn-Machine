#include "servo.h"

// 24M / (239 + 1) = 0.1M, so the time for a number is 10us. Timing period: (1999 + 1) * 10us = 20ms
#define SERVO_TIM_ARR  2000
#define SERVO_TIM_PSC  240

void init_servo(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    /* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    
    /* TIM2 Full Alternate Function mapping */
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

    /*GPIOB Configuration: TIM2 channel 3 and 4 */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = SERVO_TIM_ARR - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PSC - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM2,ENABLE);	

    TIM_Cmd(TIM2, ENABLE);
    
    servo_angle(SERVO_1, 90);
    servo_angle(SERVO_2, 90);
}

//0.5ms--0°--50pulse¡  1.5ms--90°--150pulse¡   2.5ms--180°--250pulse¡
void servo_angle(uint8_t servo, uint16_t angle)
{
    uint16_t pulse;
  
//    // For the steering gear can be rotated angle limit
//    if(angle <= 5)
//    angle = 5;
//    if(angle >= 175)
//    angle = 175;
    // Convert the angle value to a pulse value  
    // y = y0 + (x - x0)*(y1 - y0)/(x1 - x0)
    pulse = 50 + (uint16_t)(angle - 0) * (150 - 50)/(90 - 0); //This conversion formula needs to be changed according to the arr and psc configuration of pwm
    
    if (servo == SERVO_1)
        TIM_SetCompare4(TIM2, pulse);
    else        //SERVO_2
        TIM_SetCompare3(TIM2, pulse);  
}
