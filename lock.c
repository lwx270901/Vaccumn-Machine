#include "lock.h"

/* Define the STM32F10x FLASH Page Size depending on the used device */
/* Refer stm32f10x_flash.h*/
#define FLASH_PAGES_TO_BE_PROTECTED     ((uint32_t)0xffffffff)      //Page 0 to page 127


void LockChip(void)
{
	FLASH_Unlock();
     
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

    FLASH_ReadOutProtection(ENABLE);
    
    FLASH_EnableWriteProtection(FLASH_PAGES_TO_BE_PROTECTED);
    
    FLASH_Lock();
}
