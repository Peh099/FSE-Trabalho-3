#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include <stdbool.h>
#include <esp_log.h>
#include "esp32/rom/ets_sys.h"
#include "nvs_handler.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "nvs_handler.h"
#include "mqtt.h"

#include "entry_sensor.h"

static gpio_num_t SENSOR_PIN = GPIO_NUM_16;

void initialize_gpio()
{
    esp_rom_gpio_pad_select_gpio(SENSOR_PIN);
    gpio_set_direction(SENSOR_PIN, GPIO_MODE_INPUT);
}

void init_entry_sensor(void *arg)
{
    char mensagem[50];
    initialize_gpio();

    while (1)
    {
        int obstacle_sensor=gpio_get_level(SENSOR_PIN);
        if (obstacle_sensor==1)
        {
            printf("Bebida ausente no balcão\n");
            obstacle_sensor=0;
        }
        else
        {
            printf("Bebida presente no balcão\n");
            obstacle_sensor=1;
        }
        sprintf(mensagem, "{\"ObstacleSensor\": %d}", obstacle_sensor);
        mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
        grava_valor_nvs("ObstacleSensor", obstacle_sensor);


        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay de 1 segundo
    }
}