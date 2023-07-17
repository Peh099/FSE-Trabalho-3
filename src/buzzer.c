#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp32/rom/ets_sys.h"
#include "nvs_handler.h"

#include "buzzer.h"


static gpio_num_t BUZZER_PIN = GPIO_NUM_15;

void buzzerTone(int frequency, int duration) {
    int halfPeriod = 1000000 / frequency / 2; // Calcula o tempo da metade do período em microssegundos
    int cycles = frequency * duration / 1000; // Calcula o número de ciclos
    printf("a\n");
    for (int i = 0; i < cycles; i++) {
        printf("b\n");
        gpio_set_level(BUZZER_PIN, 1); // Ligue o buzzer
        ets_delay_us(halfPeriod); // Aguarde metade do período
        gpio_set_level(BUZZER_PIN, 0); // Desligue o buzzer
        ets_delay_us(halfPeriod); // Aguarde metade do período
    }
}

void init_buzzer() {
    esp_rom_gpio_pad_select_gpio(BUZZER_PIN);
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(BUZZER_PIN, 0);
    // Toca uma música simples
    // parabens int melody[] = { 262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392, 349, 262, 262, 523, 440, 349, 330, 294, 466, 466, 440, 349, 392, 349 };
    //  mario 
    int melody[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
    int duration[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};

    // interestelar int melody[] = {
    //     330, 392, 523, 659, 784, 523, 659, 784, 392, 494, 587, 698, 587, 494, 392, 330, 587, 698, 880, 698,
    //     587, 494, 392, 330, 392, 523, 659, 784, 523, 659, 784, 392, 494, 587, 698, 587, 494, 392, 330
    // };
    //int duration = 300;
    // int duration[] = {
    //     500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500, 500,
    //     1000, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 500,
    //     500, 1000, 500, 500, 500, 1000
    // };
    int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
    // got int melody[] = {
    //     330, 392, 440, 494, 523, 587, 659, 523, 587, 659, 698, 784, 880, 988, 880, 784, 698, 659, 587, 523,
    //     494, 440, 392, 330
    // };
    // int duration[] = {
    //     400, 400, 400, 400, 400, 400, 800, 400, 400, 800, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
    //     400, 400, 400, 800
    // };
    while(1){
        printf("musica\n");
        for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
            buzzerTone(melody[i], duration[i]);
            printf("g\n");
            vTaskDelay(pausadepoisdasnotas[i] / portTICK_PERIOD_MS); // Aguarde um curto intervalo entre as notas
        }
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
