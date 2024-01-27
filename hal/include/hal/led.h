// Sample button module
// Part of the Hardware Abstraction Layer (HAL)

#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>

void led_init(void);
void led_cleanup(void);
void bbgSetTrigger(const char* fileName, char* value);
void bbgLedBright(const char* fileName, char* value);

#endif