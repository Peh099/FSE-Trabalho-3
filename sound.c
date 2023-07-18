#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "gpio_setup.h"

#define SOUND_SENSOR_PIN GPIO_NUM_16

void configSoundSensor() {
    pinMode(SOUND_SENSOR_PIN, GPIO_INPUT);
}

int readSoundSensor() {
    return digitalRead(SOUND_SENSOR_PIN);
}

void init_sound():
    while (true) {
            int soundState = readSoundSensor();
            if (soundState == 1) {
                printf("%s\n", "Som detectado!");
            }
        vTaskDelay(pdMS_TO_TICKS(100));
    }