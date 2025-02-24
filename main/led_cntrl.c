#include "led_cntrl.h"

void fade_start(void) {
    ledc_set_fade_with_time(LEDC_MODE, LEDC_CHANNEL, 256, 2000);
    ledc_fade_start(LEDC_MODE, LEDC_CHANNEL, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(LEDC_MODE, LEDC_CHANNEL, 0, 2000);
    ledc_fade_start(LEDC_MODE, LEDC_CHANNEL, LEDC_FADE_NO_WAIT);
}

static void s_ledc_init(void) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQ,
        .clk_cfg = LEDC_USE_RC_FAST_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_cfg = {
        .gpio_num = LEDC_OUT,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_FADE_END,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_cfg));
}

void ledc_main(void *arg) {
    s_ledc_init();

    ledc_fade_func_install(0);

    ESP_LOGI("ledc", "LEDC configured!");
    vTaskDelay(pdMS_TO_TICKS(100));
}
