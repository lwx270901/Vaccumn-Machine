#include "watchdog.h"

void init_watchdog(WATCHDOG_Timeout_t timeout)
{
	uint16_t reload = 0;
	/* LSI 40Khz enable, necessary for IWDG */
	RCC_LSICmd(ENABLE);										
	/* Wait till LSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {}		
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/* Sets IWDG Prescaler value */
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	/* Set counter reload value */
	if (timeout == WATCHDOG_Timeout_1s) {
		reload = 156; /* IWDG_Prescaler_256 */
	} else if (timeout == WATCHDOG_Timeout_2s) {
		reload = 312; /* IWDG_Prescaler_256 */
	} else if (timeout == WATCHDOG_Timeout_4s) {
		reload = 625; /* IWDG_Prescaler_256 */
	} else if (timeout == WATCHDOG_Timeout_8s) {
		reload = 1250; /* IWDG_Prescaler_256 */
	} else if (timeout == WATCHDOG_Timeout_16s) {
		reload = 2500; /* IWDG_Prescaler_256 */
	}
	/* Sets IWDG Reload value */
	IWDG_SetReload(reload);
}

void EnableWatchdogTimer(void)
{
    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}

void WatchdogTimerReload(void)
{
    /* Reload IWDG counter */
    IWDG_ReloadCounter();  
}
