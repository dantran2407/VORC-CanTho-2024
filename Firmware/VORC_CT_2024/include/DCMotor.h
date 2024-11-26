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

            void _softStarter(int speed, bool direction, void (*func)(int, bool));
            void _softStopper(void (*func)(int, bool));
        public:
            MotorController(int ch1Pin, int ch2Pin, int maxSpeed);
            void setPIN(int speed, bool direction);
            void setSpeed(int speed, bool direction, void (*func)(int, bool));
            void stop(void (*func)(int, bool));
    };
} 
