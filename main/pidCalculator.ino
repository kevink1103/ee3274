EEProj::Pid<1> horizon_pid(0.99, 3, 0, INCREMENT);
EEProj::Vector<1> output;
unsigned long lasttime = micros();
double goal = 35; // goal RSSI to maintain

// Consider anti-clockwise now
void calculatePid() {
  double newRSSI = (double)poles[0].getRSSI();
  double error = newRSSI - goal; // if neg, too close, if pos, too far
  if (error <= 1 && error >= -1) {
    error = 0;
  }
  horizon_pid.newInput(error, micros() - lasttime);
  lasttime = micros();
  output = horizon_pid.get_pid();

  int thrust = output.x();
  int leftThrust;
  int rightThrust;

  // if (error <= 0) {
  //   leftThrust = thrust * 0.3 * -1;
  //   rightThrust = leftThrust * 0.8;
  // }
  // else if (error >= 0) {
  //   rightThrust = thrust * 0.3;
  //   leftThrust = rightThrust * 0.8;
  // }

  if (thrust >= -70 && thrust <= 0) {
    leftThrust = thrust * -1 * 1.5;
    rightThrust = thrust;
  }
  else if (thrust >= 0 && thrust <= 70) {
    rightThrust = thrust * 1.5;
    leftThrust = thrust;
  }
  else {
    leftThrust = 0;
    rightThrust = 0;
  }

  if (error == 0) {
    leftThrust = 30;
    rightThrust = 70;
  }
  
  ship.setLeftThrust(leftThrust);
  ship.setRightThrust(rightThrust);
  ship.setUpDownThrust(0);

  Serial.println(error);
  Serial.println(output.x());
  Serial.println(leftThrust);
  Serial.println(rightThrust);
}
