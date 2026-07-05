#include "servo.h"
#include "config.h"

#include "driver/ledc.h"
#include "esp_err.h"

#define SERVO_FREQ          50
#define SERVO_RESOLUTION    LEDC_TIMER_14_BIT

#define SERVO_MIN_DUTY      410
#define SERVO_MAX_DUTY      2048

static void servo_set_duty(uint32_t duty);

void servo_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = SERVO_RESOLUTION,
        .freq_hz = SERVO_FREQ,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t channel = {
        .gpio_num = SERVO_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0,
    };

    ESP_ERROR_CHECK(ledc_channel_config(&channel));

    servo_lock();
}

static void servo_set_duty(uint32_t duty)
{
    ESP_ERROR_CHECK(
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            LEDC_CHANNEL_0,
            duty));

    ESP_ERROR_CHECK(
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            LEDC_CHANNEL_0));
}

void servo_lock(void)
{
    servo_set_duty(SERVO_MIN_DUTY);
}

void servo_unlock(void)
{
    servo_set_duty((SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2);
}
