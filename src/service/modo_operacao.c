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

void energia()
{

  config_pwm();

   xTaskCreate(&init_dht11, "Temperatura_Umidade", 2048, NULL, 1, NULL);
   xTaskCreate(&init_wcmcu_h2,"RGB",2048,NULL,10,NULL);
   xTaskCreate(&init_buzzer, "Buzzer", 3072, NULL, 1, NULL);
   xTaskCreate(&init_entry_sensor, "Sensor de entrada", 2048, NULL, 10, NULL);
   xTaskCreate(&init_sound, "Voice_Sensor", 2048, NULL, 10, NULL);
   xTaskCreate(&init_flame, "Flame_Sensor", 2048, NULL, 10, NULL);
}

void bateria()
{
  xTaskCreate(&modo_bateria,"Modo_Bateria",2048,NULL,1,NULL);
}

