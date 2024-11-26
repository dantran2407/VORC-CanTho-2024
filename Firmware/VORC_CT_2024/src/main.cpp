#include <Arduino.h>
#include <ServoControl.h>
#include <DCMotor.h>
#include <PS2X_lib.h>
#include <variable.h>
#include <Adafruit_PWMServoDriver.h>

#define Y_JOY_CALIB 128

DCMotor::MotorController motorR1 = DCMotor::MotorController(MOTOR_R1_CH1, MOTOR_R1_CH2, 4095);
DCMotor::MotorController motorR2 = DCMotor::MotorController(MOTOR_R2_CH1, MOTOR_R2_CH2, 4095);
DCMotor::MotorController motorR4 = DCMotor::MotorController(MOTOR_R4_CH1, MOTOR_R4_CH2, 4095);
ServoControl::FixedAngle servo1 = ServoControl::FixedAngle(SERVO_1, 205, 410);
ServoControl::FixedAngle servo2 = ServoControl::FixedAngle(SERVO_2, 205, 410);
PS2X ps2x;

Adafruit_PWMServoDriver motor = Adafruit_PWMServoDriver();

bool inTakeState = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing servo");
    DCMotor::Initialize();
    ServoControl::initialize();

    int err = -1;
    while (err != 0)
    {
        err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
    }

    servo1.setAngle(0);
}

void moveUp(int speed, bool direction)
{
    motorR1.setPIN(speed, direction);
    motorR2.setPIN(speed, direction);
}

void change(int speed, bool direction)
{
    motorR1.setPIN(speed, direction);
    motorR2.setPIN(speed, !direction);
}

void inTake(int speed, bool direction)
{
    motorR4.setPIN(speed, direction);
}

void loop()
{
    ps2x.read_gamepad(0, 0);

    if (ps2x.ButtonPressed(PSB_GREEN))
    {
        servo1.setAngle(90);
    }
    else if (ps2x.ButtonReleased(PSB_GREEN))
    {
        servo1.setAngle(0);
    }

    if (ps2x.ButtonPressed(PSB_BLUE))
    {
        servo2.setAngle(90);
    }
    else if (ps2x.ButtonReleased(PSB_BLUE))
    {
        servo2.setAngle(0);
    }

    if (ps2x.ButtonPressed(PSB_RED))// Is OFF
    {
        inTakeState = !inTakeState;

        if (inTakeState)
        {
            motorR4.setSpeed(MOTOR_MAXSPEED, true, inTake);
        } else motorR4.stop(inTake);
    }
    delay(100);
}
