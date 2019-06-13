#include "StepperMotor.h"

StepperMotor::StepperMotor(const int stepsPerRev, const int enPin, const int dirPin, const int pulPin)
{
    this->STEPS_PER_REV = stepsPerRev;
    this->EN_PIN = enPin;
    this->DIR_PIN = dirPin;
    this->PUL_PIN = pulPin;
    StepperMotor::setSpeed(100);
    StepperMotor::setDirection(0);
}

boolean StepperMotor::setup()
{
    pinMode(this->PUL_PIN, OUTPUT);
    pinMode(this->DIR_PIN, OUTPUT);
    pinMode(this->EN_PIN, OUTPUT);

    digitalWrite(this->EN_PIN, LOW);
}

void StepperMotor::setDirection(int direction)
{
    this->direction = direction;
    if (this->direction == 0)
    {
        digitalWrite(this->DIR_PIN, HIGH);
    }
    else if (this->direction == 1)
    {
        digitalWrite(this->DIR_PIN, LOW);
    }
}

boolean StepperMotor::driveSteps(int numberOfSteps)
{
    int finalStep = this->currentStep + numberOfSteps;
    boolean finished = false;

    while (this->currentStep != finalStep)
    {
        digitalWrite(this->PUL_PIN, HIGH);
        delayMicroseconds(this->stepDelay);
        digitalWrite(this->PUL_PIN, LOW);
        delayMicroseconds(this->stepDelay);

        if (this->direction == 0)
        {
            this->currentStep++;
        }
        else if (this->direction == 1)
        {
            this->currentStep--;
        }
    }
    if (this->currentStep == finalStep)
    {
        finished = true;
    }
    return finished;
}

boolean StepperMotor::reset()
{
    int toZero = this->currentStep;
    if (this->currentStep > 0)
    {
        StepperMotor::setDirection(COUNTERCLOCKWISE);
        toZero *= -1;
    }
    else if (this->currentStep < 0)
    {
        StepperMotor::setDirection(CLOCKWISE);
        
    }
    boolean finished = StepperMotor::driveSteps(toZero);
    return finished;
}

void StepperMotor::setSpeed(long speed)
{
    this->stepDelay = 60L * 1000L * 1000L / this->STEPS_PER_REV / speed;
}

int StepperMotor::getCurrentStep()
{
    return this->currentStep;
}