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
  Serial.print(robotx);
  Serial.print(", ");
  Serial.print(roboty);
  Serial.print(", ");
  Serial.print(degre);
  Serial.print(", ");
  Serial.println(capteur1.MeasureInCentimeters());
  
  Serial.print(robotx);
  Serial.print(", ");
  Serial.print(roboty);
  Serial.print(", ");
  Serial.print(degre+90);
  Serial.print(", ");
  Serial.println(capteur2.MeasureInCentimeters());
  
  Serial.print(robotx);
  Serial.print(", ");
  Serial.print(roboty);
  Serial.print(", ");
  Serial.print(degre+180);
  Serial.print(", ");
  Serial.println(capteur3.MeasureInCentimeters());
  //Serial.println(capteur4.MeasureInCentimeters());

  if (degre == 180) {
    degre = 0;
  }
  degre += 5;
  myservo.write(degre);
  delay(500);
}