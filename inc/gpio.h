#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32l151xe.h"
#include "driver_common.h"

// Macros
#define IS_GPIO_PORT(PORT)  ((PORT == GPIO_Port_A) || \
                             (PORT == GPIO_Port_B) || \
                             (PORT == GPIO_Port_C) || \
                             (PORT == GPIO_Port_D) || \
                             (PORT == GPIO_Port_E) || \
                             (PORT == GPIO_Port_F) || \
                             (PORT == GPIO_Port_G))
#define IS_GPIO_PIN(PIN)    ((PIN >= 0) && \
                             (PIN <= 15))
#define IS_GPIO_MODE(MODE)  ((MODE == GPIO_Mode_Input) || \
                             (MODE == GPIO_Mode_Output) || \
                             (MODE == GPIO_Mode_Alternate) || \
                             (MODE == GPIO_Mode_Analog))
#define IS_GPIO_OTYPE(OTYPE)    ((OTYPE == GPIO_OType_PP) || \
                                 (OTYPE == GPIO_OType_OD))
#define IS_GPIO_OSPEED(OSPEED)  ((OSPEED == GPIO_OSpeed_Low) || \
                                 (OSPEED == GPIO_OSpeed_Medium) || \
                                 (OSPEED == GPIO_OSpeed_High) || \
                                 (OSPEED == GPIO_OSpeed_Very_High))
#define IS_GPIO_PULL(PULL)  ((PULL == GPIO_Pull_None) || \
                             (PULL == GPIO_Pull_Up) || \
                             (PULL == GPIO_Pull_Down))
#define IS_GPIO_FUNCTION(FUNCTION)  ((FUNCTION >= 0) && \
                                     (FUNCTION <= 15))

#define GPIOA_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOAEN_Msk << RCC_AHBENR_GPIOAEN_Pos))
#define GPIOB_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOBEN_Msk << RCC_AHBENR_GPIOBEN_Pos))
#define GPIOC_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOCEN_Msk << RCC_AHBENR_GPIOCEN_Pos))
#define GPIOD_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIODEN_Msk << RCC_AHBENR_GPIODEN_Pos))
#define GPIOE_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOEEN_Msk << RCC_AHBENR_GPIOEEN_Pos))
#define GPIOF_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOFEN_Msk << RCC_AHBENR_GPIOFEN_Pos))
#define GPIOG_ENABLE (RCC->AHBENR |= (RCC_AHBENR_GPIOGEN_Msk << RCC_AHBENR_GPIOGEN_Pos))

// Types
typedef enum
{
    GPIO_Port_A = 0x0,
    GPIO_Port_B,
    GPIO_Port_C,
    GPIO_Port_D,
    GPIO_Port_E,
    GPIO_Port_F,
    GPIO_Port_G,
} GPIO_Port;

typedef enum
{
    GPIO_Mode_Input = 0x0,
    GPIO_Mode_Output,
    GPIO_Mode_Alternate,
    GPIO_Mode_Analog,
} GPIO_Mode;

typedef enum
{
    GPIO_OType_PP = 0x0,
    GPIO_OType_OD,
} GPIO_OType;

typedef enum
{
    GPIO_OSpeed_Low = 0x0,
    GPIO_OSpeed_Medium,
    GPIO_OSpeed_High,
    GPIO_OSpeed_Very_High,
} GPIO_OSpeed;

typedef enum
{
    GPIO_Pull_None = 0x0,
    GPIO_Pull_Up,
    GPIO_Pull_Down,
} GPIO_Pull;

typedef struct
{
    uint8_t port;       // GPIO Port (GPIO_Port_A - GPIO_Port_G)
    uint8_t pin;        // GPIO Pin (1 - 15)
    uint8_t mode;       // Pin Mode (Input, Output, Alternate, Analog)
    uint8_t otype;      // Pin Output Type (Push-Pull, Open-Drain)
    uint8_t ospeed;     // Pin Output Speed (Slow, Medium, High, Very High)
    uint8_t pull;       // Pin Pull Direction (None, Up, Down)
    uint8_t function;   // Pin alternate function - valid only in Alternate mode
    GPIO_TypeDef *base; // Configured by driver during initialization
} GPIO_Pin_Config;

// Functions
Driver_Status GPIO_Pin_Init (GPIO_Pin_Config *config);
Driver_Status GPIO_Pin_Deinit (GPIO_Pin_Config *config);
Driver_Status GPIO_Pin_Value_Set (GPIO_Pin_Config *config, uint8_t value);
Driver_Status GPIO_Pin_Value_Get (GPIO_Pin_Config *config, uint8_t *value);

#endif // __GPIO_H__
