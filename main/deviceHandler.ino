void updateDevice(String mac, String rssi) {
  for (int i=0; i<7; i++) {
    if (areSimilarStrings(poles[i].getMAC(), mac)) {
      Serial.print("FOUND: ");
      Serial.print(mac);
      Serial.print(" : ");
      Serial.println(rssi);
      poles[i].setRSSI(rssi.toInt());
      return;
    }
  }
}