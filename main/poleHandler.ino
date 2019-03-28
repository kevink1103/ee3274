int updatePole(String mac, String rssi) {
  for (int i=0; i<7; i++) {
    if (areSimilarStrings(poles[i].getMAC(), mac)) {
      Serial.print("FOUND: ");
      Serial.print(mac);
      Serial.print(" : ");
      int rssiVal = getOnlyNum(rssi).toInt();
      Serial.println(rssiVal);
      poles[i].setRSSI(rssiVal);
      return i;
    }
  }
  return -1;
}
