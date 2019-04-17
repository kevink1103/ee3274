void localInstreamHandler() {
  while (Serial.available() > 0) {
    localIncoming = Serial.read();
    
    // every command ends with '#'
    if (localIncoming != '#') {
      localIncomingString += localIncoming;
    }
    else {
      if (isAllNumbers(localIncomingString) == true) {
        ship.setPWMValues(localIncomingString);
        Serial.println(localIncomingString);
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
    Serial.write(scannerIncoming);
    
    if (scannerIncoming == ':') {
      block = "";
      flag = true;
      continue;
    }
    else if (scannerIncoming == 'U' || scannerIncoming == 'R') {
      block = "";
      flag = false;
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
        Serial.println(mac);
        // Do something like add a device here with mac and rssi
        int result = updatePole(mac, rssi);
        if (result != -1) { // Only calculate Pid when there is update
          calculatePid();
        }
        mac = "";
        rssi = "";
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

void ultInstreamHandler() {
  UltSerial.listen();
  if (UltSerial.available() > 0) {
    ultIncoming = UltSerial.read();
    if (ultIncoming == '\n') {
      int height = ultIncomingString.substring(0,3).toInt();
      heightPid(height);
      ultIncomingString = "";
      return;
    }
    else {
      ultIncomingString += ultIncoming;
    }
  }
}