/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
//#include "driver/rmt_tx.h"
//#include "led_strip_encoder.h"
#include "ua_scars_model.h"
#include <led_strip.h>
#include <led_strip_interface.h>
#include "esp_random.h"

static const char *TAG = "ua-scars";

static led_strip_handle_t led_strip;

const segment_t s0 = { .length = 9, .leds = { 0, 1, 2, 3, 4, 5, 6, 7, 8 } };
const segment_t s1 = { .length = 4, .leds = { 9, 10, 11, 12 } };
const segment_t s2 = { .length = 13, .leds = { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 } };
const segment_t s3 = { .length = 8, .leds = { 26, 27, 28, 29, 30, 31, 32, 33 } };
const segment_t s4 = { .length = 3, .leds = { 34, 35, 36 } };
const segment_t s5 = { .length = 6, .leds = { 37, 38, 39, 40, 41, 42 } };
const segment_t s6 = { .length = 3, .leds = { 43, 44, 45 } };
const segment_t s7 = { .length = 11, .leds = { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 } };
const segment_t s8 = { .length = 12, .leds = { 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 } };
const segment_t s9 = { .length = 2, .leds = { 69, 70 } };
const segment_t s10 = { .length = 6, .leds = { 71, 72, 73, 74, 75, 76 } };
const segment_t s11 = { .length = 3, .leds = { 77, 78, 79 } };
const segment_t s12 = { .length = 8, .leds = { 80, 81, 82, 83, 84, 85, 86, 87 } };
const segment_t s13 = { .length = 13, .leds = { 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 } };
const segment_t s14 = { .length = 4, .leds = { 101, 102, 103, 104 } };
const segment_t s15 = { .length = 8, .leds = { 105, 106, 107, 108, 109, 110, 111, 112 } };


void init(void) 
{
    /// LED strip common configuration
    led_strip_config_t strip_config = {
        .strip_gpio_num = RMT_LED_STRIP_GPIO_NUM,  // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_COUNT,                 // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812, // LED strip model, it determines the bit timing
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    /// RMT backend specific configuration
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,    // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency: 10MHz
        .mem_block_symbols = 64,           // the memory size of each RMT channel, in words (4 bytes)
        .flags = {
            .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
        }
    };

    /// Create the LED strip object
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
}

void light_pixel_rgb(uint32_t pixel_index, uint8_t red, uint8_t green, uint8_t blue)
{
    led_strip_set_pixel(led_strip, pixel_index, red, green, blue);
    led_strip_refresh(led_strip);
}

void light_pixel(uint32_t pixel_index, uint8_t hue, uint8_t saturation, uint8_t value)
{
    led_strip_set_pixel_hsv(led_strip, pixel_index, hue, saturation, value);    
    led_strip_refresh(led_strip);
}

void light_segment(const segment_t *segment, uint8_t hue, uint8_t saturation, uint8_t value)
{
    for (int i = 0; i < segment->length; i++) {
        led_strip_set_pixel_hsv(led_strip, segment->leds[i], hue, saturation, value);
    }
    led_strip_refresh(led_strip);
}

void app_main(void)
{
    uint16_t current_color = 0;
    uint16_t staring_color = 0;
    //uint8_t current_segment = 0;

    init();    

    ESP_LOGI(TAG, "Start LED show");    

    //const segment_t* all_segments[] = { &s0, &s1, &s2, &s3 };        //, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11, &s12, &s13, &s14, &s15 };
    
    led_strip_clear(led_strip);

    // Power consumption test - turn on all LEDs to white
    // light_pixel_rgb(0, 255, 0, 0); // red
    // for (int i = 0; i < LED_STRIP_COUNT; i++) {
    //     led_strip_set_pixel(led_strip, i, 255, 255, 255);
    // }    
    // led_strip_refresh(led_strip);

    while (1) {
        
        // Initial light up rainbow train
        for (int i = 0; i < LED_STRIP_COUNT; i++) {
            current_color += 1;
            if (current_color >= 360) {
                current_color = 0;
            }
            led_strip_set_pixel_hsv(led_strip, i, current_color, 255, 255);
        }
        led_strip_refresh(led_strip);

        staring_color ++;
        if (staring_color >= 360) {
            staring_color = 0;
        }
        current_color = staring_color;

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
