#include <Servo.h>
#include <Ultrasonic.h>

int robotx = 0;
int roboty = 0;
int pin_servo = 5; //PIN du servomoteur
int degre = 0;
Servo myservo;

Ultrasonic capteur1(10);
Ultrasonic capteur2(11);
Ultrasonic capteur3(12);
//Ultrasonic capteur4(13);

void setup() {  
  myservo.attach(pin_servo); // On démarre le servomoteur
  Serial.begin(9600); // On commence à parler à l'ordi
  
}

void loop() {
  envoi_Mesure();

}

void envoi_Mesure() {
  Serial.println(capteur1.MeasureInCentimeters());
  Serial.println(capteur2.MeasureInCentimeters());
  Serial.println(capteur3.MeasureInCentimeters());
  //Serial.println(capteur4.MeasureInCentimeters());

  /*
  for(int i = 0; i < 1; i++) {
    long RangeInCentimeters; 
    //RangeInCentimeters = capteurs[i]->MeasureInCentimeters();   // On fait la mesure
    RangeInCentimeters = capteur1.MeasureInCentimeters();
    if(RangeInCentimeters < 516) {    // Le capteur renvoie 517 si il ne détecte rien ou si il beug --> pas d'envoi
      Serial.println((robotx, ", ", roboty, ", ", degre, ", ", RangeInCentimeters));
      Serial.println(RangeInCentimeters);
    }
  }
  */
  if (degre == 180) {
    degre = 0;
  }
  degre += 5;
  myservo.write(degre);
  delay(500);
}