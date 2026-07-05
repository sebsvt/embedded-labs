#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led.h"
#include "button.h"
#include "servo.h"

void app_main(void) {
	led_init();
	button_init();
	servo_init();

	while (1) {
		if (button_is_pressed()) {
			led_set_yellow();
			vTaskDelay(pdMS_TO_TICKS(5000));

			// Open
			servo_unlock();
			led_set_green();
			vTaskDelay(pdMS_TO_TICKS(10000));

			// Close
			servo_lock();
			led_set_red();

		}
		else {
			led_set_red();
		}
		vTaskDelay(pdMS_TO_TICKS(20));
	}
}
