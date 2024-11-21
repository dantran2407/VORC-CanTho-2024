// PWM FREQ
#define OSCILLATORFREQUENCY 27000000
#define MOTOR_PWMFREQ 1600
#define SERVO_PWMFREQ 50

// MOTOR SET
#define MOTOR_MAXSPEED 4096
#define MOTOR_HAFTSPEED 2048
#define MOTOR_THIRTSPEED 1366
#define MOTOR_QUARTSPEED 1024
#define MOTOR_NORMALSPEED 3072

//Motor H Bridge: R1-R4
#define MOTOR_R1_CH1 8
#define MOTOR_R1_CH2 9

#define MOTOR_R2_CH1 10
#define MOTOR_R2_CH2 11

#define MOTOR_R3_CH1 12
#define MOTOR_R3_CH2 13

#define MOTOR_R4_CH1 14
#define MOTOR_R4_CH2 15

// SERVO PINOUT: 1-6
#define SERVO_1 7
#define SERVO_2 6
#define SERVO_3 5
#define SERVO_4 4
#define SERVO_5 3
#define SERVO_6 2

// PS2 SPI PINOUT
#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18

// Soft Starter 
#define MAXDUTYCYCLE 255
#define INCREMENT 10
#define DUTYCYCLESTEP 20