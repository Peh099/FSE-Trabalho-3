#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "temp_hum.h"
#include "buzzer.h"
#include "entry_sensor.h"
#include "flame.h"
#include "sound.h"
#include "rgb.h"
#include "pwm.h"
#include "esp_sleep.h"
#include "esp32/rom/uart.h"
#include <time.h>
#include "driver/rtc_io.h"
#include <stdlib.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_oneshot.h"
#include "gpio_setup.h"
#include "nvs_handler.h"
#include "mqtt.h"
#include "wifi.h"
#include "modoBateria.h"

#define ENTRY 16

void modo_bateria(){

    char mensagem[50];

    // Configuração da GPIO para o botão de entrada
    pinMode(ENTRY, GPIO_INPUT_PULLUP);

    gpio_wakeup_enable(ENTRY, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();

    while (true)
    {
        ESP_LOGI("ModoLight", "Modo Light Sleep...");
        esp_light_sleep_start();
        // Configura o modo sleep somente após completar a escrita na UART para finalizar o printf
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

        int state = digitalRead(ENTRY); // lê o estado do pino

        esp_sleep_wakeup_cause_t causa = esp_sleep_get_wakeup_cause();
        if (causa == ESP_SLEEP_WAKEUP_GPIO)
        {
            printf("\nO sensor despertou!\n");
            printf("ENTRY: %d\n", state);
            sprintf(mensagem, "{\"Entry\": %d}", state);
            mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
            grava_valor_nvs("Entry", state);
            printf("Mensagem enviada!\n\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS); // aguarde por 1 segundo
            causa = ESP_SLEEP_WAKEUP_TIMER;
        }
    }
}