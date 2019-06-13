#ifndef _StepperMotor_H_
#define _StepperMotor_H_

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class StepperMotor
{

public:
//Defining Constants
#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

    // Defining Functions
    StepperMotor(const int stepsPerRev, const int enPin, const int dirPin, const int pulPin);
    boolean setup();
    void setStepDelay(unsigned long stepDelay);
    void setDirection(int direction);
    void setSpeed(long speed);
    void setHomePosition(int homePosition);
    boolean driveSteps(int numberOfSteps);
    int getCurrentStep(void);
    boolean reset(void);

private:
    // Defining varibales
    int STEPS_PER_REV;
    int EN_PIN;
    int DIR_PIN;
    int PUL_PIN;
    int currentStep;
    int direction;
    int homePosition = 0;
    unsigned long stepDelay;
};

#endif // _StepperMotor_H_
