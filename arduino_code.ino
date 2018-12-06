#include <Servo.h>
#include <Ultrasonic.h>

int robotx = 0;
int roboty = 0;
int pin_servo = 5; //PIN du servomoteur
int degre = 0;
Ultrasonic *capteurs[4];
Servo myservo;

void setup() {  
  myservo.attach(pin_servo); // On démarre le servomoteur
  Serial.begin(9600); // On commence à parler à l'ordi

  Ultrasonic capteur1(1);
  Ultrasonic capteur2(2);
  Ultrasonic capteur3(3);
  Ultrasonic capteur4(4);

  
  capteurs[0] = &capteur1;
  capteurs[1] = &capteur2;
  capteurs[2] = &capteur3;
  capteurs[3] = &capteur4;
/*
  Ultrasonic capteurs[4];
  capteurs[0] = capteur1;
  capteurs[1] = capteur2;
  capteurs[2] = capteur3;
  capteurs[3] = capteur4;*/
}

void loop() {
  envoi_Mesure();

}

void envoi_Mesure() {
  for(int i = 0; i < 4; i++) {
    long RangeInCentimeters; 
    RangeInCentimeters = capteurs[i]->MeasureInCentimeters();   // On fait la mesure
    if(RangeInCentimeters < 516) {    // Le capteur renvoie 517 si il ne détecte rien ou si il beug --> pas d'envoi
      //Serial.println(robotx, ", ", roboty, ", ", degre, ", ", RangeInCentimeters);
      Serial.print(robotx);
    }
  }
  degre += 5;
  myservo.write(degre);
}