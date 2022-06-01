#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

#define word    unsigned short

#define ADAFRUIT_MOTORHAT       0x60

#define PWM_M1_PWM      8
#define PWM_M1_IN2      9
#define PWM_M1_IN1      10

#define PWM_FREQUENCY   1600.0
#define PWM_PRESCALE    0xFE

#define PWM_MODE1       0x00
#define PWM_MODE2       0x01
#define PWM_LED0_ON_L   0x06
#define PWM_LED0_ON_H   0x07
#define PWM_LED0_OFF_L  0x08
#define PWM_LED0_OFF_H  0x09

#define PWM_RESTART     0x80
#define PWM_SLEEP       0x10
#define PWM_ALLCALL     0x01
#define PWM_INVRT       0x10
#define PWM_OUTDRV      0x04

#define PWM_ALL_LED_ON_L        0xFA
#define PWM_ALL_LED_ON_H        0xFB
#define PWM_ALL_LED_OFF_L       0xFC
#define PWM_ALL_LED_OFF_H       0xFD

#define MOTOR_FORWARD   1
#define MOTOR_BACK      2
#define MOTOR_BRAKE     3
#define MOTOR_RELEASE   4

class Moteur
{

public:

word i2c, on, off, pin, value, motor = 1, command, speed, newSpeed, newCommand;

~Moteur(){
}

Moteur(){
	i2c = init();
	initMotor(i2c, motor);
	setSpeed(i2c, motor, 120);
}

void open(){
	runMotor(i2c, motor, MOTOR_BACK);
        sleep(3);
        runMotor(i2c, motor, MOTOR_RELEASE);
	sleep(30);
}

void close(){
	runMotor(i2c, motor, MOTOR_FORWARD);
        sleep(3);
        runMotor(i2c, motor, MOTOR_RELEASE);
	sleep(30);
}

void runMotor(word i2c, word motor, word command){
        word in1 = PWM_M1_IN1;
        word in2 = PWM_M1_IN2;
        switch(command){
                case MOTOR_FORWARD:
                        setPin(i2c, PWM_M1_IN2, 0);
                        setPin(i2c, PWM_M1_IN1, 1);
                        break;
                case MOTOR_BACK:
                        setPin(i2c, PWM_M1_IN1, 0);
                        setPin(i2c, PWM_M1_IN2, 1);
                        break;
                case MOTOR_RELEASE:
                        setPin(i2c, PWM_M1_IN1, 0);
                        setPin(i2c, PWM_M1_IN2, 0);
                        break;
                default:
                        printf("Commande invalide '%d'\n", command);
                        return;
        }
}


private :

void setAllPWM(word i2c, word on, word off){
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_ON_L, on & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_ON_H, on >> 8);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_OFF_L, off & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_OFF_H, off >> 8);
}

void setPWM(word i2c, word pin, word on, word off){
        wiringPiI2CWriteReg8(i2c, PWM_LED0_ON_L + 4 * pin, on & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_ON_H + 4 * pin, on >> 8);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_OFF_L + 4 * pin, off & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_OFF_H + 4 * pin, off >> 8);
}

void setPin(word i2c, word pin, word value){
        if(pin < 0 || pin > 15){
                printf("La broche PWM doit se situer entre 0 et 15 '%d'\n", pin);
                return;
        }

        switch(value){
                case 0:
                        setPWM(i2c, pin, 0, 4096);
                        break;
                case 1:
                        setPWM(i2c, pin, 4096, 0);
                        break;
                default:
                        printf("La valeur de la broche doit être 0 ou 1 '%d'\n", pin);
                        return;
        }
}

void setSpeed(word i2c, word motor, word speed){
        if(speed < 0 || speed > 255){
                printf("La vitesse doit être situé entre 0 et 255 '%d'\n", speed);
                return;
        }

        word pwm = PWM_M1_PWM;
        setPWM(i2c, pwm, 0, speed * 16);
}

word init(){
        //Setup I2C
        word i2c = wiringPiI2CSetup(ADAFRUIT_MOTORHAT);

        //Setup PWM
        setAllPWM(i2c, 0, 0);
        wiringPiI2CWriteReg8(i2c, PWM_MODE2, PWM_OUTDRV);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, PWM_ALLCALL);
        sleep(0.5);
        word mode1 = wiringPiI2CReadReg8(i2c, PWM_MODE1) & ~PWM_SLEEP;
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, mode1);
        sleep(0.5);

        //Set PWM frequency
        word prescale = (int)(25000000.0 / 4096.0 / PWM_FREQUENCY - 1.0);
        word oldmode = wiringPiI2CReadReg8(i2c, PWM_MODE1);
        word newmode = oldmode & 0x7F | 0x10;
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, newmode);
        wiringPiI2CWriteReg8(i2c, PWM_PRESCALE, prescale);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, oldmode);
        sleep(0.5);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, oldmode | 0x80);
	return i2c;
}

void initMotor(word i2c, word motor){
        runMotor(i2c, motor, MOTOR_RELEASE);
        setSpeed(i2c, motor, 150);
        runMotor(i2c, motor, MOTOR_FORWARD);
        runMotor(i2c, motor, MOTOR_RELEASE);
}
};
