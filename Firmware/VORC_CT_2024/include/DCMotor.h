#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define OscillatorFrequency 27000000
#define PWMFreq 1600
#define Clock 400000

#define SOFT_START_DRURATION 800

#define SOFT_START_STEP 100
Adafruit_PWMServoDriver motorPWM = Adafruit_PWMServoDriver();

class DCMotor
{
private:
    uint8_t _ch1Pin;
    uint8_t _ch2Pin;
    static uint8_t _speed;
    uint8_t _maxSpeed;
    bool _direction;

public:
    DCMotor(uint8_t ch1Pin, uint8_t ch2Pin, uint8_t maxSpeed);

    void begin();

    uint8_t setSpeed(uint8_t speed);

    void start(uint8_t speed = 0, bool isBackward = false);

    void softStart(bool isBackward = false);

    void stop();

    void softStop();

    u_int8_t getSpeed();
};
