#include "StepperMotor.h"

/*
    StepperMotor constructor. Will set speed to 100 RPM
    and direction to CLOCKWISE if no other statement are
    done later in the setup.

    @param stepsPerRev - Number of steps for one revolution
    @param enPin - EN or ENA (+)pin
    @param dirPin - DIR (+)pin
    @param pulPin - PUL / PULSE / STEP (+)pin
*/
StepperMotor::StepperMotor(const int stepsPerRev, const int enPin, const int dirPin, const int pulPin)
{
    this->STEPS_PER_REV = stepsPerRev;
    this->EN_PIN = enPin;
    this->DIR_PIN = dirPin;
    this->PUL_PIN = pulPin;
    StepperMotor::setSpeed(100);
    StepperMotor::setDirection(0);
}

/*
    Initializing the steppermotor with the given
    pins in the constructor.
*/
boolean StepperMotor::setup()
{
    pinMode(this->PUL_PIN, OUTPUT);
    pinMode(this->DIR_PIN, OUTPUT);
    pinMode(this->EN_PIN, OUTPUT);

    digitalWrite(this->EN_PIN, LOW);
}

/*
    Set the direction of the steppermotor.
    Direction can either CLOCKWISE or
    COUNTERCLOCKWISE.

    @param direction - CLOCKWISE or COUNTERCLOCKWISE (0 / 1)
*/
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

/*
    Drive the steppermotor to the assigned step.
    A negative value will change the motorcontroller
    direction to COUNTERCLOCKWISE automatically.

    @pram numberOfSteps - Number of steps to be done

    @return finished - True when done, else False
*/
boolean StepperMotor::driveSteps(int numberOfSteps)
{
    int finalStep = this->currentStep + numberOfSteps;
    boolean finished = false;

    if (numberOfSteps > 0)
    {
        StepperMotor::setDirection(COUNTERCLOCKWISE);
    }
    else if (numberOfSteps < 0)
    {
        StepperMotor::setDirection(CLOCKWISE);
    }

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

/*
    Runs the stepper motor to the home position.
    If home position is not specified, it will
    return to 0 steps.

    @return finished - True when done, else False
*/
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
    boolean finished = StepperMotor::driveSteps(this->homePosition);
    return finished;
}

/*
    Set the steppermotor rotation speed,
    in RPM (Rounds Per Minute).

    @param speed - The new speed in RPM
*/
void StepperMotor::setSpeed(long speed)
{
    this->stepDelay = 60L * 1000L * 1000L / this->STEPS_PER_REV / speed;
}

/*
    Set the new home position of the steppermotor.
    This position will be driven to if reset-method 
    is to be called.

    @param homePosition - New reset position 
*/
void StepperMotor::setHomePosition(int homePosition)
{
    this->homePosition = homePosition;
}

/*
    Returns the current step.

    @ return currentStep - Current step
*/
int StepperMotor::getCurrentStep()
{
    return this->currentStep;
}
