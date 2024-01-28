// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hal/joystick.h"
#include "hal/led.h"
#include "helper.h"

int main() {
  // Set triggers to none and turn on middle two LEDs on BBG
  led_init();

  // Initialize the button (config-pin and set for input)
  button_init();

  printf("Hello embedded world, from Ian!\n");
  printf(
      "When the LEDs light up, press the joystick in that direction! (Press "
      "left or right to exit)\n");

  srand(time(NULL));
  long long bestRecord = __LONG_LONG_MAX__;
  bool responseFromUser = false;
  bool firstExecution = true;

  while (true) {
    printf("Get ready...\n");
    responseFromUser = false;

    // If the user is pressing the joystick, tell them “Please let go of
    // joystick” and wait until the joystick is not pressing.
    while (true) {
      if ((getJoystickDirection() != JSTICK_NONE) && firstExecution == true) {
        printf("Please let go of joystick\n");
        while (true) {
          if (getJoystickDirection() == JSTICK_NONE) {
            break;
          }
        }
      }
      break;
    }
    firstExecution = false;

    // Wait for 1.5 seconds
    sleepForMs(1500);

    // Turn the middle two LEDs off
    bbgLedBright(LED_PATHS_BRIGHTNESS[1], "0");
    bbgLedBright(LED_PATHS_BRIGHTNESS[2], "0");

    // 0 - Down; 1 - Up
    int direction = rand() % 2;
    if (direction == 0) {  // Down
      printf("Press DOWN now!\n");
      bbgLedBright(LED_PATHS_BRIGHTNESS[3], "1");
    } else {  // Up
      printf("Press UP now!\n");
      bbgLedBright(LED_PATHS_BRIGHTNESS[0], "1");
    }

    // Declare variables for timing & loop control
    long long responseTime = 0;
    long long startTime = getTimeInMs();
    joyStickButton userResponse = JSTICK_NONE;

    while (!responseFromUser) {
      userResponse = getJoystickDirection();
      responseTime = getTimeInMs() - startTime;

      if (userResponse != JSTICK_NONE) {
        if ((direction == 0 && userResponse == JSTICK_DOWN) ||
            (direction == 1 && userResponse == JSTICK_UP)) {
          printf("Correct!\n");
          if (responseTime < bestRecord) {
            printf("New best time!\n");
            bestRecord = responseTime;
          }
          printf(
              "Your reaction time was %lldms; best so far in game is %lld.\n",
              responseTime, bestRecord);
          flashLed(4, 0.5);
        } else if (getJoystickDirection() == JSTICK_LEFT ||
                   getJoystickDirection() == JSTICK_RIGHT) {
          printf("User selected to quit.\n");
          led_cleanup();
          return 0;
        } else {
          printf("Incorrect.\n");
          flashLed(10, 1);
        }
        responseFromUser = true;
        // Turn off the LED each round
        bbgLedBright(LED_PATHS_BRIGHTNESS[0], "0");
        bbgLedBright(LED_PATHS_BRIGHTNESS[3], "0");
      } else if (responseTime > 5000) {
        printf("No input within 5000ms; quitting!\n");
        led_cleanup();
        return 0;
      }
    }
  }

  return 0;
}