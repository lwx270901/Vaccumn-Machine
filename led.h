#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"

#define LED1_GPIO             		GPIOB
#define LED1_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define LED1_Pin           		    GPIO_Pin_3

#define LED2_GPIO             		GPIOB
#define LED2_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define LED2_Pin           		    GPIO_Pin_14

#define LED3_GPIO             		GPIOB
#define LED3_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define LED3_Pin           		    GPIO_Pin_13

#define LED4_GPIO             		GPIOB
#define LED4_GPIO_CLK         		RCC_APB2Periph_GPIOB
#define LED4_Pin           		    GPIO_Pin_12

#define DEBUG_LED_GPIO             	GPIOC
#define DEBUG_LED_GPIO_CLK         	RCC_APB2Periph_GPIOC
#define DEBUG_LED_Pin               GPIO_Pin_13


#define Led1On()       				GPIO_ResetBits(LED1_GPIO, LED1_Pin)
#define Led1Off()      				GPIO_SetBits(LED1_GPIO, LED1_Pin)
#define Led1Toggle()      			LED1_GPIO->ODR ^= LED1_Pin;

#define Led2On()       				GPIO_ResetBits(LED2_GPIO, LED2_Pin)
#define Led2Off()      				GPIO_SetBits(LED2_GPIO, LED2_Pin)
#define Led2Toggle()      			LED2_GPIO->ODR ^= LED2_Pin;

#define Led3On()       				GPIO_ResetBits(LED3_GPIO, LED3_Pin)
#define Led3Off()      				GPIO_SetBits(LED3_GPIO, LED3_Pin)
#define Led3Toggle()      			LED3_GPIO->ODR ^= LED3_Pin;

#define Led4On()       				GPIO_ResetBits(LED4_GPIO, LED4_Pin)
#define Led4Off()      				GPIO_SetBits(LED4_GPIO, LED4_Pin)
#define Led4Toggle()      			LED4_GPIO->ODR ^= LED4_Pin;

#define DebugLedOn()       			GPIO_ResetBits(DEBUG_LED_GPIO, DEBUG_LED_Pin)
#define DebugLedOff()      			GPIO_SetBits(DEBUG_LED_GPIO, DEBUG_LED_Pin)
#define DebugLedToggle()      		DEBUG_LED_GPIO->ODR ^= DEBUG_LED_Pin;

void init_led(void);
void LedPutData(uint8_t val);
void BlinkLed(void);

#endif
