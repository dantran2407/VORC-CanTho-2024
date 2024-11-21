#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

namespace ServoControl
{
    static Adafruit_PWMServoDriver _driver = Adafruit_PWMServoDriver();

    void initialize();

    class FreeAngle
    {
    private:
        Adafruit_PWMServoDriver _pwmDriver;
        int _channel;
        int _neutralPulse;
        int _rangePulse;

    public:
        FreeAngle(int channel, int neutralPulse, int rangePulse);
        void setSpeed(float speed);
    };

    class FixedAngle
    {
    private:
        Adafruit_PWMServoDriver *_pwmDriver;
        int _channel;
        int _minPulse;
        int _maxPulse;

    public:
        FixedAngle(int channel, int minPulse, int maxPulse);
        void setAngle(float angle);
    };
}
