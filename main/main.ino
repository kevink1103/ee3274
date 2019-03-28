#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "library/pid.h"
#include "classes/airship.cpp"
#include "classes/pole.cpp"
#include "utilities/textManager.cpp"

#define MAC1 "3CA5080A9A05"

#define leftPWM 5
#define leftDir 6
#define rightPWM 9
#define rightDir 10
#define upDownPWM 11
#define upDownDir 12
#define BtRx 0
#define BtTx 1
#define ScannerRx 18 // A4
#define ScannerTx 19 // A5

SoftwareSerial BluetoothSerial(BtRx, BtTx);
SoftwareSerial ScannerSerial(ScannerRx, ScannerTx); // RX|TX A4|A5

airship ship;
pole poles[7];

char scannerIncoming;
char localIncoming;
String localIncomingString;

void setup() {
  Serial.begin(115200);
  BluetoothSerial.begin(115200);
  ScannerSerial.begin(115200);

  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  pinMode(upDownPWM, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightDir, OUTPUT);
  pinMode(upDownDir, OUTPUT);

  ship.setPins(leftPWM, leftDir, rightPWM, rightDir, upDownPWM, upDownDir);
  poles[0].setMAC(MAC1);

  // while(!Serial); // Wait until serial port is ready
}

void loop() {
  localInstreamHandler();
  scannerInstreamHandler();
  ship.pwmManager();
}
