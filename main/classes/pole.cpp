#include <Arduino.h>

class pole {
private:
  String mac = "";
  int rssi = 0;
public:
  // Setters
  void setMAC(String newMAC) {
    mac = newMAC;
  }
  void setRSSI(int newRSSI) {
    rssi = newRSSI;
  }

  // Getters
  String getMAC() {
    return mac;
  }
  int getRSSI() {
    return rssi;
  }
};
