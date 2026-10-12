

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "Arduino_CapacitiveTouch.h"

ArduinoLEDMatrix matrice;
CapacitiveTouch capteur(LOVE_BUTTON);   // le cœur au dos de la carte

unsigned int compteur = 0;
bool etaitTouche = false;

void afficherNombre(unsigned int n) {
  char txt[12];
  snprintf(txt, sizeof(txt), "%u", n);
  int longueur = strlen(txt);

  matrice.beginDraw();
  matrice.clear();
  matrice.stroke(0xFFFFFFFF);

  if (longueur <= 3) {
    // Jusqu'à 999 : nombre fixe et centré
    matrice.textFont(Font_4x6);
    matrice.beginText((12 - longueur * 4) / 2, 1, 0xFFFFFF);
    matrice.print(txt);
    matrice.endText();
  } else {
    // Au-delà : le nombre défile
    char defile[20];
    snprintf(defile, sizeof(defile), "  %s  ", txt);
    matrice.textFont(Font_5x7);
    matrice.textScrollSpeed(50);
    matrice.beginText(0, 1, 0xFFFFFF);
    matrice.print(defile);
    matrice.endText(SCROLL_LEFT);
  }
  matrice.endDraw();
}

void setup() {
  Serial.begin(115200);
  matrice.begin();
  capteur.begin();
  // capteur.setThreshold(2000);  // à ajuster si le toucher est trop/pas assez sensible

  afficherNombre(compteur);
}

void loop() {
  bool touche = capteur.isTouched();

  // On compte uniquement quand le doigt se pose (pas tant qu'il reste posé)
  if (touche && !etaitTouche) {
    compteur++;
    afficherNombre(compteur);
    Serial.println(compteur);
  }
  etaitTouche = touche;

  delay(20);
}
