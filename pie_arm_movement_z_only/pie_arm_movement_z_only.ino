// Arm movement test for one stepper motor (z-axis only) + matcha dispenser servo and water solenoid valve 

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *zMotor = AFMS.getStepper(200, 1);  // Stepper motor for z-axis motion, connected to motor port #1

Servo matchaServo;  // servo for matcha dispenser

const int zSteps = 50;  // number of steps that the arm will move in the z-axis

int solenoidPin = 8;  // solenoid valve will be connected to pin D8

int matchaPos = 0;    // stores matcha dispenser position
int matchaMax = 180;  // stores maximum position that matcha dispenser will reach

int waterTime = 1000;  // amount of time that water will dispense for
int whiskTime = 5000;  // amount of time that the whisk will be moving in the x-axis for

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  zMotor->setSpeed(50);  // sets z-axis motor speed to 50 rpm

  pinMode(solenoidPin, OUTPUT);    // sets solenoid pin as an output
  digitalWrite(solenoidPin, LOW);  // ensures solenoid valve starts as closed

  matchaServo.attach(9);  // matcha dispenser servo connects to pin D9
}

void loop() {
  // matcha dispenser opens
  for (matchaPos = 0; matchaPos <= matchaMax; matchaPos += 1) {
    matchaServo.write(matchaPos);
    delay(15);
  }

  // matcha dispenser closes
  for (matchaPos = matchaMax; matchaPos >= 0; matchaPos -= 1) {
    matchaServo.write(matchaPos);
    delay(15);
  }

  // waits 2 seconds before water dispenser sequence starts
  delay(2000);

  // water valve opens
  digitalWrite(solenoidPin, HIGH);

  // valve stays open for amount of time we want water to flow for
  delay(waterTime);

  // water valve closes
  digitalWrite(solenoidPin, LOW);

  // waits 2 seconds before the arm starts moving
  delay(2000);

  // moves arm down into bowl
  zMotor->step(zSteps, FORWARD, MICROSTEP);

  delay(whiskTime);  // waits for whisk to finish moving in the x-axis before moving it up

  // moves arm up out of bowl
  zMotor->step(zSteps, BACKWARD, MICROSTEP);

  // wait 5 seconds before redoing the loop
  delay(5000);
}
