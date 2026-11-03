// Arm movement test for one stepper motor (z-axis only)

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *zMotor = AFMS.getStepper(200, 1);  // Stepper motor for z-axis motion, connected to motor port #1

const int zSteps = 50;  // number of steps that the arm will move in the z-axis

int whiskTime = 5000; // amount of time that the whisk will be moving in the x-axis for

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  zMotor->setSpeed(50);  // sets z-axis motor speed to 50 rpm
}

void loop() {
  // moves arm down into bowl
  zMotor->step(zSteps, FORWARD, MICROSTEP);

  delay(whiskTime); // waits for whisk to finish moving in the x-axis before moving it up

  // moves arm up out of bowl
  zMotor->step(zSteps, BACKWARD, MICROSTEP);

  // wait 5 seconds before redoing the loop
  delay(5000);
}
