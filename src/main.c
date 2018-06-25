#include "platforms.h"

int main (void)
{
    int k = 0;

    GPIO_Pin_Config led1_config = {
        .port = LED1_GPIO_PORT,
        .pin = LED1_GPIO_PIN,
        .mode = GPIO_Mode_Output,
        .otype = GPIO_OType_PP,
        .pull = GPIO_Pull_Down,
    };

    GPIO_Pin_Init(&led1_config);
    while (1)
    {
        GPIO_Pin_Value_Set(&led1_config, 1);
        for (int i = 0; i < 200000; i++)
        {
            k = i;
        }
        GPIO_Pin_Value_Set(&led1_config, 0);
        for (int i = 0; i < 200000; i++)
        {
            k = i;
        }
    }
}
