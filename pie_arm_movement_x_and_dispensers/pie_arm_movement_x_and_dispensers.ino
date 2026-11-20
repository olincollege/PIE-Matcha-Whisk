// Arm movement test for x-axis stepper motor + water and matcha dispensers

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *xMotor = AFMS.getStepper(200, 1);  // Stepper motor for x-axis motion, connected to motor port #1

Servo matchaServo;  // servo for matcha dispenser

int solenoidPin = 8;  // solenoid valve will be connected to pin D8

int matchaPos = 0;    // stores matcha dispenser position
int matchaMax = 180;  // stores maximum position that matcha dispenser will reach

const int xSteps = 25;  // number of steps that the arm will move in the x-axis

const int whiskCountMax = 5;  // maximum amount of times the whisk will move back and forth
int whiskCount = 0;           // amount of times the whisk has gone back and forth

const int dispenseTime = 5000;  // amount of time that the dispensers will take before arm movement sequence starts
const int waterTime = 1000;  // amount of time that water will dispense for
const int zTime = 5000; // amount of time the arm takes to move up and down 

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  xMotor->setSpeed(50);  // sets z-axis motor speed to 50 rpm

  pinMode(solenoidPin, OUTPUT);    // sets solenoid pin as an output
  digitalWrite(solenoidPin, LOW);  // ensures solenoid valve starts as closed

  matchaServo.attach(9);  // matcha dispenser servo connects to pin D9
}

void loop() {
  // matcha dispenser opens
  for (matchaPos = 0; matchaPos <= matchaMax; matchaPos += 1) {
    matchaServo.write(matchaPos);
    delay(7);
  }

  // matcha dispenser closes
  for (matchaPos = matchaMax; matchaPos >= 0; matchaPos -= 1) {
    matchaServo.write(matchaPos);
    delay(7);
  }

  // waits 2 seconds before water dispenser sequence starts
  delay(2000);

  // water valve opens
  digitalWrite(solenoidPin, HIGH);

  // valve stays open for amount of time we want water to flow for
  delay(waterTime);

  // water valve closes
  digitalWrite(solenoidPin, LOW);

  // waits until arm fully moves up
  delay(zTime);

  // whisks back and forth a given amount of times
  while (whiskCount <= whiskCountMax) {
    xMotor->step(xSteps, FORWARD, SINGLE);
    xMotor->step(xSteps, BACKWARD, SINGLE);
    whiskCount++;
  }

  // waits until arm fully moves down
  delay(zTime);

  // wait 5 seconds before redoing the loop
  delay(5000);
}
