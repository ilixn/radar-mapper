#include <Servo.h>
#include <Ultrasonic.h>

int robotx = 0, roboty = 0; //Position x, y
int orientation = 0; //boussole: 0-360

//<SERVO
int degre = 5, signe = 1;
int pin_servo = 5; //PIN du servomoteur
Servo myservo;
// SERVO>

//<ULTRASONS
Ultrasonic capteur1(10); //Ultrasons
Ultrasonic capteur2(11);
Ultrasonic capteur3(12);
//Ultrasonic capteur4(13);
// ULTRASONS>

//<MOTEURS
int pinI1 = 8, pinI2 = 11, moteurA = 9; //branché sur OUT1, OUT2
int pinI3 = 12, pinI4 = 13, moteurB = 10; //branché sur OUT3, OUT4

int tour = 0; //Tours de moteur
int huitieme = 0; //huitièmes de tour
int high = 0; //Pour ne pas compter un huitième deux fois
int roue = 0; //Tours de roue

int vitesse = 50;
// MOTEURS>


void setup() {
  //SERVO
  myservo.attach(pin_servo); // On démarre le servomoteur
  myservo.write(0);

  //MOTEURS
  pinMode(pinI1, OUTPUT);
  pinMode(pinI2, OUTPUT);
  pinMode(moteurA, OUTPUT);

  pinMode(pinI3, OUTPUT);
  pinMode(pinI4, OUTPUT);
  pinMode(moteurB, OUTPUT);

  Serial.begin(9600); // On commence à parler à l'ordi
}

void loop() {
  scan();
}

void scan() {
  while(degre != 0) {
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
  degre = 5; //(prochin scan)
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






void compter() {
  int encodeur = analogRead(A2); //PIN de l'encodeur / 1 tour = 8 trous = 22 cm
  if (encodeur > 2 && high == 0) { //On est devant un trou ET on était pas devant un trou avant, sinon on compte le même deux fois :/
    huitieme ++;
    if (huitieme == 8) {
      tour ++; //8 huitièmes --> un tour de moteur
      huitieme = 0;
    }
    
    high = 1; //On note qu'on est devant un trou
  }
  if (encodeur == 0) { // On est pas devant un trou, on met high à 0
    high = 0;
  }
  if (tour == 46) { //Ratio de 1:46 (plus ou moins)
    roue ++;
    tour = 0;
    Serial.println(roue); //Envoie le nombre de tours de roue pour info
  }
}

void reset_compteur() {
  roue = 0;
  huitieme = 0;
  tour = 0;
}

void avancer(int nb) {
  reset_compteur(); //On va compter des tours, on remet à 0
  while (roue < nb) {
    moteurs(1, 1); //On fait avancer  les deux moteurs en même temps
    compter(); //Fonction qui va compter les tours, doit être appelée le plus souvent possible
  }
  moteurs(-1, -1); //Marche arrière pour bloquer
  delay(80);
  moteurs(0, 0);
  reset_compteur();
}

/*
void turn_right() { 
  vitesse = 100;
  int mesure = mesure();
  while (mesure < mesure + 90)
  {
    moteurs(1, -1);
  }
  moteurs(-1, 1);
  delay(80);
  moteurs(0, 0);
}
*/

void turn_left() {
  vitesse = 100;
  int mesure = 0;
  while (mesure < 2) { // pour la boussole mettre >
    moteurs(-1, 1);
    compter();
    mesure = roue; //(Pas pour la boussole)
  }
  moteurs(1, -1);
  delay(80);
  moteurs(0, 0);
  reset_compteur();
}

void moteurs(int gauche, int droite) { //Quel moteur faire avancer ? A REFAIRE
  if (gauche == 1) {
    analogWrite(moteurB, vitesse);
    digitalWrite(pinI4, HIGH);
    digitalWrite(pinI3, LOW);
  }
  if (gauche == 0) {
    analogWrite(moteurB, vitesse);
    digitalWrite(pinI4, LOW);
    digitalWrite(pinI3, LOW);
  }
  if (gauche == -1)
  {
    analogWrite(moteurB, vitesse);
    digitalWrite(pinI4, LOW);
    digitalWrite(pinI3, HIGH);
  }

  if (droite == 1) {
    analogWrite(moteurA, vitesse);
    digitalWrite(pinI2, LOW);
    digitalWrite(pinI1, HIGH);
  }
  if (droite == 0) {
    analogWrite(moteurA, vitesse);
    digitalWrite(pinI2, LOW);
    digitalWrite(pinI1, LOW);
  }
  if (droite == -1) {
    analogWrite(moteurA, vitesse);
    digitalWrite(pinI2, HIGH);
    digitalWrite(pinI1, LOW);
  }
}
