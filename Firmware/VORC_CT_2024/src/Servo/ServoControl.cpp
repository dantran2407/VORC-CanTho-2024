#include <ServoControl.h>
#include <variable.h>

using namespace ServoControl;

void ServoControl::initialize()
{
    _driver.begin();
    _driver.setOscillatorFrequency(OSCILLATORFREQUENCY);
    _driver.setPWMFreq(SERVO_PWMFREQ);
}

FreeAngle::FreeAngle(int channel, int neutralPulse, int rangePulse) : 
    _channel(channel),
    _neutralPulse(neutralPulse), 
    _rangePulse(rangePulse) 
{};

void FreeAngle::setSpeed(float speed)
{
    if (speed < -1)
        speed = -1;
    if (speed > 1)
        speed = 1;

    int pulseLength = _neutralPulse + speed * _rangePulse;
    _driver.setPWM(_channel, 0, pulseLength);
};

FixedAngle::FixedAngle(int channel, int minPulse, int maxPulse): 
    _channel(channel), 
    _minPulse(minPulse),
    _maxPulse(maxPulse)
{};

void FixedAngle::setAngle(float angle)
{
    if (angle < 0)
        angle = 0;
    if (angle > 180)
        angle = 180;

    int pulseLength = _minPulse + (angle / 180.0) * (_maxPulse - _minPulse);
    _driver.setPWM(_channel, 0, pulseLength*1.62);
}