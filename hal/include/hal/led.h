// Sample button module
// Part of the Hardware Abstraction Layer (HAL)

#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>

// Paths to LED brightness
static const char* LED_PATHS_BRIGHTNESS[] = {
    "/sys/class/leds/beaglebone:green:usr0/brightness",
    "/sys/class/leds/beaglebone:green:usr1/brightness",
    "/sys/class/leds/beaglebone:green:usr2/brightness",
    "/sys/class/leds/beaglebone:green:usr3/brightness"};

void led_init(void);
void led_cleanup(void);
void bbgSetTrigger(const char* fileName, char* value);
void bbgLedBright(const char* fileName, char* value);

#endif