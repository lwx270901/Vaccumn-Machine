#ifndef __MAIN_H_
#define __MAIN_H_


#include "stm32f10x.h"
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "adc.h"
#include "encoder.h"
#include "pwm.h"
#include "motor.h"
#include "sr04.h"
#include "lock.h"
#include "rgb.h"
#include "servo.h"
#include "watchdog.h"

void init_system(void);
void MainProcess(void);
void HSI_SetSysClk( uint32_t RCC_PLLMul_x);
void Testing(void);

#endif
