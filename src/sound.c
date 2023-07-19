#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "gpio_setup.h"
#include "nvs_handler.h"
#include "mqtt.h"

#define SOUND_SENSOR_PIN GPIO_NUM_5

void configSoundSensor() {
    pinMode(SOUND_SENSOR_PIN, GPIO_INPUT);
}

int readSoundSensor() {
    return digitalRead(SOUND_SENSOR_PIN);
}

void init_sound(){
    char mensagem[50];
    while (true) {
        int soundState = readSoundSensor();
        if (soundState == 1) {
            printf("%s\n", "Som detectado!");
        }
        sprintf(mensagem, "{\"SongSensor\": %d}", soundState);
        mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
        grava_valor_nvs("SongSensor", soundState);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}