#include "hal/joystick.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

// UP 26, RIGHT 47, DOWN 46, LEFT 65, PUSHED 27
static const char* JSTICK[] = {
    "/sys/class/gpio/gpio26/value", "/sys/class/gpio/gpio47/value",
    "/sys/class/gpio/gpio46/value", "/sys/class/gpio/gpio65/value",
    "/sys/class/gpio/gpio27/value"};

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

void runCommand(const char* command) {
  // Execute the shell command (output into pipe)
  FILE* pipe = popen(command, "r");

  // Ignore output of the command; but consume it
  // so we don't get an error when closing the pipe.
  char buffer[1024];
  while (!feof(pipe) && !ferror(pipe)) {
    if (fgets(buffer, sizeof(buffer), pipe) == NULL) break;

    // printf("--> %s", buffer); // Uncomment for debugging
  }

  // Get the exit code from the pipe; non-zero is an error:
  int pcloseResult = pclose(pipe);
  int exitCode = WEXITSTATUS(pcloseResult);
  if (exitCode != 0) {
    perror("Unable to execute command:");
    printf(" command: %s\n", command);
    printf(" exit code: %d\n", exitCode);
  }
}

void button_init(void) {
  assert(!is_initialized);
  is_initialized = true;

  // Execute config-pin
  runCommand("config-pin p8.26 gpio");
  //   runCommand("config-pin p8.47 gpio");
  runCommand("config-pin p8.46 gpio");
  //   runCommand("config-pin p8.65 gpio");
  runCommand("config-pin p8.27 gpio");

  // Set in > direction
  runCommand("echo in > /sys/class/gpio/gpio26/direction");
  runCommand("echo in > /sys/class/gpio/gpio47/direction");
  runCommand("echo in > /sys/class/gpio/gpio46/direction");
  runCommand("echo in > /sys/class/gpio/gpio65/direction");
  runCommand("echo in > /sys/class/gpio/gpio27/direction");
}

bool readGpioPin(const char* fileName) {
  FILE* gpioValueFile = fopen(fileName, "r");

  if (gpioValueFile == NULL) {
    printf("ERROR OPENING %s.", fileName);
    exit(1);
  }

  bool isPressed = (fgetc(gpioValueFile) == '0');
  fclose(gpioValueFile);

  return isPressed;
}

joyStickButton getJoystickDirection() {
  if (readGpioPin(JSTICK[0])) {
    return JSTICK_UP;
  } else if (readGpioPin(JSTICK[1])) {
    return JSTICK_RIGHT;
  } else if (readGpioPin(JSTICK[2])) {
    return JSTICK_DOWN;
  } else if (readGpioPin(JSTICK[3])) {
    return JSTICK_LEFT;
  } else if (readGpioPin(JSTICK[4])) {
    return JSIICK_PUSHED;
  }

  return JSTICK_NONE;
}

void button_cleanup(void) {
  // Free any memory, close files, ...
  printf("Button - Cleanup\n");
  assert(is_initialized);
  is_initialized = false;
}
