#include <Motor/DCMotor.h>

DCMotor::DCMotor(uint8_t motorPin1, uint8_t motorPin2, uint8_t maxSpeed)
    : _motorPin1(motorPin1), _motorPin2(motorPin2), _maxSpeed(maxSpeed) {};

void DCMotor::begin()
{
    pinMode(_motorPin1, OUTPUT);
    pinMode(_motorPin2, OUTPUT);
};

uint8_t DCMotor::setSpeed(uint8_t speed, bool direction = true)
{
    if (speed > _maxSpeed)
    {
        speed = _maxSpeed;
    }

    _current = speed;

    if (direction)
    {
        motorPWM.setPWM(_motorPin1, 0, _current);
        motorPWM.setPWM(_motorPin2, 0, 0);
    }
    else
    {
        motorPWM.setPWM(_motorPin2, 0, _current);
        motorPWM.setPWM(_motorPin1, 0, 0);
    }

    return _current;
};

void DCMotor::stop()
{
    DCMotor::setSpeed(0);
    return;
};

void DCMotor::softStart(u_int8_t startSpeed, u_int8_t endSpeed, bool direction)
{

    u_int8_t currentSpeed = startSpeed;

    for (u_int8_t current_duration = 0; current_duration < SOFT_START_DRURATION; current_duration + SOFT_START_STEP)
    {
        current_duration += SOFT_START_STEP;

        currentSpeed = map(current_duration, 0, SOFT_START_DRURATION, startSpeed, endSpeed);
        DCMotor::setSpeed(currentSpeed, direction);
        delay(10);
    }
    return;
};