#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "classes/pins.cpp"
#include "classes/macs.cpp"
#include "classes/airship.cpp"
#include "classes/device.cpp"
#include "utilities/textManager.cpp"

SoftwareSerial BluetoothSerial(0, 1);
SoftwareSerial ScannerSerial(18, 19); // RX|TX A4|A5

airship *ship = new airship();
device poles[7];

char scannerIncoming;
char localIncoming;
String localIncomingString;

void setup() {
  Serial.begin(115200);
  BluetoothSerial.begin(115200);
  ScannerSerial.begin(115200);

  pinMode(PINS::leftPWM, OUTPUT);
  pinMode(PINS::rightPWM, OUTPUT);
  pinMode(PINS::upDownPWM, OUTPUT);
  pinMode(PINS::leftDirection, OUTPUT);
  pinMode(PINS::rightDirection, OUTPUT);
  pinMode(PINS::upDownDirection, OUTPUT);

  MACS mac_list;
  poles[0].setMAC(mac_list.PA);
  poles[1].setMAC(mac_list.PB);
  poles[2].setMAC(mac_list.PC);
  poles[3].setMAC(mac_list.PD);
  poles[4].setMAC(mac_list.PE);
  poles[5].setMAC(mac_list.PF);
  poles[6].setMAC(mac_list.PG);

  while(!Serial); // Wait until serial port is ready
}

void loop() {
  ship->pwmManager();
  localInstreamHandler();
  scannerInstreamHandler();
}
