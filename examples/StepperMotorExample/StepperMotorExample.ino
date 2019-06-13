#include "StepperMotor.h"

const int STEPS_PER_REV = 400;
const int STEP_PIN = 5;
const int DIR_PIN = 2;
const int EN_PIN = 8;
boolean completed = false;
StepperMotor stepperMotor(STEPS_PER_REV, EN_PIN, DIR_PIN, STEP_PIN);


void setup() {
  stepperMotor.setup();
  stepperMotor.setSpeed(500);
  stepperMotor.setDirection(CLOCKWISE);
}

void loop() {
  stepperMotor.driveSteps(4000);
  completed = stepperMotor.reset();
  if (completed) {
    for (;;) {};
  }

}
