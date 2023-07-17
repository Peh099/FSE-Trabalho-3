#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <inttypes.h>
#include "sdkconfig.h"
#include "esp_chip_info.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "wcmcu-h2.h"

#define TAG "COLORS"

void led_rgb_init()
{
    // Configuração do Timer
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_1,
        .freq_hz = 200,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    // Configuração do Canal
    ledc_channel_config_t channel_config_blue = {
        .gpio_num = LEDBLUE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config_blue));

    // Configuração do Canal
    ledc_channel_config_t channel_config_green = {
        .gpio_num = LEDGREEN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config_green));

    // Configuração do Canal
    ledc_channel_config_t channel_config_red = {
        .gpio_num = LEDRED,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config_red));

    //    ledc_fade_func_install(0);
}

void led_rgb_set_mode(int duty)
{

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}


bool led_on = false; // Variável global para representar o estado do LED (inicialmente ligado).

void set_true(){
    printf("Ligando led!");
    led_on = true;
}

void set_false(){
    printf("Desligando led!");
    led_on = false;
}


void init_wcmcu_h2(void *params)
{
    led_rgb_init();
    
    while (true)
    {
        if (led_on)
        {
            for (int i = 0; i < 255; i++)
            {
                led_rgb_set_mode(i);
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            for (int i = 255; i > 0; i--)
            {
                led_rgb_set_mode(i);
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }
        else
        {
            // Mantém o LED desligado (duty cycle em 0).
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
        }

        // Introduce a small delay (e.g., 100 ms) to allow other tasks to run.
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}