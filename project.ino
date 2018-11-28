#include <SoftwareSerial.h>

SoftwareSerial BT_Serial(0, 1); // RX|TX 7 8

char character;
String btInput = "";

// PWM: 3, 5, 6, 9, 10, and 11
int leftPin = 5;
int leftDir = 6;
int rightPin = 9;
int rightDir = 10;
int upDownPin = 11;
int upDownDir = 12;
int pwmValues[6];

void setup() {
  Serial.begin(9600);
  BT_Serial.begin(9600);
  
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(upDownPin, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightDir, OUTPUT);
  pinMode(upDownDir, OUTPUT);

  while(!Serial); // wait until serial port is ready
}

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

void loop() {

  // keep setting the values
  pwmManager();
  
  // put your main code here, to run repeatedly:
  // read AT command from Terminal, then write it to Bluetooth Module
  while (Serial.available() > 0) {
    character = Serial.read();
    
    // every command ends with '#'
    if (character != '#') {
      btInput += character;
    }
    else {
      if (isAllNumber(btInput) == true) {
        setPWMValues(btInput);
      }
      btInput = ""; // clear input
    }
  }

  // read response from Bluetooth Module, then display it on Terminals
  while (BT_Serial.available() > 0) {
    character = BT_Serial.read();
    // Nothing should happen here
    // When connected with Pin 0,1
  }
}
