#include "led_cntrl.h"
#include "motion-sensor-esp32.h"


void app_main(void) {
    ledc_main(NULL);
    xTaskCreatePinnedToCore(motion_sensor_task, "motion_sensor_task", 2048, NULL, 2, NULL, 1);
}
