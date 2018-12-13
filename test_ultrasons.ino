#include <Ultrasonic.h>

Ultrasonic capteur1(10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // On commence à parler à l'ordi

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(capteur1.MeasureInCentimeters());
}