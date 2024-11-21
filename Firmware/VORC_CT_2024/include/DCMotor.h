#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

namespace DCMotor
{
    static Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

    void Initialize();

    class MotorController {
        private:
            int _ch1Pin;
            int _ch2Pin;
            int _currentSpeed;
            int _currentDirection;
            int _maxSpeed;

            void _softStarter(int speed, bool direction);
            void _softStopper();
            void _setPIN(int speed, bool direction);
        public:
            MotorController(int ch1Pin, int ch2Pin, int maxSpeed);
            void setSpeed(int speed, bool direction);
            void stop();
    };
} 
