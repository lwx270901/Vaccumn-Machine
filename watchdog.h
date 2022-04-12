#ifndef __WATCHDOG_H_
#define __WATCHDOG_H_

#include "stm32f10x.h"

typedef enum {
	WATCHDOG_Timeout_1s = 0x00,    /*!< System reset called every 1s */
	WATCHDOG_Timeout_2s = 0x01,    /*!< System reset called every 2s */
	WATCHDOG_Timeout_4s = 0x02,    /*!< System reset called every 4s */
	WATCHDOG_Timeout_8s = 0x03,    /*!< System reset called every 8s */
	WATCHDOG_Timeout_16s = 0x04,   /*!< System reset called every 16s */
} WATCHDOG_Timeout_t;

void init_watchdog(WATCHDOG_Timeout_t timeout);
void EnableWatchdogTimer(void);
void WatchdogTimerReload(void);

#endif
