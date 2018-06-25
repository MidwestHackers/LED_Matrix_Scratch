#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "driver_common.h"

// Configure system clocking
// HSI -> PLL -> 32MHz SYSCLK
void SystemInit (void);

// Delay for some us using TIM6
// Maximum is 65535us
void delay_us(uint16_t us);

// Delay for some ms using TIM6
// Maximum is 65535ms
void delay_ms(uint16_t ms);

#endif // __SYSTEM_H__
