// On ajoute ici les bibliothèques nécessaires au fonctionnement du programme

#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nous avons ici des redéfinitions de nombres que j'ai trouvé sur internet permettant la traduction entre les commandes du motorhat adafruit et notre programme en C++//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define word    unsigned short // unsigned short est renommé word pour aller plus vite

#define ADAFRUIT_MOTORHAT       0x60 // On parle ici du module ADAFRUIT MOTORHAT, la carte puissance permettant le contrôle du moteur

// On parle ici des broches lié au moteur dans le cas ou il est branché (ce qui est le cas ici) sur le port M1

#define PWM_M1_PWM      8
#define PWM_M1_IN2      9
#define PWM_M1_IN1      10

// On parle ici des valeurs de pré configuration du moteur, j'ai trouvé sur internet des méthodes permettant cette configuration, on ne modifiera pas ce code

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

// On parle ici des instructions données au moteur

#define MOTOR_FORWARD   1
#define MOTOR_BACK      2
#define MOTOR_BRAKE     3
#define MOTOR_RELEASE   4

// Création de la classe Moteur 

class Moteur
{

	// Création des méthodes publics

	public:
	
	// Constructeur de la classe 
	
	Moteur(){
		// Les méthodes init() et initMotor() permettent le démarrage du programme et du moteur, ces méthodes ont été trouvées sur internet et ne sont pas retouchées
		
		i2c = init();
		initMotor(i2c, motor);
		
		// On met la vitesse de base du moteur avec setSpeed
		
		setSpeed(i2c, motor, 120);
	}

	// Méthode permettant l'ouverture de la fenêtre
	// La méthode runMotor permet le changement de sens du moteur
	
	void open(){
		runMotor(i2c, motor, MOTOR_BACK);
		sleep(3);
		runMotor(i2c, motor, MOTOR_RELEASE);
		sleep(30);
	}

	// Méthode permettant la fermeture de la fenêtre
	
	void close(){
		runMotor(i2c, motor, MOTOR_FORWARD);
		sleep(3);
		runMotor(i2c, motor, MOTOR_RELEASE);
		sleep(30);
	}
	
	// Méthode permettant le changement de sens d'un moteur, ici nous avons un seul moteur donc on aura toujours la même chose pour motor, mais dans un futur ou on ajoute des moteurs pour plusieurs fenêtre, on laisse cette option dans la méthode

	void runMotor(word i2c, word motor, word command){
		
		// On définit les broches lié au moteur
		
		word in1 = PWM_M1_IN1;
		word in2 = PWM_M1_IN2;
		
		// Switch permettant le changement de sens du moteur en fonction de l'instruction reçue
		
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
	
	// Destructeur de la classe
	
	~Moteur(){
	}

	private :
	
	// Variables nécessaires au méthodes de la classe Moteur

	word i2c, on, off, pin, value, motor = 1, command, speed, newSpeed, newCommand;

	// 3 méthodes trouvées sur internet permettant l'initialisation des pins sur le motorhat en liaison I2C
	
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

		// Ce switch permet la mise à 0 ou à 1 d'une broche
		
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

	// Cette méthode permet le changement de vitesse, on peut inscrire une valeur entre 0 et 255 qui permet de modifier la vitesse du moteur
	
	void setSpeed(word i2c, word motor, word speed){
		if(speed < 0 || speed > 255){
			printf("La vitesse doit être situé entre 0 et 255 '%d'\n", speed);
			return;
		}

		word pwm = PWM_M1_PWM;
		setPWM(i2c, pwm, 0, speed * 16);
	}

	// 2 méthodes trouvées qui permettent l'initialisation du moteur avec sa carte puissance adafruit
	
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
