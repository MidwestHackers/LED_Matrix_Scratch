#include "platforms.h"
#include "system.h"

GPIO_Pin_Config led1_config = {
    .port = LED1_GPIO_PORT,
    .pin = LED1_GPIO_PIN,
    .mode = GPIO_Mode_Output,
    .otype = GPIO_OType_PP,
    .pull = GPIO_Pull_Down,
};

int main (void)
{
    GPIO_Pin_Init(&led1_config);
    while (1)
    {
        GPIO_Pin_Value_Set(&led1_config, 1);
        delay_ms(250);
        GPIO_Pin_Value_Set(&led1_config, 0);
        delay_ms(250);
    }
}
