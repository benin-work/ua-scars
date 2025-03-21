#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RMT_LED_STRIP_GPIO_NUM 8
#define LED_STRIP_COUNT 300

/**
 * @brief
 */
typedef struct {
    uint8_t length;
    uint8_t leds[];
} segment_t;


#ifdef __cplusplus
}
#endif
