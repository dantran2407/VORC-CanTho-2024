#include <DCMotor.h>

DCMotor::DCMotor(uint8_t ch1Pin, uint8_t ch2Pin, uint8_t maxSpeed)
    : _ch1Pin(ch1Pin), _ch2Pin(ch2Pin), _maxSpeed(maxSpeed) {};

void DCMotor::begin()
{
    pinMode(_ch1Pin, OUTPUT);
    pinMode(_ch2Pin, OUTPUT);

    Wire.begin();
    motorPWM.begin();
    motorPWM.setOscillatorFrequency(OscillatorFrequency);
    motorPWM.setPWMFreq(PWMFreq);
    Wire.setClock(Clock);
};

uint8_t DCMotor::setSpeed(uint8_t speed)
{
    if (speed > _maxSpeed)
    {
        speed = _maxSpeed;
    }

    _speed = speed;

    return _speed;
};

void DCMotor::stop()
{
    DCMotor::setSpeed(0);
    DCMotor::start();
    return;
};

void DCMotor::start(uint8_t speed, bool isBackward)
{
    if (speed == 0)
        speed = _speed;
    else 
        _speed = speed;

    if (!isBackward)
    {
        motorPWM.setPWM(_ch1Pin, 0, speed);
        motorPWM.setPWM(_ch2Pin, 0, 0);
    }

    motorPWM.setPWM(_ch1Pin, 0, 0);
    motorPWM.setPWM(_ch2Pin, 0, speed);
};

void DCMotor::softStart(bool isBackward)
{
    uint8_t speed = 0;

    for (uint8_t current_duration = 0; current_duration < SOFT_START_DRURATION;)
    {
        current_duration += SOFT_START_STEP;
        speed = map(current_duration, 0, SOFT_START_DRURATION, 0, DCMotor::getSpeed());
        start();
        delay(10);
    }
    return;
};