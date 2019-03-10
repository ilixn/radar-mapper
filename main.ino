#include <Servo.h>
#include <Ultrasonic.h>
#include <Arduino.h>
#include <Wire.h>
// Compass
#include "bmm150.h"
#include "bmm150_defs.h"
#include "MotorDriver.h"


//<COMPASS
BMM150 bmm = BMM150();
bmm150_mag_data value_offset;
// COMPASS>

int robotx = 0, roboty = 0; //Position x, y

//<SERVO
int degre = 5, signe = 1;
int pin_servo = 8; //PIN du servomoteur
Servo myservo;
// SERVO>

//<ULTRASONS
Ultrasonic capteur1(4); //Ultrasons
Ultrasonic capteur2(2);
Ultrasonic capteur3(3);
//Ultrasonic capteur4(13);
// ULTRASONS>

//<MOTEURS
MotorDriver motor;

int tour = 0; //Tours de moteur
int huitieme = 0; //huitièmes de tour
int high = 0; //Pour ne pas compter un huitième deux fois
int roue = 0; //Tours de roue

int vitesse = 90;
// MOTEURS>


void setup() {
  //SERVO
  myservo.attach(pin_servo); // On démarre le servomoteur
  myservo.write(0);

  //MOTEURS
  motor.begin();

  Serial.begin(9600); // On commence à parler à l'ordi

  //BOUSSOLE
  init_compass();

  delay(2000);
  mesure_depart = mesure_compass();
}

void loop() {
  scan();
  delay(1000);
}

//Scanne la pièce en aller-retour
void scan() {
  while (degre != 0) {
    capteur1.MeasureInCentimeters();
    capteur2.MeasureInCentimeters();
    capteur3.MeasureInCentimeters();
    envoi_Mesure(capteur1.RangeInCentimeters, 0);
    envoi_Mesure(capteur2.RangeInCentimeters, 90);
    envoi_Mesure(capteur3.RangeInCentimeters, 180);

    degre += 5 * signe;

    if (degre == 180 || degre == 0) {
      signe = - signe;
    }

    myservo.write(degre);
    delay(200);
  }
  degre = 5;
  myservo.write(degre);
}

// Envoie la mesure à l'ordi en convertissant les degrés dans le sens trigonométrique.
// TODO: intégrer la boussole
void envoi_Mesure(int mesure, int decalage) {
  Serial.print(robotx);
  Serial.print(",");
  Serial.print(roboty);
  Serial.print(",");
  int degre_trigo = 90 - degre + decalage;
  if(degre_trigo < 0) {
    degre_trigo = 360 + degre_trigo;
  }
  Serial.print(degre_trigo);
  Serial.print(",");
  Serial.println(mesure);
}








void init_compass() {
  if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while (1);
  } else {
    Serial.println("Initialize done!");
  }

  Serial.println("Start figure-8 calibration after 2 seconds.");
  delay(2000);
  calibrate(15000);
  Serial.print("\n\rCalibrate done..");
}

/**
   @brief Do figure-8 calibration for a limited time to get offset values of x/y/z axis.
   @param timeout - seconds of calibration period.
*/
void calibrate(uint32_t timeout)
{
  int16_t value_x_min = 0;
  int16_t value_x_max = 0;
  int16_t value_y_min = 0;
  int16_t value_y_max = 0;
  int16_t value_z_min = 0;
  int16_t value_z_max = 0;
  uint32_t timeStart = 0;

  bmm.read_mag_data();
  value_x_min = bmm.raw_mag_data.raw_datax;
  value_x_max = bmm.raw_mag_data.raw_datax;
  value_y_min = bmm.raw_mag_data.raw_datay;
  value_y_max = bmm.raw_mag_data.raw_datay;
  value_z_min = bmm.raw_mag_data.raw_dataz;
  value_z_max = bmm.raw_mag_data.raw_dataz;
  delay(100);

  timeStart = millis();

  while ((millis() - timeStart) < timeout)
  {
    bmm.read_mag_data();

    /* Update x-Axis max/min value */
    if (value_x_min > bmm.raw_mag_data.raw_datax)
    {
      value_x_min = bmm.raw_mag_data.raw_datax;
      // Serial.print("Update value_x_min: ");
      // Serial.println(value_x_min);

    }
    else if (value_x_max < bmm.raw_mag_data.raw_datax)
    {
      value_x_max = bmm.raw_mag_data.raw_datax;
      // Serial.print("update value_x_max: ");
      // Serial.println(value_x_max);
    }

    /* Update y-Axis max/min value */
    if (value_y_min > bmm.raw_mag_data.raw_datay)
    {
      value_y_min = bmm.raw_mag_data.raw_datay;
      // Serial.print("Update value_y_min: ");
      // Serial.println(value_y_min);

    }
    else if (value_y_max < bmm.raw_mag_data.raw_datay)
    {
      value_y_max = bmm.raw_mag_data.raw_datay;
      // Serial.print("update value_y_max: ");
      // Serial.println(value_y_max);
    }

    /* Update z-Axis max/min value */
    if (value_z_min > bmm.raw_mag_data.raw_dataz)
    {
      value_z_min = bmm.raw_mag_data.raw_dataz;
      // Serial.print("Update value_z_min: ");
      // Serial.println(value_z_min);

    }
    else if (value_z_max < bmm.raw_mag_data.raw_dataz)
    {
      value_z_max = bmm.raw_mag_data.raw_dataz;
      // Serial.print("update value_z_max: ");
      // Serial.println(value_z_max);
    }

    Serial.println(millis());
    delay(100);
  }

  value_offset.x = value_x_min + (value_x_max - value_x_min) / 2;
  value_offset.y = value_y_min + (value_y_max - value_y_min) / 2;
  value_offset.z = value_z_min + (value_z_max - value_z_min) / 2;
}

// Effectue la mesure de l'orientation, dans le sens trigonométrique (à tester)
int mesure_compass() {
  float headingDegrees = 0;
  for (int i = 0; i < 5; i++) {
    bmm150_mag_data value;
    bmm.read_mag_data();

    value.x = bmm.raw_mag_data.raw_datax - value_offset.x;
    value.y = bmm.raw_mag_data.raw_datay - value_offset.y;
    value.z = bmm.raw_mag_data.raw_dataz - value_offset.z;

    float xyHeading = atan2(value.x, value.y);
    float zxHeading = atan2(value.z, value.x);
    float heading = xyHeading;

    if (heading < 0)
      heading += 2 * PI;
    if (heading > 2 * PI)
      heading -= 2 * PI;
    headingDegrees += heading * 180 / M_PI;
    float xyHeadingDegrees = xyHeading * 180 / M_PI;
    float zxHeadingDegrees = zxHeading * 180 / M_PI;

    delay(100);
  }
  headingDegrees = headingDegrees / 5;
  headingDegrees = 90 - headingDegrees;
  if(headingDegrees < 0) {
    headingDegrees = 360 + headingDegrees;
  }
  return int(headingDegrees);
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

void turn_right() {
  Serial.println("turn_right();");
  vitesse = 50;
  int mesure = 0;
  int mesured = mesure_compass();
  int arret = mesured - 90;
  if(arret < 0) {
    arret = 360 - arret;
  }
  Serial.println(mesure);
  Serial.println(arret);
  while (mesure > arret + 15 || mesure < arret - 15) {
    mesure = mesure_compass();
    moteurs(1, -1);
    Serial.print("moteurs(1,-1); / ");
    Serial.print(mesure);
    Serial.print(" ");
    Serial.println(arret);
  }
  moteurs(-1, 1);
  delay(80);
  moteurs(0, 0);
  reset_compteur();
}

void turn_left() {
  Serial.println("turn_left();");
  vitesse = 50;
  int mesure = 0;
  int mesured = mesure_compass();
  int arret = mesured + 90;
  if(arret > 360) {
    arret = arret - 360;
  }
  Serial.println(mesure);
  Serial.println(arret);
  while (mesure > arret + 15 || mesure < arret - 15) {
    mesure = mesure_compass();
    moteurs(-1, 1);
    Serial.print("moteurs(-1,1); / ");
    Serial.print(mesure);
    Serial.print(" ");
    Serial.println(arret);
  }
  moteurs(1, -1);
  delay(80);
  moteurs(0, 0);
  reset_compteur();
}

void moteurs(int gauche, int droite) { //Quel moteur faire avancer ? A REFAIRE
  if (gauche == 1) {
    motor.speed(1, vitesse);
  }
  if (gauche == 0) {
    motor.brake(1);
  }
  if (gauche == -1)
  {
    motor.speed(1, -vitesse);
  }

  if (droite == 1) {
    motor.speed(0, vitesse-12);
  }
  if (droite == 0) {
    motor.brake(0);
  }
  if (droite == -1) {
    motor.speed(0, -vitesse+12);
  }
}
