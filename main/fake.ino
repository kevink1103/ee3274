void fakeMove() {
  long diff = micros() - lastTime;
  long hold = 0;

  if (thrust) {
    hold = 1000000;
  }
  else {
    hold = 500000;
  }

  if (diff >= hold) { // after 1 seconds = 1000000
    thrust = !thrust;
    lastTime = micros();
  }

  if (thrust) {
    ship.setLeftThrust(30);
    ship.setRightThrust(80);
  }
  else {
    ship.setLeftThrust(25);
    ship.setRightThrust(25);
  }
}