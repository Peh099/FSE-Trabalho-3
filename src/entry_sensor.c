#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp32/rom/ets_sys.h"
#include "nvs_handler.h"

#include "entry_sensor.h"

static gpio_num_t SENSOR_PIN = GPIO_NUM_15;


int peopleCount = 0; // Variável para contar o número de pessoas
bool sensorState = false; // Estado atual do sensor
bool lastSensorState = false; // Estado anterior do sensor

void IRAM_ATTR sensorInterruptHandler(void *arg) {
    sensorState = gpio_get_level(SENSOR_PIN); // Obtém o estado atual do pino do sensor
    
    if (sensorState && !lastSensorState) {
        peopleCount++; // Incrementa o contador quando o sensor detectar que o obstáculo foi removido
    }
    
    lastSensorState = sensorState; // Atualiza o estado anterior do sensor
}

void init_entry_sensor() {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = (1ULL << SENSOR_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(SENSOR_PIN, sensorInterruptHandler, (void *)SENSOR_PIN);

    printf("Contador de pessoas iniciado.\n");

    while (1) {
        printf("Número de pessoas: %d\n", peopleCount);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Atualiza a exibição a cada segundo
    }
}