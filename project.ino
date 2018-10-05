#include <SoftwareSerial.h>

SoftwareSerial BT_Serial(10, 11); // RX|TX

char character;
String btInput = "";

// PWM: 3, 5, 6, 9, 10, and 11
int leftDir = 2;
int leftPin = 3;
int rightDir = 4;
int rightPin = 5;
int upDownPin = 6;
int upDownDir = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set baud rate for Serial communication (between Arduino and Terminal)
  BT_Serial.begin(9600); // set baud rate for BT_Serial communication (between Arduino and Bluetooth Module)
  
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(upDownPin, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightDir, OUTPUT);
  pinMode(upDownDir, OUTPUT);

  while(!Serial);// wait until serial port is ready
}

boolean checkNum(String base) {
  // Check if the whole string is composed of numbers
  boolean result = true;
  for (int i=0; i<base.length(); i++) {
    char currentChar = base.charAt(i);
    
    if (isAlpha(currentChar) == true) {
      result = false;
    }
    else {
      continue;
    }
  }
  return result;
}

void pwm_manager() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // read AT command from Terminal, then write it to Bluetooth Module
  while (Serial.available() > 0) {
    character = Serial.read();

    if (character != '\n') {
      BT_Serial.write(character);
      btInput += character;
    }
    else {
      // end of string
      if (checkNum(btInput) == true) {
        // if the input string is number
        int value = btInput.toInt();
        if (value >= 0 && value <= 255) {
          // Put value to the PWM pin
          Serial.print(value, DEC);
          analogWrite(leftPin, value);
        }
        else {
          Serial.write("Input value invalid.");
        }
        
      }
      
      btInput = ""; // clear input
    }
    
  }

  // read response from Bluetooth Module, then display it on Terminals
  while (BT_Serial.available() > 0) {
    character = BT_Serial.read();
    Serial.write(character);
    
  }
}
