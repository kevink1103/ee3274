#include <Arduino.h>

// PWM: 3, 5, 6, 9, 10, and 11
enum PINS: int {
  leftPWM = 5,
  leftDirection = 6,
  rightPWM = 9,
  rightDirection = 10,
  upDownPWM = 11,
  upDownDirection = 12
};