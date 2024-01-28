#include "hal/led.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../app/include/helper.h"

// Paths to LED trigger
static const char* LED_PATHS_TRIGGER[] = {
    "/sys/class/leds/beaglebone:green:usr0/trigger",
    "/sys/class/leds/beaglebone:green:usr1/trigger",
    "/sys/class/leds/beaglebone:green:usr2/trigger",
    "/sys/class/leds/beaglebone:green:usr3/trigger"};

// Set triggers to none and turn on middle two LEDs
void led_init() {
  for (int i = 0; i < 4; i++) {
    bbgSetTrigger(LED_PATHS_TRIGGER[i], "none");
  }

  led_cleanup();

  for (int i = 1; i < 3; i++) {
    bbgLedBright(LED_PATHS_BRIGHTNESS[i], "1");
  }
}

// Turn off all LEDs
void led_cleanup(void) {
  for (int i = 0; i < 4; i++) {
    bbgLedBright(LED_PATHS_BRIGHTNESS[i], "0");
  }
}

// Set trigger values
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

// Set brightness values
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

// Flash four LEDs
// Duration in seconds
void flashLed(const int frequency, const double duration) {
  long long startTime = getTimeInMs();
  long long durationInMs = duration * 1000;
  int halfPeriodInMs = 1000 / (2 * frequency);

  while (getTimeInMs() - startTime <= durationInMs) {
    bbgLedBright(LED_PATHS_BRIGHTNESS[0], "1");
    bbgLedBright(LED_PATHS_BRIGHTNESS[1], "1");
    bbgLedBright(LED_PATHS_BRIGHTNESS[2], "1");
    bbgLedBright(LED_PATHS_BRIGHTNESS[3], "1");
    sleepForMs(halfPeriodInMs);
    bbgLedBright(LED_PATHS_BRIGHTNESS[0], "0");
    bbgLedBright(LED_PATHS_BRIGHTNESS[1], "0");
    bbgLedBright(LED_PATHS_BRIGHTNESS[2], "0");
    bbgLedBright(LED_PATHS_BRIGHTNESS[3], "0");
    sleepForMs(halfPeriodInMs);
  }
}