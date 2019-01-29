int pinI1 = 8;
int pinI2 = 11;
int moteurA = 9; //branché sur OUT1, OUT2

int pinI3 = 12;
int pinI4 = 13;
int moteurB = 10; //branché sur OUT3, OUT4

int tour = 0;
int huitieme = 0;
int high = 0;
int roue = 0;

int vitesse = 55;

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
}

void compter() {
  int encodeur = analogRead(A2); //PIN de l'encodeur / 1 tour = 8 trous = 22 cm
  if (encodeur > 2 && high == 0) {
    huitieme ++;
    if (huitieme == 8) {
      tour ++;
      huitieme = 0;
    }

    //Serial.print(tour);
    high = 1;
  }
  if (encodeur == 0) {
    high = 0;
  }
  if (tour == 46) {
    roue ++;
    tour = 0;
    Serial.println(roue);
  }
}

void avancer(int nb) {
  roue = 0;
  while (roue < nb) {
    moteurs(1, 1);
    compter();
  }
  moteurs(-1, -1);
  delay(80);
  moteurs(0, 0);
  roue = 0;
}

void moteurs(int gauche, int droite) { //Quel moteur faire avancer ?
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
  if (gauche==-1)
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
