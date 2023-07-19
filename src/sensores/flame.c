#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "gpio_setup.h"
#include "nvs_handler.h"
#include "mqtt.h"

#define FLAME_SENSOR_PIN GPIO_NUM_23

void configFlameSensor() {
    pinMode(FLAME_SENSOR_PIN, GPIO_INPUT);
}

int readFlameSensor() {
    return digitalRead(FLAME_SENSOR_PIN);
}

void init_flame(){
    char mensagem[50];
    while (true) {
        // Leitura do sensor de som
        int flames = readFlameSensor();
        if (flames == 1) {
            printf("%s\n", "Fogo detectado!");
        }
        sprintf(mensagem, "{\"FlameSensor\": %d}", flames);
        mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
        grava_valor_nvs("FlameSensor", flames);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}