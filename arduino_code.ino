#include <Servo.h>
#include <Ultrasonic.h>

int robotx = 0;
int roboty = 0;
int pin_servo = 5; //PIN du servomoteur
int degre = 0;
int signe = 1;
Servo myservo;

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

  if (degre == 180 || degre == 0) {
    signe = - signe;
  }
  degre += 5*signe;
  myservo.write(degre);
  delay(500);
}

void envoi_Mesure(int mesure, int decalage) {
  Serial.print(robotx);
  Serial.print(", ");
  Serial.print(roboty);
  Serial.print(", ");
  Serial.print(degre + decalage);
  Serial.print(", ");
  Serial.println(mesure);
}