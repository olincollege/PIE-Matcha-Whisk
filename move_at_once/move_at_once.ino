// Arm movement test for one stepper motor (z-axis only) + matcha dispenser servo and water solenoid valve

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *zMotor1 = AFMS.getStepper(200, 1);  // Stepper motor for z-axis motion, connected to motor port #1
Adafruit_StepperMotor *zMotor2 = AFMS.getStepper(200, 2); 

Servo matchaServo;  // servo for matcha dispenser

int zSteps = 0;  // number of steps that the arm will move in the z-axis

int whiskTime = 5000;  // amount of time that the whisk will be moving in the x-axis for

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  zMotor1->setSpeed(100);  // sets z-axis motor speed to 50 rpm
  zMotor2->setSpeed(100);
}

void loop() {
  // moves arm down into bowl
  for (zSteps = 0; zSteps <= 75; zSteps++) {
    zMotor1->step(1, BACKWARD, SINGLE);
    zMotor2->step(1, BACKWARD, SINGLE);
  }

  zSteps = 0;

  delay(whiskTime);  // waits for whisk to finish moving in the x-axis before moving it up

  // moves arm up out of bowl
  for (zSteps = 0; zSteps <= 75; zSteps++) {
    zMotor1->step(1, FORWARD, SINGLE);
    zMotor2->step(1, FORWARD, SINGLE);
  }

  zSteps = 0;

  // wait 5 seconds before redoing the loop
  delay(2000);
}
