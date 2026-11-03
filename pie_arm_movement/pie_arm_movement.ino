// Arm movement test for two stepper motors

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *xMotor = AFMS.getStepper(200, 1);  // Stepper motor for x-axis motion, connected to motor port #1
Adafruit_StepperMotor *zMotor = AFMS.getStepper(200, 2);  // Stepper motor for z-axis motion, connected to motor port #2

const int zSteps = 50;  // number of steps that the arm will move in the z-axis
const int xSteps = 25;  // number of steps that the arm will move in the x-axis

const int whiskCountMax = 5;  // maximum amount of times the whisk will move back and forth
int whiskCount = 0;           // amount of times the whisk has gone back and forth

int dispenseTime = 5000;  // amount of time that the dispensers will take before arm movement sequence starts

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  xMotor->setSpeed(10);  // sets x-axis motor speed to 10 rpm
  zMotor->setSpeed(50);  // sets z-axis motor speed to 50 rpm
}

void loop() {
  // waits for dispensers to finish their sequences before arm starts moving
  delay(dispenseTime);

  // moves arm down into bowl
  zMotor->step(zSteps, FORWARD, MICROSTEP);

  // whisks back and forth a given amount of times
  while (whiskCount <= whiskCountMax) {
    xMotor->step(xSteps, FORWARD, MICROSTEP);
    xMotor->step(xSteps, BACKWARD, MICROSTEP);
    whiskCount++;
  }

  // moves arm up out of bowl
  zMotor->step(zSteps, BACKWARD, MICROSTEP);

  // wait 5 seconds before redoing the loop
  delay(5000);
}