#include "main.h"
#include "math.h"      
#include "string.h"

void ControlMotor(void);
void ResponseSensorValue(void);
void ResponseDistanceValue(void);
void ResetEncoderPulse(void);
void ResponseEnncoderPulse(void);
void ControlRGBLed(void);
void ControlLed(void);
void ControlServo(void);
void MicrobitProcess(void);
void ServoTesting(void);

uint16_t startIndex = 0;

int main(void)
{   
    uint16_t cnt = 0, angle = 0;
//    LockChip();

    init_system();

    printf("\rAI Robot\r\n");
    
    EnableWatchdogTimer();
    
    SetSpeed(FRONT,60, 60);
    SetSpeed(REAR, 60, 60);
    delay_ms(500);
    SetSpeed(FRONT,0, 0);
    SetSpeed(REAR, 0, 0);
    while (1)
    {
        while (!flag_timer);
        flag_timer = 0;
        
        BlinkLed();

        GetADC();
        GetDistance();
//        cnt = (cnt + 1)%(1000/REAL_TIME_SYSTEM);
//        if (cnt == 0)
//        {
//            angle = angle + 10;
//            if (angle > 180)
//                angle = 0;
//            servo_angle(SERVO_2, angle);
//        }
        MicrobitProcess();
        
        WatchdogTimerReload();
    }
}

void init_system(void)    
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);   
    
    HSI_SetSysClk(RCC_PLLMul_6);   //PLLCLK = 8 / 2 * 6 = 24 Mhz
    
    init_led();
    init_timer();
	SetTimer_ms(REAL_TIME_SYSTEM);
    
	USART1_Init(115200);
    USART2_Init(9600);
    
    init_adc();
    init_encoder_1_wire();
    init_pwm();
    init_motor();
    init_sr04();
    init_servo();
    
    SetLedRGB(RED);
    delay_ms(300);
    SetLedRGB(GREEN);
    delay_ms(300);
    SetLedRGB(BLUE);
    delay_ms(300);
    SetLedRGB(WHITE);
    
    init_watchdog(WATCHDOG_Timeout_1s);
    
}

void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus = 0;
	
	 // Reset the RCC register to the reset value
	RCC_DeInit();	
 
	 // Enable HSI 
	RCC_HSICmd(ENABLE);
	
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if( HSIStatus == RCC_CR_HSIRDY )
	{
		// Enable prefetch
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		 // Configure PLLCLK = PLL_HSI * RCC_PLLMul_x
        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		
         // Enable PLL
		RCC_PLLCmd(ENABLE);
		
		 // Wait for the PLL to stabilize
		while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET );
		
         // Select the system clock
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
        while( RCC_GetSYSCLKSource() != 0x08 );
	}
	else
    {
		 /* If the HSI fails to start, the user can add a code to handle the error here */
	}
}

void SetSysClockTo24Mhz(void)   //24Mhz
{
    RCC_ClocksTypeDef RCC_ClockFreq;
    ErrorStatus HSEStartUpStatus;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
		RCC_HCLKConfig(RCC_SYSCLK_Div256); 
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div1);

		/* PLLCLK = 16MHz / 2 * 3 = 24 MHz */
		RCC_PLLConfig(RCC_PREDIV1_Div2, RCC_PLLMul_3);

		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while (RCC_GetSYSCLKSource() != 0x08);
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    
    }

    /* This function fills the RCC_ClockFreq structure with the current
     frequencies of different on chip clocks (for debug purpose) */
    RCC_GetClocksFreq(&RCC_ClockFreq);

    /* Enable Clock Security System(CSS): this will generate an NMI exception
     when HSE clock fails */
    RCC_ClockSecuritySystemCmd(ENABLE);     
}


void Testing(void)
{
    uint8_t i = 0;
    static uint8_t cnt = 0;
    static uint16_t old_distance = 0;
    
    for (i = 0; i < 2; i++)
    {
        if (pulseBase[i] != encoderPulse[i])
        {
            pulseBase[i] = encoderPulse[i];
            printf("Pulse %d: %d\r\n", i + 1, encoderPulse[i]);
        }
    }
    
    if (old_distance != sr04_distance)
    {
        old_distance = sr04_distance;
        printf("Distance : %d\r\n", sr04_distance);
    }
    
    cnt = (cnt + 1)%(1000/REAL_TIME_SYSTEM);
    if (cnt == 0)
    {
        printf("ADC : %d, %d, %d, %d\r\n", adc_value[0], adc_value[1], adc_value[2], adc_value[3]);
        printf("Sensor: 0x%02x\r\n", sensor_value);
    }
}

void MicrobitProcess(void)
{
    uint8_t i = 0;
    if (flagReceiveComplete == 1)
    {
        printf("flag\r\n");
        for (i = 0; i < indexOfDataReceive; i++)
            USART1_SendChar(bufferOfDataReceive[i]);
        flagReceiveComplete = 0;
        if (bufferOfDataReceive[indexOfDataReceive - 17] == 'm')
        {
            startIndex = indexOfDataReceive - 17;
            ControlMotor();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 1] == 's')
        {
            startIndex = indexOfDataReceive - 1;
            ResponseSensorValue();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 1] == 'd')
        {
            startIndex = indexOfDataReceive - 1;
            ResponseDistanceValue();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 1] == 'r')
        {
            startIndex = indexOfDataReceive - 1;
            ResetEncoderPulse();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 1] == 'e')
        {
            startIndex = indexOfDataReceive - 1;
            ResponseEnncoderPulse();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 9] == 'j')
        {
            startIndex = indexOfDataReceive - 9;
            ControlServo();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 2] == 'l')
        {
            startIndex = indexOfDataReceive - 2;
            ControlRGBLed();
        }
        else if (bufferOfDataReceive[indexOfDataReceive - 5] == 'b')
        {
            startIndex = indexOfDataReceive - 5;
            ControlLed();
        }
        
        indexOfDataReceive = 0;
    }
    
    
}

void MicrobitSendChar(char chr)
{
	USART2_SendChar(chr);  
}

void MicrobitSendString(char* str)
{
	while(*str)	
	{
		MicrobitSendChar(*str++);
	}
}

void MicrobitSendNum(long num)
{
    char _sNum[15];
    sprintf(_sNum, "%ld", num);
    
    MicrobitSendString(_sNum);
}

void MicrobitSendNum3Digit(long num)
{
    MicrobitSendNum(num/100%10);
    MicrobitSendNum(num/10%10);
    MicrobitSendNum(num/1%10);
}

void ControlMotor(void)
{
    static int16_t front_left_speed = 0, front_right_speed = 0;
    static int16_t rear_left_speed = 0, rear_right_speed = 0;
    
    front_left_speed = (bufferOfDataReceive[startIndex + 2] - '0') * 100 + (bufferOfDataReceive[startIndex + 3] - '0') * 10 + (bufferOfDataReceive[startIndex + 4] - '0');
    front_right_speed = (bufferOfDataReceive[startIndex + 6] - '0') * 100 + (bufferOfDataReceive[startIndex + 7] - '0') * 10 + (bufferOfDataReceive[startIndex + 8] - '0');
    
    rear_left_speed = (bufferOfDataReceive[startIndex + 10] - '0') * 100 + (bufferOfDataReceive[startIndex + 11] - '0') * 10 + (bufferOfDataReceive[startIndex + 12] - '0');
    rear_right_speed = (bufferOfDataReceive[startIndex + 14] - '0') * 100 + (bufferOfDataReceive[startIndex + 15] - '0') * 10 + (bufferOfDataReceive[startIndex + 16] - '0');
    
    if (front_left_speed > 200)
        front_left_speed = 100;
    if (front_right_speed > 200)
        front_right_speed = 100;
    
    if (rear_left_speed > 200)
        rear_left_speed = 100;
    if (rear_right_speed > 200)
        rear_right_speed = 100;
    
//    printf("Front Speed: %d, %d\r\n", front_left_speed, front_right_speed);
//    printf("Rear Speed: %d, %d\r\n", rear_left_speed, rear_right_speed);
   
    SetSpeed(FRONT, front_left_speed - 100, front_right_speed - 100);
    SetSpeed(REAR, rear_left_speed - 100, rear_right_speed - 100);
}

void ResponseSensorValue(void)
{
    uint16_t sensor_1, sensor_2, sensor_3, sensor_4;
    
    // Get 8-bit ADC
    sensor_1 = adc_value[0]/4;
    sensor_2 = adc_value[1]/4;
    sensor_3 = adc_value[2]/4;
    sensor_4 = adc_value[3]/4;
    
    // Send data
    MicrobitSendNum3Digit(sensor_1);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(sensor_2);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(sensor_3);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(sensor_4);
    MicrobitSendString("\r\n");
}

void ResponseDistanceValue(void)
{   
    MicrobitSendNum(sr04_distance);
    MicrobitSendString("\r\n");
}

void ResetEncoderPulse(void)
{
    encoderPulse[0] = 0;
    encoderPulse[1] = 0;
    encoderPulse[2] = 0;
    encoderPulse[3] = 0;
}

void ResponseEnncoderPulse(void)
{   
    uint16_t pulse_1, pulse_2, pulse_3, pulse_4;
    
    // Get encoder pulse
    pulse_1 = encoderPulse[0]%1000;
    pulse_2 = encoderPulse[1]%1000;
    pulse_3 = encoderPulse[2]%1000;
    pulse_4 = encoderPulse[3]%1000;
    
    // Send data
    MicrobitSendNum3Digit(pulse_1);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(pulse_2);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(pulse_3);
    MicrobitSendChar(':');
    MicrobitSendNum3Digit(pulse_4);
    MicrobitSendString("\r\n");
}

void ControlRGBLed(void)
{
    if (bufferOfDataReceive[startIndex + 1] == '1')
    {
        SetLedRGB(RED);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '2')
    {
        SetLedRGB(GREEN);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '3')
    {
        SetLedRGB(BLUE);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '4')
    {
        SetLedRGB(YELLOW);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '5')
    {
        SetLedRGB(CYAN);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '6')
    {
        SetLedRGB(MAGENTA);
    }
    else if (bufferOfDataReceive[startIndex + 1] == '7')
    {
        SetLedRGB(WHITE);
    }   
}

void ControlServo(void)
{
    uint16_t angle_1 = 0, angle_2 = 0;
    
    angle_1 = (bufferOfDataReceive[startIndex + 2] - '0') * 100 + (bufferOfDataReceive[startIndex + 3] - '0') * 10 + (bufferOfDataReceive[startIndex + 4] - '0');
    angle_2 = (bufferOfDataReceive[startIndex + 6] - '0') * 100 + (bufferOfDataReceive[startIndex + 7] - '0') * 10 + (bufferOfDataReceive[startIndex + 8] - '0');
    
    if (angle_1 >= 360)
        angle_1 = 0;
    if (angle_2 >= 360)
        angle_2 = 0;
    
    servo_angle(SERVO_1, angle_1);
    servo_angle(SERVO_2, angle_2);
}

void ControlLed(void)
{
    if (bufferOfDataReceive[startIndex + 1] == '1')
        Led1On();
    else
        Led1Off();
    
    if (bufferOfDataReceive[startIndex + 2] == '1')
        Led2On();
    else
        Led2Off();
    
    if (bufferOfDataReceive[startIndex + 3] == '1')
        Led3On();
    else
        Led3Off();
    
    if (bufferOfDataReceive[startIndex + 4] == '1')
        Led4On();
    else
        Led4Off();
}
