#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON GPIO_NUM_4
#define LED    GPIO_NUM_1

typedef enum {
    MODE_OFF = 0,
    MODE_ON,
    MODE_BLINK
} mode_t;

static mode_t mode = MODE_OFF;

void app_main(void)
{
    // GPIO config
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << BUTTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io);

    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    int last_button_state = 1;

    while (1) {
        int current = gpio_get_level(BUTTON);

        // detect press (HIGH -> LOW)
        if (last_button_state == 1 && current == 0) {
            vTaskDelay(pdMS_TO_TICKS(30)); // debounce

            if (gpio_get_level(BUTTON) == 0) {
                mode = (mode + 1) % 3;
                printf("Mode changed: %d\n", mode);
            }
        }

        last_button_state = current;

        // control LED
        if (mode == MODE_OFF) {
            gpio_set_level(LED, 0);
        }
        else if (mode == MODE_ON) {
            gpio_set_level(LED, 1);
        }
        else if (mode == MODE_BLINK) {
            gpio_set_level(LED, 1);
            vTaskDelay(pdMS_TO_TICKS(200));
            gpio_set_level(LED, 0);
            vTaskDelay(pdMS_TO_TICKS(200));
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
