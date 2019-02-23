void localInstreamHandler() {
  while (Serial.available() > 0) {
    localIncoming = Serial.read();
    
    // every command ends with '#'
    if (localIncoming != '#') {
      localIncomingString += localIncoming;
    }
    else {
      if (isAllNumbers(localIncomingString) == true) {
        ship->setPWMValues(localIncomingString);
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
