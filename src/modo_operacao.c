#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "dht11.h"
#include "wcmcu-h2.h"
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

#define HALL 4

void energia()
{

  config_pwm();

   xTaskCreate(&init_dht11, "Temperatura_Umidade", 2048, NULL, 1, NULL);
   xTaskCreate(&init_wcmcu_h2,"RGB",2048,NULL,10,NULL);
   //xTaskCreate(&read_touch_sensor, "Touch", 2048, NULL, 1, NULL);
   //xTaskCreate(&read_hall_magnetic_sensor, "Hall_Sensor_Task", 2048, NULL, 10, NULL);
   //xTaskCreate(read_sound_sensor, "Voice_Sensor", 2048, NULL, 10, NULL);
   //xTaskCreate(read_flame_sensor, "Flame_Sensor", 2048, NULL, 10, NULL);
   //xTaskCreate(read_reed_switch, "Reed_Switch", 2048, NULL, 10, NULL);
}

void bateria()
{
  char mensagem[50];

  // Configuração da GPIO para o botão de entrada
  pinMode(HALL, GPIO_INPUT_PULLUP);

  gpio_wakeup_enable(HALL, GPIO_INTR_HIGH_LEVEL);
  esp_sleep_enable_gpio_wakeup();

  while (true)
  {
    ESP_LOGI("ModoLight", "Modo Light Sleep...");
    esp_light_sleep_start();
    // Configura o modo sleep somente após completar a escrita na UART para finalizar o printf
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

    int state = digitalRead(HALL); // lê o estado do pino

    esp_sleep_wakeup_cause_t causa = esp_sleep_get_wakeup_cause();
    if (causa == ESP_SLEEP_WAKEUP_GPIO)
    {
      printf("\nO sensor despertou!\n");
      printf("Touch: %d\n", state);
      sprintf(mensagem, "{\"Touch\": %d}", state);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
      grava_valor_nvs("Touch", state);
      causa = ESP_SLEEP_WAKEUP_TIMER;
      printf("Mensagem enviada!\n\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS); // aguarde por 1 segundo
    }
    
  }
}
