#include "uart.h"
#include "timer.h"
#include <string.h>

#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
    
#define RECEIVE_DATA    1
#define RECEIVE_END     2
unsigned char statusDataProcess = RECEIVE_DATA;
unsigned char flagReceiveComplete = 0;

char bufferOfDataReceive[RECEIVE_BYTES];
uint16_t indexOfDataReceive = 0;
    
unsigned long uart_power_of(int a, int x) 
{
    char i;
    unsigned long temp = 1;
    for(i = 0; i < x; i++)
            temp *= a;
    return temp;
}

void USART1_Init(uint32_t baudrate)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	/* Configure USART1 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	
	/* Configure USART1 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	/* Enable USART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
	
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* Configures the priority grouping: pre-emption priority and subpriority. */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* NVIC Init Structure definition */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
}

void USART2_Init(uint32_t baudrate)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(USART2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	
	/* Configure USART2 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);
	
	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

	/* Enable USART clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	
	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* Configures the priority grouping: pre-emption priority and subpriority. */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* NVIC Init Structure definition */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
	/* Enable USART */
	USART_Cmd(USART2, ENABLE);
}

void USART3_Init(uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(USART3_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);
	/* Configure USART3 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
	
	/* Configure USART3 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(USART3_GPIO, &GPIO_InitStructure);

	/* Enable USART clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	
	/* Enable USART3 Receive and Transmit interrupts */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* Configures the priority grouping: pre-emption priority and subpriority. */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* NVIC Init Structure definition */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USART */
	USART_Cmd(USART3, ENABLE);
}


void USART1_SendChar(char chr)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, chr);    
}

void USART2_SendChar(char chr)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, chr);    
}

void USART3_SendChar(char chr)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3, chr);
}

void USART1_SendString(char* str)
{
	while(*str)	
	{
		USART1_SendChar(*str++);
	}
}

void USART2_SendString(char* str)
{
	while(*str)	
	{
        USART2_SendChar(*str++);
	}
}

void USART3_SendString(char* str)
{
	while(*str)	
	{
		USART3_SendChar(*str++);
	}
}

void USART1_IRQ_Handler(void)
{
	uint8_t data = 0;
	data = USART_ReceiveData(USART1);
    
//    switch(statusDataProcess)
//    {
//        case RECEIVE_DATA:
//            if(data != '#')
//            {
//                bufferOfDataReceive[indexOfDataReceive] = data;
//                indexOfDataReceive = (indexOfDataReceive + 1)%RECEIVE_BYTES;
//            }
//            else
//            {
//                statusDataProcess = RECEIVE_END;
//            }
//            break;
//        case RECEIVE_END:
//            if(data == '#')
//            {
//                flagReceiveComplete = 1;
//            }
//            statusDataProcess = RECEIVE_DATA;
//            break;
//        default:
//            indexOfDataReceive = 0;
//            flagReceiveComplete = 0;
//            statusDataProcess = RECEIVE_DATA;
//            break;  
//    }
//    USART1_SendChar(data);
    
//    switch(statusDataProcess)
//    {
//        case RECEIVE_DATA:
//            if(data != 0x0d)
//            {
//                bufferOfDataReceive[indexOfDataReceive] = data;
//                indexOfDataReceive ++;
//            }
//            else
//            {
//                statusDataProcess = RECEIVE_END;
//            }
//            break;
//        case RECEIVE_END:
//            if(data == 0x0a)
//            {
//                flagReceiveComplete = 1;
//            }
//            statusDataProcess = RECEIVE_DATA;
//            break;
//        default:
//            indexOfDataReceive = 0;
//            flagReceiveComplete = 0;
//            statusDataProcess = RECEIVE_DATA;
//            break;  
//    }
}

void USART2_IRQ_Handler(void)
{
	uint8_t data = 0; 	   
	data = USART_ReceiveData(USART2);
    
    switch(statusDataProcess)
    {
        case RECEIVE_DATA:
            if(data != '#')
            {
                bufferOfDataReceive[indexOfDataReceive] = data;
                indexOfDataReceive = (indexOfDataReceive + 1)%RECEIVE_BYTES;
            }
            else
            {
                statusDataProcess = RECEIVE_END;
            }
            break;
        case RECEIVE_END:
            if(data == '#')
            {
                flagReceiveComplete = 1;
            }
            statusDataProcess = RECEIVE_DATA;
            break;
        default:
            indexOfDataReceive = 0;
            flagReceiveComplete = 0;
            statusDataProcess = RECEIVE_DATA;
            break;  
    }
//    USART1_SendChar(data);
}

void USART3_IRQ_Handler(void)
{
	uint8_t data = 0; 	   
	data = USART_ReceiveData(USART3);
    
}

void USART1_SendGraphData(unsigned int Data1, unsigned int Data2, unsigned int Data3)
{	
	USART1_SendChar(0xFF);
	USART1_SendChar(0xFF);
	USART1_SendChar(Data1/256);
	USART1_SendChar(Data1%256);
	USART1_SendChar(Data2/256);
	USART1_SendChar(Data2%256);
	USART1_SendChar(Data3/256);
	USART1_SendChar(Data3%256);
	USART1_SendChar(0);
	USART1_SendChar(0);
	USART1_SendChar(0xFE);
	USART1_SendChar(0xFE);
}

void USART2_SendGraphData(unsigned int Data1, unsigned int Data2, unsigned int Data3)
{	
	USART2_SendChar(0xFF);
	USART2_SendChar(0xFF);
	USART2_SendChar(Data1/256);
	USART2_SendChar(Data1%256);
	USART2_SendChar(Data2/256);
	USART2_SendChar(Data2%256);
	USART2_SendChar(Data3/256);
	USART2_SendChar(Data3%256);
	USART2_SendChar(0);
	USART2_SendChar(0);
	USART2_SendChar(0xFE);
	USART2_SendChar(0xFE);
}

void USART3_SendGraphData(unsigned int Data1, unsigned int Data2, unsigned int Data3)
{	
	USART3_SendChar(0xFF);
	USART3_SendChar(0xFF);
	USART3_SendChar(Data1/256);
	USART3_SendChar(Data1%256);
	USART3_SendChar(Data2/256);
	USART3_SendChar(Data2%256);
	USART3_SendChar(Data3/256);
	USART3_SendChar(Data3%256);
	USART3_SendChar(0);
	USART3_SendChar(0);
	USART3_SendChar(0xFE);
	USART3_SendChar(0xFE);
}

void USART1_SendNum(long num)
{
    char _sNum[15];
    sprintf(_sNum, "%ld", num);
    
    USART1_SendString(_sNum);
}

void USART2_SendNum(long num)
{
    char _sNum[15];
    sprintf(_sNum, "%ld", num);
    
    USART2_SendString(_sNum);
}

void USART3_SendNum(long num)
{
    char _sNum[15];
    sprintf(_sNum, "%ld", num);
    
    USART3_SendString(_sNum);
}

void USART1_SendNumPercent(long num)
{
    USART1_SendNum(num/100);
    USART1_SendChar('.');
    USART1_SendNum(num%100/10);
	USART1_SendNum(num%100%10);
}

void USART2_SendNumPercent(long num)
{
    USART2_SendNum(num/100);
    USART2_SendChar('.');
    USART2_SendNum(num%100/10);
	USART2_SendNum(num%100%10);
}

void USART3_SendNumPercent(long num)
{
    USART3_SendNum(num/100);
    USART3_SendChar('.');
    USART3_SendNum(num%100/10);
	USART3_SendNum(num%100%10);
}

void USART1_SendNumOneDigit(uint32_t num)
{
	USART1_SendNum(num/10);
	USART1_SendChar('.');
	USART1_SendNum(num%10);
}

void USART2_SendNumOneDigit(uint32_t num)
{
	USART2_SendNum(num/10);
	USART2_SendChar('.');
	USART2_SendNum(num%10);
}

void USART3_SendNumOneDigit(uint32_t num)
{
	USART3_SendNum(num/10);
	USART3_SendChar('.');
	USART3_SendNum(num%10);
}


PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

