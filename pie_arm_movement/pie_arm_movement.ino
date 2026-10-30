// Arm movement test based on the circuit schematic with 2 servos

#include <Servo.h>

Servo xServo;  // servo for x-axis movement
Servo zServo;  // servo for z-axis movement

int xPos = 0;  // stores x-axis servo position
int zPos = 0;  // stores z-axis servo position

int xMax = 180;  // stores maximum x-axis position
int zMax = 180;  // stores maximum z-axis position

int maxWhiskTime = 15000;    // stores maximum amount of time we want to whisk for
uint32_t whiskTime = 0;  // stores amount of time we have been whisking for

void setup() {
  xServo.attach(9);   // x-axis servo connects to pin D9
  zServo.attach(10);  // z-axis servo connects to pin D10
}

// loops infinitely with no consideration for dispensers or bowl changes, just for testing
void loop() {
  // moves arm down into bowl
  for (zPos = 0; zPos <= zMax; zPos += 1) {
    zServo.write(zPos);
    delay(15);
  }

  // starts keeping track of how long we have been whisking for
  whiskTime = millis();

  // whisks back and forth for a set amount of time
  for (whiskTime <= maxWhiskTime) {
    // moves whisk in one direction
    for (xPos = 0; xPos <= xMax; xPos += 1) {
      xServo.write(xPos);
      delay(15);
    }

    // moves whisk in opposite direction
    for (xPos = xMax; xPos >= 0; xPos -= 1) {
      xServo.write(xPos);
      delay(15);
    }
  }

  // sets whisk back to default x-axis position if it ended somewhere else
  if (xPos != 0) {
    for (xPos = xServo.read(); xPos >= 0; xPos -= 1) {
      xServo.write(xPos);
      delay(15);
    }
  }

  // raises arm out of bowl
  for (zPos = zMax; zPos >= 0; zPos -= 1) {
    zServo.write(zPos);
    delay(15);
  }

  delay(5000);  // 5 second delay till redoing the loop
}
