#include "led.h"
#include "timer.h"

void init_led(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = LED1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = LED2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(LED3_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = LED3_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED3_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(LED4_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = LED4_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED4_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(DEBUG_LED_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = DEBUG_LED_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_LED_GPIO, &GPIO_InitStructure);
    
    Led1Off();
    Led2Off();
    Led3Off();
    Led4Off();
    
}

void LedPutData(uint8_t val)
{
    if (val & 0x01)
        Led4On();
    else
        Led4Off();
    
    if (val & 0x02)
        Led3On();
    else
        Led3Off();
    
    if (val & 0x04)
        Led2On();
    else
        Led2Off();
    
    if (val & 0x08)
        Led1On();
    else
        Led1Off();
}

void BlinkLed(void)
{
     static uint16_t cnt = 0;
    
    cnt = (cnt + 1)%(500/REAL_TIME_SYSTEM);
    if (cnt == 0)
        DebugLedToggle();
}


