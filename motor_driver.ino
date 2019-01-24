int pinI1 = 8;
int pinI2 = 11;
int moteurA = 9;

int pinI3 = 12;
int pinI4 = 13;
int moteurB = 10;

int tour = 0;
int huitieme = 0;

int vitesse = 42;

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
  analogWrite(moteurA, vitesse);
  digitalWrite(pinI2, LOW);
  digitalWrite(pinI1, HIGH);

  analogWrite(moteurB, vitesse);
  digitalWrite(pinI4, LOW);
  digitalWrite(pinI3, HIGH);
  
  Serial.println(analogRead(1)); //PIN de l'encodeur / 1 tour = 8 trous = 22 cm
}
