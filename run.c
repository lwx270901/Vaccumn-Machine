#include "run.h"
#include "timer.h"
#include "adc.h"
#include "motor.h"

int8_t current_speed = 0;

void runforwardline (int speed)
{
	unsigned char temp;
	temp = sensor_value;
    
	switch(temp) 
    {
        case 0x00:// 0000
            break;
        case 0x01:// 0001
            break;
        case 0x02:// 0010
            break;
        case 0x03:// 0011
            break;
        case 0x04:// 0100
            break;
        case 0x05:// 0101
            break;
        case 0x06:// 0110
            SetSpeed (FRONT, speed, speed);
            break;
        case 0x07:// 0117
            break;
        case 0x08:// 1000
            break;
        case 0x09:// 1001
            break;
        case 0x0a:// 1010
            break;
        case 0x0b:// 1011
            break;
        case 0x0c:// 1100
            break;
        case 0x0d:// 1101
            break;
        case 0x0e:// 1110
            break;
        case 0x0f:// 1111
            break;		
		default:
			break;
	}
}

