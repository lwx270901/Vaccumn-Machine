#include "adc.h"
#include "timer.h"
#include "led.h"

#define NUMBER_OF_SAMPLE		        5
volatile uint16_t raw_adc_value[NUM_OF_CHANNEL];
int32_t adc_value[NUM_OF_CHANNEL];
int32_t dataOfValue[NUM_OF_CHANNEL][NUMBER_OF_SAMPLE];
uint8_t indexOfData = 0;      
int64_t sumOfAdc[NUM_OF_CHANNEL] = {0,0,0,0};

uint8_t sensor_value = 0;
uint16_t v_compare[NUM_OF_CHANNEL] = {400,400,400,400};

uint8_t adc_timeout = 0;

void init_adc(void)
{
    GPIO_InitTypeDef           GPIO_InitStructure; 
    ADC_InitTypeDef            ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA, ENABLE);   
    // PA0, PA1, PA4, PA5 - analog input   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   
    GPIO_Init (GPIOA, &GPIO_InitStructure);   
    // ADC Structure Initialization   
    ADC_StructInit(&ADC_InitStructure);   
    // Preinit   
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;   
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   
    ADC_InitStructure.ADC_NbrOfChannel = 1;   
    ADC_Init(ADC1, &ADC_InitStructure);   
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5); 

    // Enable the ADC   
    ADC_Cmd(ADC1, ENABLE); 

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);   
}

void adc_timeout_counter(void)
{
    if (adc_timeout > 0)
        adc_timeout = adc_timeout - 1;
}

uint16_t adc_get_value(uint8_t adc_channel)
{
	uint16_t adc_value;
	if(adc_channel == 0)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5); 
	else if(adc_channel == 1)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_71Cycles5); 		
	else if(adc_channel == 2)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_71Cycles5); 
	else if(adc_channel == 3)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_71Cycles5);	
		
	
	ADC_ResetCalibration(ADC1);
    adc_timeout = 3;
	while(ADC_GetResetCalibrationStatus(ADC1))
    {
        if (adc_timeout == 0)
            break;
    }
    
	ADC_StartCalibration(ADC1);
    adc_timeout = 3;
	while(ADC_GetCalibrationStatus(ADC1))
    {
        if (adc_timeout == 0)
            break;
    }    
    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);  
    adc_timeout = 3;
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_JSTRT))
    {
        if (adc_timeout == 0)
            break;
    }
	adc_value = ADC_GetConversionValue(ADC1);
	return adc_value;
}

void read_sensor(void)
{ 
    uint8_t temp = 0;
	uint8_t i = 0;   

    for (i = 0; i < 4; i++)
    {
        temp = temp << 1;  
        if (adc_value[i] < v_compare[i]) 
            temp |= 0x01;
        else 
            temp &= 0xfe;
    }
    sensor_value = temp;         

//    LedPutData(sensor_value);       
}

void GetADC(void)
{
	uint16_t i, j;

	for (i = 0; i < NUM_OF_CHANNEL; i++)
        dataOfValue[i][indexOfData] = adc_get_value(i);
	indexOfData = (indexOfData + 1)%NUMBER_OF_SAMPLE;
    
    for (i = 0; i < NUM_OF_CHANNEL; i++)
	{
        sumOfAdc[i] = 0;
        for(j = 0; j < NUMBER_OF_SAMPLE; j++)
        {
            sumOfAdc[i] = sumOfAdc[i] + dataOfValue[i][j];
        }
        adc_value[i] = sumOfAdc[i]/NUMBER_OF_SAMPLE;
    }
    
//    read_sensor();
}
