#include <Servo.h>

// TODO: change pins to match wiring
Servo right;
Servo left;


const int turnTime = 0; // average duration of a turn (ms)
const int targetTime = 60000; // (ms)

int remainingDistance = 0; // (cm)
byte numTurns = 10;

int startTime = 0; // (ms)
int remainingTime = 0; // (ms)
float velocity = 0; // (cm/s)
bool start = false;
int buttonPressed = 0;
float maxSpeed; // (cm/ms)

float calRight = 1;
float calLeft = 0.7;

// Stand-in for whatever actually makes the motors move properly
void moveRight(int v) {
  right.write(-v * calRight + 90);
}
void moveLeft(int v) {
  left.write(v * calLeft + 90);
}

void stop() {
  right.write(92);
  left.write(92);
}

// Drives straight a given distance (cm)
void driveFor(int dist) {
  int end = millis() + (dist / (maxSpeed * velocity));
  while (millis() < end) {
    if (dist > 0) {
      moveLeft(velocity * 90);
      moveRight(velocity * 90);
    } else {
      moveLeft(velocity * -90);
      moveRight(velocity * -90);
    }
  }
  remainingDistance -= dist;
}

void driveFor(int dist, int ms) {
  int end = millis() + ms;
  while (millis() < end) {
    moveLeft((((float) dist / ms) / maxSpeed) * 90);
    moveRight((((float) dist / ms) / maxSpeed) * 90);
  }
}

void driveForTime(int ms) {
  int end = millis() + ms;
  while (millis() < end) {
    moveLeft(45);
    moveRight(45);
  }
  stop();
}

// Turns clockwise a given angle (degrees)
void turn(float angle) {
  int end = millis() + (666 * (abs(angle) / 90));
  while (millis() < end) {
    if (angle > 0) {
      moveLeft(10);
      moveRight(-10);
    } else {
      moveLeft(-10);
      moveRight(10);
    }
  }
  stop();
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
  Serial.begin(9600);
  pinMode(2, INPUT);
  right.attach(9);
  left.attach(10);
  delay(5000);
  //turn(-90);
  //driveForTime(1250) = ~50cm
  //turn(90) = ~90d clockwise
  //turn(-60) = ~90d counterclockwise
  delay(5000);
}

void loop() {
  /*buttonPressed = digitalRead(2);
  if (buttonPressed) {
    start = true;
  }
  if (start) {
    Serial.println("started");
  }
  Serial.println(buttonPressed);
  delay(1000);*/
  
}
