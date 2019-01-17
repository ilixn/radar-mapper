#include <Servo.h>
#include <Ultrasonic.h>

int robotx = 0;
int roboty = 0; //Position x, y
int orientation = 0; //boussole

int degre = 0; //Servo
int signe = 1;

int pin_servo = 5; //PIN du servomoteur
Servo myservo;

//MOTEURS
int pinI1 = 8;
int pinI2 = 11;
int moteurA = 9; //Devant
int pinI3 = 12;
int pinI4 = 13;
int moteurB = 10; //Derrière
int vitesse = 0;

Ultrasonic capteur1(10);
Ultrasonic capteur2(11);
Ultrasonic capteur3(12);
//Ultrasonic capteur4(13);

void setup() {
  myservo.attach(pin_servo); // On démarre le servomoteur
  myservo.write(0);
  Serial.begin(9600); // On commence à parler à l'ordi
}

void loop() {
  envoi_Mesure(capteur1.MeasureInCentimeters(), 0);
  envoi_Mesure(capteur2.MeasureInCentimeters(), 90);
  envoi_Mesure(capteur3.MeasureInCentimeters(), 180);
  //envoi_Mesure(capteur4.MeasureInCentimeters(), 180);

  degre += 5*signe;

  if (degre == 180 || degre == 0) {
    signe = - signe;
  }
  
  myservo.write(degre);
  delay(200);
}

void envoi_Mesure(int mesure, int decalage) {
  Serial.print(robotx);
  Serial.print(",");
  Serial.print(roboty);
  Serial.print(",");
  Serial.print(degre + decalage);
  Serial.print(",");
  Serial.println(mesure);
}