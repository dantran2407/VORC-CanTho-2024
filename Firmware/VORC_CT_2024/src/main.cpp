#include <Arduino.h>
#include <ServoControl.h>
#include <DCMotor.h>
#include <PS2X_lib.h>
#include <variable.h>

DCMotor::MotorController motorR1 = DCMotor::MotorController(MOTOR_R1_CH1, MOTOR_R1_CH2, 4098);
ServoControl::FreeAngle servo1 = ServoControl::FreeAngle(SERVO_1 ,375, 225);
PS2X ps2x;

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
}


void loop()
{
  ps2x.read_gamepad(0, 0);

  if (ps2x.ButtonPressed(PSB_PAD_UP))
  {
    motorR1.setSpeed(MOTOR_NORMALSPEED, true);
  }

  if (ps2x.ButtonReleased(PSB_PAD_UP))
  {
    motorR1.stop();
  }
  
  
}
