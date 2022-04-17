/*
    We should only be using ADC1 instead of ADC2 due to hardware priotities.

    For ADC1 Channels, the mapping goes as following:
    +----------------+----------+
    |  ADC1 Channel  | GPIO PIN |
    +----------------+----------+
    | ADC1_CHANNEL_0 | GPIO36   |
    | ADC1_CHANNEL_1 | GPIO37   |
    | ADC1_CHANNEL_2 | GPIO38   |
    | ADC1_CHANNEL_3 | GPIO39   |
    | ADC1_CHANNEL_4 | GPIO32   |
    | ADC1_CHANNEL_5 | GPIO33   |
    | ADC1_CHANNEL_6 | GPIO34   |
    | ADC1_CHANNEL_7 | GPIO35   |
    +----------------+----------+
 */

#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static esp_adc_cal_characteristics_t adc1_chars;

static const char *TAG = "ADC1";
int tpot = 473; // Resistance of the trim pot, 473 means 47k3 ohm resistances. Used to calculate mV


void app_main(void)
{
    uint32_t voltage;

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11));

    while (1) 
    {
        voltage = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_6), &adc1_chars);
        ESP_LOGI(TAG, "ADC1_CHANNEL_6: %d mV", (voltage + tpot));
        vTaskDelay(pdMS_TO_TICKS(100));

    }
}