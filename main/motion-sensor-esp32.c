#include <esp_attr.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "led_cntrl.h"

#define SENSOR_PIN GPIO_NUM_34
#define LED_PIN GPIO_NUM_32
#define MOTION_DETECTED BIT0

static EventGroupHandle_t motion_event_group;

static void IRAM_ATTR motion_sensor_isr_handler(void *arg) {
    xEventGroupSetBits(motion_event_group, MOTION_DETECTED);
}

static void s_sensor_gpio_config(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SENSOR_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en =  GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);

    motion_event_group = xEventGroupCreate();

    gpio_set_intr_type(SENSOR_PIN, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(SENSOR_PIN, motion_sensor_isr_handler, NULL);
}

void motion_sensor_task(void *arg) {
    s_sensor_gpio_config();

    while (1) {
        xEventGroupWaitBits(motion_event_group, MOTION_DETECTED, pdTRUE, pdFALSE, portMAX_DELAY);
        ESP_LOGI("main", "Motion detected!");
        fade_start();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
