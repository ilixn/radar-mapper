int pinI1 = 8;
int pinI2 = 11;
int moteurA = 9; //branché sur OUT1, OUT2

int pinI3 = 12;
int pinI4 = 13;
int moteurB = 10; //branché sur OUT3, OUT4

int tour = 0; //Tours de moteur
int huitieme = 0; //huitièmes de tour
int high = 0; //Pour ne pas compter un huitième deux fois
int roue = 0; //Tours de roue

int vitesse = 50;

void setup()
{
  pinMode(pinI1, OUTPUT);
  pinMode(pinI2, OUTPUT);
  pinMode(moteurA, OUTPUT);

  pinMode(pinI3, OUTPUT);
  pinMode(pinI4, OUTPUT);
  pinMode(moteurB, OUTPUT);

  Serial.begin(9600);
}

void loop ()
{
  avancer(10);
  delay(1000);
  turn_left();
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
    mesure = roue;
  }
  moteurs(1, -1);
  delay(80);
  moteurs(0, 0);
  roue = 0;
  tour = 0;
  huitieme = 0;
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
