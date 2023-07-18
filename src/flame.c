#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "gpio_setup.h"

#define FLAME_SENSOR_PIN GPIO_NUM_23

void configFlameSensor() {
    pinMode(FLAME_SENSOR_PIN, GPIO_INPUT);
}

int readFlameSensor() {
    return digitalRead(FLAME_SENSOR_PIN);
}


void init_flame(){
    while (true) {
            // Leitura do sensor de som
            int flames = readFlameSensor();
            if (flames == 1) {
               printf("%s\n", "Fogo detectado!");
            }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}