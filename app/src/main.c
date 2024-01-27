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
  nanosleep(&reqDelay, (struct timespec *) NULL);
}

int main() {
  // Set triggers to none and turn on middle two LEDs on BBG
  led_init();

  // Initialize the button (config-pin and set for input)
  button_init();

  printf("Hello embedded world, from Ian!\n");
  printf("get ready\n");

  // If the user is pressing the joystick, tell them “Please let go of joystick”
  // and wait until the joystick is not pressing.
  while (true) {
    if (getJoystickDirection() != JSTICK_NONE) {
        printf("Please let go of joystick\n");
        while (getJoystickDirection() != JSTICK_NONE) {
          sleepForMs(500);  
        }
        break;
    }
  }

  // Wait for 1s
  sleepForMs(1000);

  // 5. Picks a random direction (up or down) and print the direction name to the screen.



  // 6. Display the program’s chosen direction on the BBG’s LEDs:

  // - Turn off the middle two LEDs

  // - If program chose up, then turn on the top LED (#0).

  // - If program chose down, then turn on the bottom LED (#3).

  // 7. Time how long it takes for the user to press the joystick in any direction.

  // - If timer > 5s, exit program with a message without waiting for a joystick press.

  // 8. Process the user’s joystick press:

  // a) If the user pressed up or down correctly, then:

  // - print a message,

  // - if this was the fastest correct response time yet then display that in a message,

  // - display this attempt’s response time, and best response time so far (in ms),

  // - flash all four LEDs on and off at 4hz for 0.5 seconds (two flashes).

  // b) If the user pressed up or down incorrectly, print a message and flash all four LEDs on and off at 10hz for 1 second.

  // c) If the user pressed left or right, print a message and quit.
}