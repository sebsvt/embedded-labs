#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON GPIO_NUM_4
#define LED    GPIO_NUM_1

static volatile int led_state = 0;

// interrupt handler
static void IRAM_ATTR button_isr_handler(void* arg)
{
    led_state = !led_state;
    gpio_set_level(LED, led_state);
}

void app_main(void)
{
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    gpio_config_t io = {
        .pin_bit_mask = (1ULL << BUTTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE   // กด = falling edge
    };
    gpio_config(&io);

    gpio_install_isr_service(0);

    gpio_isr_handler_add(BUTTON, button_isr_handler, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
