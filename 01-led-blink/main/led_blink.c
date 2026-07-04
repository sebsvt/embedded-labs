#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>

#define LED_GPIO GPIO_NUM_8

void app_main(void)
{
    printf("Blink start!\n");

    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        printf("ON\n");
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(100));

        printf("OFF\n");
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
