#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdbool.h>

typedef enum {
  JSTICK_UP,
  JSTICK_RIGHT,
  JSTICK_DOWN,
  JSTICK_LEFT,
  JSIICK_PUSHED,
  JSTICK_NONE
} joyStickButton;

void button_init(void);
void button_cleanup(void);
bool readGpioPin(const char* fileName);
joyStickButton getJoystickDirection();
void runCommand(const char* command);

#endif