#include "led.h"
#include "config.h"
#include "driver/gpio.h"

void led_init(void)
{
	gpio_config_t io_conf = {
		.mode = GPIO_MODE_OUTPUT,
		.pin_bit_mask = 
			(1ULL << LED_RED_GPIO) |
			(1ULL << LED_YELLOW_GPIO) |
			(1ULL << LED_GREEN_GPIO),
	};

	gpio_config(&io_conf);

	led_all_off();
}

void led_all_off(void) {
	gpio_set_level(LED_RED_GPIO, 0);
	gpio_set_level(LED_YELLOW_GPIO, 0);
	gpio_set_level(LED_GREEN_GPIO, 0);
}

void led_set_red(void) {
	led_all_off();
	gpio_set_level(LED_RED_GPIO, 1);
}

void led_set_green(void) {
	led_all_off();
	gpio_set_level(LED_GREEN_GPIO, 1);
}

void led_set_yellow(void) {
	led_all_off();
	gpio_set_level(LED_YELLOW_GPIO, 1);
}
