#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "pins.cpp"
#include "classes/device.cpp"
#include "utilities/textManager.h"

SoftwareSerial BluetoothSerial(0, 1);
SoftwareSerial ScannerSerial(18, 19); // RX|TX A4|A5

char scannerIncoming;
char localIncoming;
String localIncomingString;

int leftPin = PINS::leftPWM;
int leftDir = PINS::leftDirection;
int rightPin = PINS::rightPWM;
int rightDir = PINS::rightDirection;
int upDownPin = PINS::upDownPWM;
int upDownDir = PINS::upDownDirection;
int pwmValues[6];

boolean isAllNumber(String base) {
  // Check if the whole string is composed of numbers
  boolean result = true;
  for (int i=0; i<base.length(); i++) {
    char currentChar = base.charAt(i);
    
    if (isAlpha(currentChar) == true) {
      result = false;
      break;
    }
    else {
      continue;
    }
  }
  return result;
}

void setPWMValues(String inputString) {
  // inputString format:
  // "leftPin leftDir rightPin rightDir upDownPin upDownDir#"

  // Store values in int to pwmValues Array
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
  Serial.print(inputString);
  Serial.println(" SET");
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
  else {
    Serial.println("smth wrong");
  }
}

void setup() {
  Serial.begin(115200);
  BluetoothSerial.begin(115200);
  ScannerSerial.begin(115200);

  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(upDownPin, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightDir, OUTPUT);
  pinMode(upDownDir, OUTPUT);

  while(!Serial); // Wait until serial port is ready
}

void loop() {
  pwmManager();
  localInstreamHandler();
  scannerInstreamHandler();
}

void localInstreamHandler() {
  while (Serial.available() > 0) {
    localIncoming = Serial.read();
    
    // every command ends with '#'
    if (localIncoming != '#') {
      localIncomingString += localIncoming;
    }
    else {
      if (isAllNumber(localIncomingString) == true) {
        setPWMValues(localIncomingString);
      }
      localIncomingString = ""; // clear input
    }
    ScannerSerial.write(localIncoming);
  }
}

void scannerInstreamHandler() {
  String block = "";
  String mac = "";
  String rssi = "";
  
  bool flag = false;
  while (ScannerSerial.available() > 0) {
    scannerIncoming = ScannerSerial.read();

    if (scannerIncoming == ':') {
      block = "";
      flag = true;
      continue;
    }
    else if (scannerIncoming == '	' || scannerIncoming == '\n') {
      if (block.length() == 12) {
        mac = block;
      }
      else if (block.charAt(0) == '-') {
        rssi = block;
      }
      if (mac.length() == 12 && rssi.length() > 0) {
        // Do something like add a device here with mac and rssi
        // Serial.println(mac);
        // Serial.println(rssi);
        device *ibeacon = new device();
        ibeacon->setMAC(mac);
        ibeacon->setRSSI(rssi.toInt());
        Serial.println(ibeacon->getMAC());
        Serial.println(ibeacon->getRSSI());
        delete ibeacon;
      }
      block = "";
      flag = false;
      continue;
    }
    if (flag) {
      block += scannerIncoming;
    }

  }
}
