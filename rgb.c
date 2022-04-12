#include "rgb.h"
#include "timer.h"
#include "pwm.h"


void SetLedRGB(uint16_t color)
{
    if (color == RED)
    {
        TIM4_PWM2(255);
        TIM4_PWM3(0);
        TIM4_PWM4(0);
    }
    else if (color == GREEN)
    {
        TIM4_PWM2(0);
        TIM4_PWM3(255);
        TIM4_PWM4(0);
    }
    else if (color == BLUE)
    {
        TIM4_PWM2(0);
        TIM4_PWM3(0);
        TIM4_PWM4(255);
    }
    else if (color == YELLOW)
    {
        TIM4_PWM2(250);
        TIM4_PWM3(200);
        TIM4_PWM4(0);
    }
    else if (color == CYAN)
    {
        TIM4_PWM2(255);
        TIM4_PWM3(0);
        TIM4_PWM4(255);
    }
    else if (color == MAGENTA)
    {
        TIM4_PWM2(0);
        TIM4_PWM3(255);
        TIM4_PWM4(255);
    }
    else
    {
        TIM4_PWM2(0);
        TIM4_PWM3(0);
        TIM4_PWM4(0);
    }  
}
