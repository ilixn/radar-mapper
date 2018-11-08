#include <Servo.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(7); //Capteur de distance branché sur 7
Servo myservo;
int pos = 0; // Position de la plateforme rotative
int affpos = 0;
int pin_servo = 5; //PIN du servomoteur

void setup() {

	myservo.attach(pin_servo);
	Serial.begin(9600);

}

void loop() {
	
	for (pos = 0; pos <= 180; pos += 5) {	 
		// Rotation 0-180 degrés par pas de 5 degrés
		myservo.write(pos);	// le servo va à la position "pos" 
		delay(150);	// on attend 15ms pour que le servo atteigne la position "pos"

		affpos=pos-90; // Position à envoyer au Raspberry Pi : on passe de 0-180 à -90 - 90
		printDistance(affpos); 
	}
	for (pos = 180; pos >= 0; pos -= 5) {
		// le retour: 180-0 degrés par pas de 5°
		myservo.write(pos);
		delay(150);

		affpos=pos-90;			//Position à envoyer au Raspberry pi
		printDistance(affpos); 
	}
}
 
void printDistance(int pos) { 
	long RangeInCentimeters; 
	RangeInCentimeters = ultrasonic.MeasureInCentimeters(); 	// On fait la mesure
	if(RangeInCentimeters < 516) { 		// Le capteur renvoie 517 si il ne détecte rien ou si il beug --> pas d'envoi
		Serial.print(RangeInCentimeters); //0~400cm 
	}
	Serial.print(" cm, ");
	Serial.print(pos);
	Serial.println(" deg");
	//Exemple: 50 cm, 45 deg
}
