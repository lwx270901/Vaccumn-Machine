#ifndef __ADC_H_
#define __ADC_H_

#include "stm32f10x.h"

#define NUM_OF_CHANNEL			4
extern int32_t adc_value[NUM_OF_CHANNEL];
extern uint8_t sensor_value;
extern uint8_t adc_timeout;

void init_adc(void);
void adc_timeout_counter(void);
void GetADC(void);

#endif
