#include <Arduino.h>

class airship {
private:
  int leftPin = PINS::leftPWM;
  int leftDir = PINS::leftDirection;
  int rightPin = PINS::rightPWM;
  int rightDir = PINS::rightDirection;
  int upDownPin = PINS::upDownPWM;
  int upDownDir = PINS::upDownDirection;
  int pwmValues[6];
public:
  void setPWMValues(String inputString) {
    // inputString format:
    // "leftPin leftDir rightPin rightDir upDownPin upDownDir#"
    String temp;
    int word = 0;
    for (int i=0; i<inputString.length(); i++) {
      char currentChar = inputString.charAt(i);
      if (currentChar == ' ' || i == inputString.length()-1) {
        if (i == inputString.length()-1) {
          temp += currentChar;
        }
        pwmValues[word] = temp.toInt();
        temp = "";
        word++;
        continue;
      }
      temp += currentChar;
    }
  }

  void pwmManager() {
    // Set values to pins accordingly
    if ((pwmValues[0] >= 0 && pwmValues[0] <= 255) &&
        (pwmValues[1] >= 0 && pwmValues[1] <= 1) &&
        (pwmValues[2] >= 0 && pwmValues[2] <= 255) &&
        (pwmValues[3] >= 0 && pwmValues[3] <= 1) &&
        (pwmValues[4] >= 0 && pwmValues[4] <= 255) &&
        (pwmValues[5] >= 0 && pwmValues[5] <= 1)) {
      analogWrite(leftPin, pwmValues[0]);
      digitalWrite(leftDir, pwmValues[1]);
      analogWrite(rightPin, pwmValues[2]);
      digitalWrite(rightDir, pwmValues[3]);
      analogWrite(upDownPin, pwmValues[4]);
      digitalWrite(upDownDir, pwmValues[5]);
    }
  }
};
