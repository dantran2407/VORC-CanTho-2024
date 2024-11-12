#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define OscillatorFrequency 27000000
#define PWMFreq 1600
#define Clock 400000

#define SOFT_START_DRURATION 800

#define SOFT_START_STEP 100
Adafruit_PWMServoDriver motorPWM = Adafruit_PWMServoDriver();

class DCMotor
{
private:
    uint8_t _motorPin1;
    uint8_t _motorPin2;
    uint8_t _current;
    uint8_t _maxSpeed;
    bool _direction;

public:
    DCMotor(uint8_t motorPin1, uint8_t motorPin2, uint8_t maxSpeed);

    void begin();

    uint8_t setSpeed(uint8_t speed, bool isReverse = false);

    void softStart(u_int8_t currentSpeed, u_int8_t speed, bool direction);

    void stop();

    u_int8_t getSpeed();
};
