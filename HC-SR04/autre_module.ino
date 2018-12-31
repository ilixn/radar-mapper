// Sketch pour un seul module HC-SRO4

#include <NewPing.h>
#include <Servo.h> 

#define SERVO_PIN 7
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;
int degre = 0;
int signe = 1;
 
void setup() {
   Serial.begin(9600);
   servo.attach(SERVO_PIN);
   servo.write(0);
}
 
void loop() {
   delay(200);
   unsigned int distance = sonar.ping_cm();
   if(distance > 3) {
    Serial.print("0,0,");
    Serial.print(degre);
    Serial.print(",");
    Serial.println(distance);
   }
   servo.write(degre);
   degre = degre + signe*2;
   if(degre==180 || degre==0) {
    signe = - signe;
   }
}
