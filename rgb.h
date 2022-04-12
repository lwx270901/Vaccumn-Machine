#ifndef __RGB_H_
#define __RGB_H_

#include "stm32f10x.h"

#define RED         0
#define GREEN       1
#define BLUE        2
#define YELLOW      3
#define CYAN        4    
#define MAGENTA     5
#define WHITE       6

void SetLedRGB(uint16_t color);

#endif
