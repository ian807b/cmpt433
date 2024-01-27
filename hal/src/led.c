#include "hal/led.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// #define LED0_PATH_TRIGGER "/sys/class/leds/beaglebone:green:usr0/trigger"
// #define LED1_PATH_TRIGGER "/sys/class/leds/beaglebone:green:usr1/trigger"
// #define LED2_PATH_TRIGGER "/sys/class/leds/beaglebone:green:usr2/trigger"
// #define LED3_PATH_TRIGGER "/sys/class/leds/beaglebone:green:usr3/trigger"

// #define LED0_PATH_BRIGHT "/sys/class/leds/beaglebone:green:usr0/brightness"
// #define LED1_PATH_BRIGHT "/sys/class/leds/beaglebone:green:usr1/brightness"
// #define LED2_PATH_BRIGHT "/sys/class/leds/beaglebone:green:usr2/brightness"
// #define LED3_PATH_BRIGHT "/sys/class/leds/beaglebone:green:usr3/brightness"

// Paths to LED control files
static const char* LED_PATHS_TRIGGER[] = {
    "/sys/class/leds/beaglebone:green:usr0/trigger",
    "/sys/class/leds/beaglebone:green:usr1/trigger",
    "/sys/class/leds/beaglebone:green:usr2/trigger",
    "/sys/class/leds/beaglebone:green:usr3/trigger"};

static const char* LED_PATHS_BRIGHTNESS[] = {
    "/sys/class/leds/beaglebone:green:usr0/brightness",
    "/sys/class/leds/beaglebone:green:usr1/brightness",
    "/sys/class/leds/beaglebone:green:usr2/brightness",
    "/sys/class/leds/beaglebone:green:usr3/brightness"};

static bool is_initialized = false;

void led_init() {
  assert(!is_initialized);
  is_initialized = true;

  for (int i = 0; i < 4; i++) {  // Set triggers to none
    bbgSetTrigger(LED_PATHS_TRIGGER[i], "none");
  }

  for (int i = 1; i < 3; i++) {  // Turn on middle two LEDs on BBG
    bbgLedBright(LED_PATHS_BRIGHTNESS[i], "1");
  }
}

void led_cleanup(void) {
  printf("LED - Cleanup\n");
  assert(is_initialized);
  is_initialized = false;

  // Reset LEDs (optional, based on your application needs)
}

void bbgSetTrigger(const char* fileName, char* value) {
  FILE* pLedTriggerFile = fopen(fileName, "w");

  if (pLedTriggerFile == NULL) {
    printf("ERROR OPENING %s.", fileName);
    exit(1);
  }

  int charWritten = fprintf(pLedTriggerFile, "%s", value);
  if (charWritten <= 0) {
    printf("ERROR WRITING DATA");
    exit(1);
  }
  fclose(pLedTriggerFile);
}

void bbgLedBright(const char* fileName, char* value) {
  FILE* pLedBrightnessFile = fopen(fileName, "w");

  if (pLedBrightnessFile == NULL) {
    printf("ERROR OPENING %s.", fileName);
    exit(1);
  }

  int charWritten = fprintf(pLedBrightnessFile, "%s", value);
  if (charWritten <= 0) {
    printf("ERROR WRITING DATA");
    exit(1);
  }
  fclose(pLedBrightnessFile);
}