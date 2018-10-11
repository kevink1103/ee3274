char character;
String btInput = "";

// PWM: 3, 5, 6, 9, 10, and 11
int leftPin = 3;
int leftDir = 2;
int rightPin = 5;
int rightDir = 4;
int upDownPin = 6;
int upDownDir = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set baud rate for Serial communication (between Arduino and Terminal)
  
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
      break;
    }
    else {
      continue;
    }
  }
  return result;
}

void pwmManager(String inputString) {
  // inputString format:
  // "leftPin leftDir rightPin rightDir upDownPin upDownDir"

  // Store values in int to pwmValues Array
  int pwmValues[6];
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
    Serial.print(inputString);
    Serial.println(" APPLIED");
  }
  else {
    Serial.println("Input numbers out of range");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // read AT command from Terminal, then write it to Bluetooth Module
  while (Serial.available() > 0) {
    character = Serial.read();

    if (character != '\n') {
      btInput += character;
    }
    else {
      // end of string (character == '\n')
      if (checkNum(btInput) == true) {
        // if the whole input string is number
        pwmManager(btInput);
      }
      else {
        // Not number
      }
      btInput = ""; // clear input
    }
  }
}
