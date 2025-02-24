#ifndef LED_CNTRL_H
#define LED_CNTRL_H

#include "driver/ledc.h"
#include "hal/ledc_types.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_OUT GPIO_NUM_32
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_FREQ 4000
#define LEDC_RES LEDC_TIMER_8_BIT

void fade_start(void);
void ledc_main(void *arg);

#endif //LED_CNTRL_H
