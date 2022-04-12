#include "encoder.h"

uint8_t pulse1_prev_state = STATE_01, pulse2_prev_state = STATE_01, pulse3_prev_state = STATE_01, pulse4_prev_state = STATE_01;
int32_t encoderPulse[4] = {0,0,0,0};
int32_t pulseBase[4] = {0,0,0,0};

void init_encoder_2_wire(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(ENC1_A_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC1_A_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC1_A_GPIO, &GPIO_InitStructure);
    
	RCC_APB2PeriphClockCmd(ENC1_B_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC1_B_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC1_B_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(ENC2_A_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC2_A_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC2_A_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(ENC2_B_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC2_B_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC2_B_GPIO, &GPIO_InitStructure);
}

void encoder_2_wire_isr(void)
{
    switch (pulse1_prev_state)
    {
        case STATE_00:
        if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
        {
            encoderPulse[0]++;
            pulse1_prev_state = STATE_01;
        }
        else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
        {
            encoderPulse[0]--;
            pulse1_prev_state = STATE_10;
        }
        else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
        {
            pulse1_prev_state = STATE_11;
        }
        else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
        {
            pulse1_prev_state = STATE_00;
        }
        break;
        case STATE_01:
            if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]++;
                pulse1_prev_state = STATE_11;
            }
            else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]--;
                pulse1_prev_state = STATE_00;
            }
            else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_01;
            }
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]++;
                pulse1_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]--;
                pulse1_prev_state = STATE_01;
            }
            else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_11;
            }
            else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_00;
            }
            break;
        case STATE_10:
            if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]++;
                pulse1_prev_state = STATE_00;
            }
            else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                encoderPulse[0]--;
                pulse1_prev_state = STATE_11;
            }
            else if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && !GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) && GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin))
            {
                pulse1_prev_state = STATE_01;
            }
            break;
        default:
            pulse1_prev_state = STATE_01;
            break;
    }
	
    switch (pulse2_prev_state)
    {	
        case STATE_00:
            if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]++;
                pulse2_prev_state = STATE_01;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]--;
                pulse2_prev_state = STATE_10;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_11;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_00;
            }
            break;
        case STATE_01:
            if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]++;
                pulse2_prev_state = STATE_11;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]--;
                pulse2_prev_state = STATE_00;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_01;
            }
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]++;
                pulse2_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]--;
                pulse2_prev_state = STATE_01;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_11;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_00;
            }
            break;
        case STATE_10:
            if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]++;
                pulse2_prev_state = STATE_00;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                encoderPulse[1]--;
                pulse2_prev_state = STATE_11;
            }
            else if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && !GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_10;
            }
            else if (!GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) && GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin))
            {
                pulse2_prev_state = STATE_01;
            }
            break;
        default:
            pulse2_prev_state = STATE_01;
            break;	
    }
}

void init_encoder_1_wire(void)
{
//    EXTI_InitTypeDef   EXTI_InitStructure;
//    GPIO_InitTypeDef   GPIO_InitStructure;
//    NVIC_InitTypeDef   NVIC_InitStructure;
//        
//    //ENC 1
//    /* Enable GPIOB clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//    /* Configure PB.04 pin as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    /* Enable AFIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

//    /* Connect EXTI4 Line to PB.04 pin */
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

//    /* Configure EXTI4 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);

//    /* Enable and set EXTI4 Interrupt to the lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    //ENC 2
//    /* Enable GPIOB clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//    /* Configure PB.15 pin as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);

//    /* Enable AFIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

//    /* Connect EXTI15 Line to PB.04 pin */
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);

//    /* Configure EXTI15 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line15;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);

//    /* Enable and set EXTI15 Interrupt to the lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    //ENC 3
//    /* Enable GPIOA clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    /* Configure PA.11 pin as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    /* Enable AFIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

//    /* Connect EXTI11 Line to PA.11 pin */
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);

//    /* Configure EXTI11 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);

//    /* Enable and set EXTI11 Interrupt to the lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    //ENC 4
//    /* Enable GPIOA clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    /* Configure PA.12 pin as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    /* Enable AFIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

//    /* Connect EXTI11 Line to PA.12 pin */
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);

//    /* Configure EXTI12 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);

//    /* Enable and set EXTI12 Interrupt to the lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(ENC1_A_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC1_A_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC1_A_GPIO, &GPIO_InitStructure);
    
	RCC_APB2PeriphClockCmd(ENC1_B_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC1_B_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC1_B_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(ENC2_A_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC2_A_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC2_A_GPIO, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(ENC2_B_GPIO_CLK, ENABLE);	 	
	GPIO_InitStructure.GPIO_Pin = ENC2_B_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENC2_B_GPIO, &GPIO_InitStructure);
    
    pulse1_prev_state = STATE_00;
    pulse2_prev_state = STATE_00;
    pulse3_prev_state = STATE_00;
    pulse4_prev_state = STATE_00;
}

void encoder_1_wire_isr(void)
{
    switch (pulse1_prev_state)
    {	
        case STATE_00:
            if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) == 0)
            {
                encoderPulse[0]++;
                pulse1_prev_state = STATE_11;
            }           
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC1_A_GPIO, ENC1_A_Pin) == 1)
            {
                pulse1_prev_state = STATE_00;
            }          
            break;
        default:
            pulse1_prev_state = STATE_00;
            break;	
    }
    switch (pulse2_prev_state)
    {	
        case STATE_00:
            if (GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin) == 0)
            {
                encoderPulse[1]++;
                pulse2_prev_state = STATE_11;
            }           
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC1_B_GPIO, ENC1_B_Pin) == 1)
            {
                pulse2_prev_state = STATE_00;
            }          
            break;
        default:
            pulse2_prev_state = STATE_00;
            break;	
    }
    switch (pulse3_prev_state)
    {	
        case STATE_00:
            if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) == 0)
            {
                encoderPulse[2]++;
                pulse3_prev_state = STATE_11;
            }           
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC2_A_GPIO, ENC2_A_Pin) == 1)
            {
                pulse3_prev_state = STATE_00;
            }          
            break;
        default:
            pulse3_prev_state = STATE_00;
            break;	
    }
    switch (pulse4_prev_state)
    {	
        case STATE_00:
            if (GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin) == 0)
            {
                encoderPulse[3]++;
                pulse4_prev_state = STATE_11;
            }           
            break;
        case STATE_11:
            if (GPIO_ReadInputDataBit(ENC2_B_GPIO, ENC2_B_Pin) == 1)
            {
                pulse4_prev_state = STATE_00;
            }          
            break;
        default:
            pulse4_prev_state = STATE_00;
            break;	
    }
//    if(EXTI_GetITStatus(EXTI_Line8) != RESET)
//    {
//        encoderPulse[0] = encoderPulse[0] + 1;
//        
//        /* Clear the  EXTI line 4 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line8);
//    }
//    
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
}



