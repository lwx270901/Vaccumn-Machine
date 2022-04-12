#include "stm32f10x_it.h"
#include "timer.h"
#include "uart.h"
#include "encoder.h"
#include "sr04.h"

void SysTick_Handler(void)
{
    timer_isr();
} 

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        USART1_IRQ_Handler();
    }
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
        USART2_IRQ_Handler();     
    }
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        USART3_IRQ_Handler();
    }
}

//void EXTI9_5_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(EXTI_Line8) != RESET)
//    {
//        encoderPulse[0] = encoderPulse[0] + 1;
//        
//        /* Clear the  EXTI line 4 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line8);
//    }
//}

//void EXTI15_10_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(EXTI_Line15) != RESET)
//    {
//        encoderPulse[1] = encoderPulse[1] + 1;
//        
//        /* Clear the  EXTI line 15 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line15);
//    }
//    
//    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
//    {
//        encoderPulse[2] = encoderPulse[2] + 1;
//        
//        /* Clear the  EXTI line 11 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line11);
//    }
//    
//    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
//    {
//        encoderPulse[3] = encoderPulse[3] + 1;
//        
//        /* Clear the  EXTI line 12 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line12);
//    }
//}

