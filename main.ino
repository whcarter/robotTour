#include <Stepper.h>

// TODO: change pins to match wiring
Stepper right = Stepper(200, 2, 3, 4, 5); //3 5 4 2     2453  2435
Stepper left = Stepper(200, 8, 9, 10, 11);

const int turnTime = 0; // average duration of a turn (ms)
const int targetTime = 60000; // (ms)

int remainingDistance = 0; // (cm)
byte numTurns = 10;

int startTime = 0; // (ms)
int remainingTime = 0; // (ms)
int velocity = 0; // (rpm)

// Stand-in for whatever actually makes the motors move properly
void moveRight(int steps) {}
void moveLeft(int steps) {}

// Drives straight a given distance (cm)
void driveFor(int dist) {
  moveRight(int(dist / 22 * 200));
  moveLeft(int(dist / 22 * 200));
  remainingDistance -= dist;
}

// Turns clockwise a given angle (degrees)
void turn(int angle) {
  // angle / 360 * turn circumference / wheel circumference * num steps
  moveLeft(int(angle * 1.185));
  moveRight(int(-angle * 1.185));
  numTurns--;
}

void adjustVelocity() {
  remainingTime = targetTime - (millis() - startTime);
  velocity = int((remainingDistance / 22) / ((remainingTime - numTurns * turnTime) / 60000));
}

void route() {
  startTime = millis();
  adjustVelocity();
  // Add route:
  
}

void setup() {
  pinMode(13, INPUT);
}

void loop() {
  if (digitalRead(13) == HIGH) {
    delay(1000);
    route();
    delay(100000000);
  }
}
