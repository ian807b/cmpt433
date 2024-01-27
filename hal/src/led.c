#include "hal/led.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Paths to LED trigger
static const char* LED_PATHS_TRIGGER[] = {
    "/sys/class/leds/beaglebone:green:usr0/trigger",
    "/sys/class/leds/beaglebone:green:usr1/trigger",
    "/sys/class/leds/beaglebone:green:usr2/trigger",
    "/sys/class/leds/beaglebone:green:usr3/trigger"};

static bool is_initialized = false;

void led_init() {
  assert(!is_initialized);
  is_initialized = true;

  for (int i = 0; i < 4; i++) {  // Set triggers to none
    bbgSetTrigger(LED_PATHS_TRIGGER[i], "none");
  }

  led_cleanup();  // Turn off everything first

  for (int i = 1; i < 3; i++) {  // Turn on middle two LEDs on BBG
    bbgLedBright(LED_PATHS_BRIGHTNESS[i], "1");
  }
}

void led_cleanup(void) {
  for (int i = 0; i < 4; i++) {
    bbgLedBright(LED_PATHS_BRIGHTNESS[i], "0");
  }
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

// void flashLed(const char* fileName, const int interval) {
// }