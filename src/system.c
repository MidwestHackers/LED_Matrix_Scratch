#include "system.h"
#include "gpio.h"

#if defined (MCO_OUTPUT)
GPIO_Pin_Config mco_config = {
    .port = GPIO_Port_A,
    .pin = 8,
    .mode = GPIO_Mode_Alternate,
    .otype = GPIO_OType_PP,
    .pull = GPIO_Pull_None,
};
#endif // MCO_OUTPUT

void SystemInit (void)
{
    // Vector table offset
    SCB->VTOR = FLASH_BASE;

    // Increase flash latency from 0 WS to 1 WS
    FLASH->ACR |= FLASH_ACR_ACC64;
    while (! (FLASH->ACR & FLASH_ACR_ACC64));
    FLASH->ACR |= FLASH_ACR_LATENCY;
    while (! (FLASH->ACR & FLASH_ACR_LATENCY));
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    while (! (FLASH->ACR & FLASH_ACR_PRFTEN));

    // Enable HSI clock (16MHz)
    RCC->CR |= RCC_CR_HSION;
    // Wait for HSI ready
    while (! (RCC->CR & RCC_CR_HSIRDY));

    // Disable PLL
    RCC->CR &= ~RCC_CR_PLLON;

    // PLL multiplier to 6 (PLLVCO = 96MHz)
    RCC->CFGR &= ~RCC_CFGR_PLLMUL;
    RCC->CFGR |= RCC_CFGR_PLLMUL6;

    // PLL divider to 3 (SYSCLK = 32MHz)
    RCC->CFGR &= ~RCC_CFGR_PLLDIV;
    RCC->CFGR |= RCC_CFGR_PLLDIV3;

    // Set HSI as PLL source
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSI;

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    // Wait for PLL ready
    while (! (RCC->CR & RCC_CR_PLLRDY));

    // Switch to PLL as SYSCLK source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    // Wait for system to switch to PLL source
    while (! (RCC->CFGR & RCC_CFGR_SWS_PLL));

    // Disable MSI clock
    RCC->CR &= ~RCC_CR_MSION;

#if defined (MCO_OUTPUT)
    // Enable MCO output (SYSCLK / 8 = 4MHz)
    GPIO_Pin_Init(&mco_config);
    RCC->CFGR &= ~RCC_CFGR_MCOPRE;
    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV8;
    RCC->CFGR &= ~RCC_CFGR_MCOSEL;
    RCC->CFGR |= RCC_CFGR_MCOSEL_SYSCLK;
#endif // MCO_OUTPUT
}
