#include <DCMotor.h>
#include <variable.h>
#include <Arduino.h>

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

// void MotorController::_softStarter(int speed, bool direction, void (*func)(int, bool))
// {
//     int tSpeed = 0;

//     for (int dutyCycle = 0; dutyCycle <= MAXDUTYCYCLE; dutyCycle += INCREMENT)
//     {
//         tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, _currentSpeed, speed);
//         func(tSpeed, direction);
//         delay(DUTYCYCLESTEP);
//     }

//     _currentSpeed = speed;
//     _currentDirection = direction;
// }

/* UPDATE NEW TIMER - SOFT STARTER USING MILLIS AND YIELD */
void MotorController::_softStarter(int speed, bool direction, void (*func)(int, bool)) {
    unsigned long previousMillis = millis();  // Store the current time
    int tSpeed = 0;

    for (unsigned int dutyCycle = 0; dutyCycle <= MAXDUTYCYCLE; dutyCycle += INCREMENT) {
        while (millis() - previousMillis < DUTYCYCLESTEP) {
            yield();  // Allow other tasks to run
        }

        previousMillis += DUTYCYCLESTEP;  // Update for the next cycle

        // Calculate speed based on duty cycle
        tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, _currentSpeed, speed);
        
        // Call the provided function pointer to set motor speed
        func(tSpeed, direction);
    }

    // Update the motor's current state
    _currentSpeed = speed;
    _currentDirection = direction;
}

// void MotorController::_softStopper(void (*func)(int, bool))
// {
//     int tSpeed = 0;

//     for (int dutyCycle = MAXDUTYCYCLE; dutyCycle >= 0; dutyCycle -= INCREMENT)
//     {
//         tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, 0, _currentSpeed);
//         func(tSpeed, _currentDirection);
//         delay(DUTYCYCLESTEP);
//     }

//     func(0, _currentDirection);

//     _currentSpeed = 0;
//     _currentDirection = true;
// }

/* UPDATE NEW TIMER - SOFT STOPPER USING MILLIS AND YIELD*/
void MotorController::_softStopper(void (*func)(int, bool)) {
    unsigned long previousMillis = millis();  // Store the current time
    int tSpeed = 0;

    // Loop to gradually decrease speed from current to zero
    for (unsigned int dutyCycle = MAXDUTYCYCLE; dutyCycle > 0; dutyCycle -= INCREMENT) {
        if (millis() - previousMillis >= DUTYCYCLESTEP) {
            previousMillis += DUTYCYCLESTEP;  // Move to the next interval

            // Calculate speed based on duty cycle
            tSpeed = map(dutyCycle, 0, MAXDUTYCYCLE, 0, _currentSpeed);
            
            // Call the provided function pointer to set motor speed
            func(tSpeed, _currentDirection);
        }
        yield();  // Allow other tasks to run
    }

    // Ensure motor is completely stopped at the end
    func(0, _currentDirection);

    // Update the motor's state
    _currentSpeed = 0;
    _currentDirection = true;  // Default direction (optional)
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