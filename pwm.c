#include "pwm.h"

uint16_t timerPeriod = 0;
uint16_t pulseWidth = 0;
TIM_OCInitTypeDef  TIM_OCInitStructure;

void init_pwm(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	/* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
    timerPeriod = (SystemCoreClock / 17570 ) - 1;

    /* MOTOR PWM1, PWM2, PWM3, PWM4 */
    /* TIM3: PA6(CH1), PA7(CH2), PB0(CH3), PB1(CH4) */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = timerPeriod;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Channel 1, 2, 3 , 4 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
        
    /* TIM3 counter enable */
    TIM_Cmd(TIM3, ENABLE);
    
    /* TIM3 Main Output Enable */
//    TIM_CtrlPWMOutputs(TIM3, ENABLE);

    
    
    /* RGB RED, GREEN, BLUE */
    /* TIM4: PB8(CH3), PB9(CH4) */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = timerPeriod;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /* Channel 2, 3 , 4 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    
    /* TIM4 counter enable */
    TIM_Cmd(TIM4, ENABLE);

    /* TIM4 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

void TIM3_PWM1(uint8_t duty_cycle)
{
    duty_cycle = 100 - duty_cycle;
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 100);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
}

void TIM3_PWM2(uint8_t duty_cycle)
{
    duty_cycle = 100 - duty_cycle;
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 100);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
}

void TIM3_PWM3(uint8_t duty_cycle)
{
    duty_cycle = 100 - duty_cycle;
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 100);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
}

void TIM3_PWM4(uint8_t duty_cycle)
{
    duty_cycle = 100 - duty_cycle;
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 100);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
}

void TIM4_PWM2(uint8_t duty_cycle)
{
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 255);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
}

void TIM4_PWM3(uint8_t duty_cycle)
{
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 255);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
}

void TIM4_PWM4(uint8_t duty_cycle)
{
    pulseWidth = (uint16_t) (((uint32_t) duty_cycle * (timerPeriod - 1)) / 255);
    
    TIM_OCInitStructure.TIM_Pulse = pulseWidth;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}

