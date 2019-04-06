#include <Arduino.h>

#define leftForward 1;
#define leftBackward 0;
#define rightForward 0;
#define rightBackward 1;
#define upDownUp 0;
#define upDownDown 1;

class airship {
private:
  int leftPWM;
  int leftDir;
  int rightPWM;
  int rightDir;
  int upDownPWM;
  int upDownDir;
  int pwmValues[6];
public:
  void setPins(int left1, int left2, int right1, int right2, int ud1, int ud2) {
    leftPWM = left1;
    leftDir = left2;
    rightPWM = right1;
    rightDir = right2;
    upDownPWM = ud1;
    upDownDir = ud2;
  }

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

  void setLeftThrust(int signal) {
    int adjSignal = adjustSignalRange(signal);
    if (adjSignal >= 0 && adjSignal <= 255) {
      pwmValues[0] = adjSignal;
      pwmValues[1] = leftForward;
    }
    else if (adjSignal < 0 && adjSignal >= -255) {
      pwmValues[0] = adjSignal*-1;
      pwmValues[1] = leftBackward;
    }
  }

  void setRightThrust(int signal) {
    int adjSignal = adjustSignalRange(signal);
    if (adjSignal >= 0 && adjSignal <= 255) {
      pwmValues[2] = adjSignal;
      pwmValues[3] = rightForward;
    }
    else if (adjSignal < 0 && adjSignal >= -255) {
      pwmValues[2] = adjSignal*-1;
      pwmValues[3] = rightBackward;
    }
  }

  void setUpDownThrust(int signal) {
    int adjSignal = adjustSignalRange(signal);
    if (adjSignal >= 0 && adjSignal <= 255) {
      pwmValues[4] = adjSignal;
      pwmValues[5] = upDownUp;
    }
    else if (adjSignal < 0 && adjSignal >= -255) {
      pwmValues[4] = adjSignal*-1;
      pwmValues[5] = upDownDown;
    }
  }

  int adjustSignalRange(int signal) {
    if (signal > 255) {
      return 255;
    }
    else if (signal < -255) {
      return -255;
    }
    else {
      return signal;
    }
  }

  int getUpDownVal() {
    return pwmValues[4];
  }

  int getUpDownDir() {
    return pwmValues[5];
  }

  void pwmManager() {
    // Set values to pins accordingly
    if ((pwmValues[0] >= 0 && pwmValues[0] <= 255) &&
        (pwmValues[1] >= 0 && pwmValues[1] <= 1) &&
        (pwmValues[2] >= 0 && pwmValues[2] <= 255) &&
        (pwmValues[3] >= 0 && pwmValues[3] <= 1) &&
        (pwmValues[4] >= 0 && pwmValues[4] <= 255) &&
        (pwmValues[5] >= 0 && pwmValues[5] <= 1)) {
      analogWrite(leftPWM, pwmValues[0]);
      digitalWrite(leftDir, pwmValues[1]);
      analogWrite(rightPWM, pwmValues[2]);
      digitalWrite(rightDir, pwmValues[3]);
      analogWrite(upDownPWM, pwmValues[4]);
      digitalWrite(upDownDir, pwmValues[5]);
    }
  }
};
