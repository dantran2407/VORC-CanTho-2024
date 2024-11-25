#include <DCMotor.h>
#include <variable.h>

using namespace DCMotor;

bool isInverted = true;

void DCMotor::Initialize()
{
    driver.begin();
    driver.setOscillatorFrequency(OSCILLATORFREQUENCY);
    driver.setPWMFreq(MOTOR_PWMFREQ);
}

MotorController::MotorController(int CH1, int CH2, int maxSpeed) : _ch1Pin(CH1),
                                                                   _ch2Pin(CH2),
                                                                   _maxSpeed(maxSpeed)
{
    _currentSpeed = 0;
    _currentDirection = true;
};

void MotorController::setPIN(int speed, bool direction)
{
    if (direction)
    {
        driver.setPin(_ch1Pin, speed, isInverted);
        driver.setPin(_ch2Pin, 0, isInverted);
    }
    else
    {
        driver.setPin(_ch1Pin, 0, isInverted);
        driver.setPin(_ch2Pin, speed, isInverted);
    }
}

void MotorController::_softStarter(int speed, bool direction, void (*func)(int, bool))
{
    int tSpeed = 0;

    for (int dutyCycle = 0; dutyCycle <= MAXDUTYCYCLE; dutyCycle += INCREMENT)
    {
        tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, _currentSpeed, speed);
        func(tSpeed, direction);
        delay(DUTYCYCLESTEP);
    }

    _currentSpeed = speed;
    _currentDirection = direction;
}

void MotorController::_softStopper(void (*func)(int, bool))
{
    int tSpeed = 0;

    for (int dutyCycle = MAXDUTYCYCLE; dutyCycle >= 0; dutyCycle -= INCREMENT)
    {
        tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, 0, _currentSpeed);
        func(tSpeed, _currentDirection);
        delay(DUTYCYCLESTEP);
    }

    setPIN(0, _currentDirection);

    _currentSpeed = 0;
    _currentDirection = true;
}

void MotorController::setSpeed(int speed, bool direction, void (*func)(int, bool))
{
    if (
        _currentSpeed == 0 || 
        _currentSpeed != speed && 
        _currentDirection != direction
    ){
        _softStarter(speed, direction, func);
    } else {
        setPIN(_currentSpeed, _currentDirection);
    }
}


void MotorController::stop(void (*func)(int, bool)) {
    _softStopper(func);
}