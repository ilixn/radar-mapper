int mesuredepart = mesure();
mesure = mesure() - mesuredepart;
if(mesure < 0) {
  mesure = 360 + mesure; //--> mesure entre 0 et 360
}
mesure = 540 - mesure; //passage dans l'autre sens
mesure = mesure + degre + decalage; //degre entre 0 et 180, decalage entre 0 et 180
if(mesure > 360) {
  mesure = mesure - 360;
}