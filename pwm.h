#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

void init_pwm(void);

void TIM3_PWM1(uint8_t duty_cycle);
void TIM3_PWM2(uint8_t duty_cycle);
void TIM3_PWM3(uint8_t duty_cycle);
void TIM3_PWM4(uint8_t duty_cycle);

void TIM4_PWM2(uint8_t duty_cycle);
void TIM4_PWM3(uint8_t duty_cycle);
void TIM4_PWM4(uint8_t duty_cycle);

#endif
