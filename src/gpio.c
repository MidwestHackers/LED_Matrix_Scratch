#include "gpio.h"

Driver_Status GPIO_Pin_Init (GPIO_Pin_Config *config)
{
    if (!config || 
        !IS_GPIO_PORT(config->port) ||
        !IS_GPIO_PIN(config->pin) ||
        !IS_GPIO_MODE(config->mode) ||
        !IS_GPIO_OTYPE(config->otype) ||
        !IS_GPIO_OSPEED(config->ospeed) ||
        !IS_GPIO_PULL(config->pull) ||
        !IS_GPIO_FUNCTION(config->function))
    {
        return DRIVER_ERROR_INVALID_PARAM;
    }

    if (config->port == GPIO_Port_A)
    {
        config->base = GPIOA;
        GPIOA_ENABLE;
    }
    else if (config->port == GPIO_Port_B)
    {
        config->base = GPIOB;
        GPIOB_ENABLE;
    }
    else if (config->port == GPIO_Port_C)
    {
        config->base = GPIOC;
        GPIOC_ENABLE;
    }
    else if (config->port == GPIO_Port_D)
    {
        config->base = GPIOD;
        GPIOD_ENABLE;
    }
    else if (config->port == GPIO_Port_E)
    {
        config->base = GPIOE;
        GPIOE_ENABLE;
    }
    else if (config->port == GPIO_Port_F)
    {
        config->base = GPIOF;
        GPIOF_ENABLE;
    }
    else if (config->port == GPIO_Port_G)
    {
        config->base = GPIOG;
        GPIOG_ENABLE;
    }

    // Clear all bits in mask, then set according to config
    config->base->MODER &= ~(0x03 << (config->pin * 2));
    config->base->MODER |= ((0x3 & config->mode) << (config->pin * 2));

    config->base->OTYPER &= ~(0x1 << config->pin);
    config->base->OTYPER |= ((0x1 & config->otype) << config->pin);

    config->base->OSPEEDR &= ~(0x3 << (config->pin * 2));
    config->base->OSPEEDR |= ((0x3 & config->ospeed) << (config->pin * 2));

    config->base->PUPDR &= ~(0x3 << (config->pin * 2));
    config->base->PUPDR |= ((0x3 & config->pull) << (config->pin * 2));

    if (config->pin < 8)
    {
        config->base->AFR[0] &= ~(0xF << (config->pin * 4));
        config->base->AFR[0] |= ((0xF & config->function) << (config->pin * 4));
    }
    else
    {
        config->base->AFR[1] &= ~(0xF << (config->pin * 4));
        config->base->AFR[1] |= ((0xF & config->function) << (config->pin * 4));
    }

    return DRIVER_OK;
}

Driver_Status GPIO_Pin_Deinit (GPIO_Pin_Config *config)
{
    if (!config)
    {
        return DRIVER_ERROR_INVALID_PARAM;
    }

    config->base->MODER &= ~(0x3 << (config->pin * 2));
    config->base->OTYPER &= ~(0x1 << config->pin);
    config->base->OSPEEDR &= ~(0x3 << (config->pin * 2));
    config->base->PUPDR &= ~(0x3 << (config->pin * 2));
    if (config->pin < 8)
    {
        config->base->AFR[0] &= ~(0xF << (config->pin * 4));
    }
    else
    {
        config->base->AFR[1] &= ~(0xF << (config->pin * 4));
    }
    
    return DRIVER_OK;
}

Driver_Status GPIO_Pin_Value_Set (GPIO_Pin_Config *config, uint8_t value)
{
    if (!config)
    {
        return DRIVER_ERROR_INVALID_PARAM;
    }

    if (value)
    {
        config->base->ODR |= (1 << config->pin);
    }
    else
    {
        config->base->ODR &= ~(1 << config->pin);
    }

    return DRIVER_OK;
}

Driver_Status GPIO_Pin_Value_Get (GPIO_Pin_Config *config, uint8_t *value)
{
    if (!config)
    {
        return DRIVER_ERROR_INVALID_PARAM;
    }

    if (!value)
    {
        return DRIVER_ERROR_INVALID_PARAM;
    }

    value = config->base->IDR & (1 << config->pin);

    return DRIVER_OK;
}
