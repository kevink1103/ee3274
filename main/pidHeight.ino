EEProj::Pid<1> height_pid(0.99, 3, 0, INCREMENT);
EEProj::Vector<1> height_output;
unsigned long lastt = micros();
double altitude = 1000;

void heightPid(int height) {
  if (height == 200) {
    return;
  }
  double error = altitude - height;
  if (error <= 25 && error >= -25) {
    error = 0;
  }

  height_pid.newInput(error, micros() - lastt);
  lastt = micros();
  height_output = height_pid.get_pid();

  int thrust = height_output.x();

  ship.setUpDownThrust(thrust);

  Serial.println("BEGIN");
  Serial.println(height);
  Serial.println(ship.getUpDownVal());
  Serial.println(ship.getUpDownDir());
}
