// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hal/button.h"
#include "hal/led.h"

// Code provided for sleep
static void sleepForMs(long long delayInMs) {
  const long long NS_PER_MS = 1000 * 1000;
  const long long NS_PER_SECOND = 1000000000;

  long long delayNs = delayInMs * NS_PER_MS;
  int seconds = delayNs / NS_PER_SECOND;
  int nanoseconds = delayNs % NS_PER_SECOND;

  struct timespec reqDelay = {seconds, nanoseconds};
  nanosleep(&reqDelay, (struct timespec *)NULL);
}

// Code provided for getting current time
static long long getTimeInMs(void) {
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  long long seconds = spec.tv_sec;
  long long nanoSeconds = spec.tv_nsec;
  long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
  return milliSeconds;
}

int main() {
  // Set triggers to none and turn on middle two LEDs on BBG
  led_init();

  // Initialize the button (config-pin and set for input)
  button_init();

  printf("Hello embedded world, from Ian!\n");
  printf("Get ready...\n");

  // If the user is pressing the joystick, tell them “Please let go of joystick”
  // and wait until the joystick is not pressing.
  while (true) {
    if (getJoystickDirection() != JSTICK_NONE) {
      printf("Please let go of joystick\n");
      while (getJoystickDirection() != JSTICK_NONE) {
        sleepForMs(500);
      }
      break;
    } else {
      break;
    }
  }

  // Wait for 3 seconds
  sleepForMs(3000);

  // Turn the middle two LEDs off
  bbgLedBright(LED_PATHS_BRIGHTNESS[1], "0");
  bbgLedBright(LED_PATHS_BRIGHTNESS[2], "0");
  srand(time(NULL));

  while (true) {
    getTimeInMs();
    // 0 - Down; 1 - Up
    int direction = rand() % 2;
    if (direction == 0) {  // Down
      printf("Press DOWN now!\n");
      bbgLedBright(LED_PATHS_BRIGHTNESS[0], "1");
    } else {  // Up
      printf("Press UP now!\n");
      bbgLedBright(LED_PATHS_BRIGHTNESS[3], "1");
    }

    // Quit for pressing left or right
    if (getJoystickDirection() == JSTICK_LEFT ||
        getJoystickDirection() == JSTICK_RIGHT) {
      printf("User selected to quit.\n");
      for (int i = 0; i < 4; i++) {
        bbgLedBright(LED_PATHS_BRIGHTNESS[i], "0");
      }
      break;
    }
  }

  return 0;
}