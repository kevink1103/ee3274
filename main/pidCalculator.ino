EEProj::Pid<1> horizon_pid(0.99, 3, 1, INCREMENT);
EEProj::Vector<1> output;
unsigned long lasttime = micros();
double goal = 50; // goal RSSI to maintain

// Consider anti-clockwise
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

  if (thrust >= -70 && thrust < 0) {
    leftThrust = thrust * -1 * 1.4;
    rightThrust = thrust * 0.7;
  }
  else if (thrust >= 0 && thrust <= 70) {
    rightThrust = thrust * 1.4;
    leftThrust = thrust * 0.7;
  }
  else {
    leftThrust = 0;
    rightThrust = 0;
  }

  if (error == 0) {
    leftThrust = 20;
    rightThrust = 50;
  }
  
  ship.setLeftThrust(leftThrust);
  ship.setRightThrust(rightThrust);

  Serial.println(error);
  Serial.println(output.x());
  Serial.println(leftThrust);
  Serial.println(rightThrust);
}
