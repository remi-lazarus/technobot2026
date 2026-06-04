#include "config.h"
#include <QTRSensors.h>

// ============================================================
//  CAPTEURS DE SOL (QTR-1RC)
// ============================================================
static QTRSensors qtrSol;
static uint16_t   solValues[2];

// ============================================================
//  ÉTAT GLOBAL
// ============================================================
static bool    enDepart          = true;
static uint8_t derniereDirection = 1;  // 0=avant 1=droite 2=gauche (1 par défaut : cherche à droite)

// ============================================================
//  PRIMITIVES MOTEURS
//  Positif = avant, négatif = arrière, 0 = arrêt
// ============================================================
void motorGauche(int vitesse) {
  if (vitesse > 0) {
    analogWrite(MOTEUR_G_PWM, vitesse);
    digitalWrite(MOTEUR_G_H1, HIGH);
    digitalWrite(MOTEUR_G_H2, LOW);
  } else if (vitesse < 0) {
    analogWrite(MOTEUR_G_PWM, -vitesse);
    digitalWrite(MOTEUR_G_H1, LOW);
    digitalWrite(MOTEUR_G_H2, HIGH);
  } else {
    analogWrite(MOTEUR_G_PWM, 0);
    digitalWrite(MOTEUR_G_H1, HIGH);
    digitalWrite(MOTEUR_G_H2, LOW);
  }
}

void motorDroit(int vitesse) {
  if (vitesse > 0) {
    analogWrite(MOTEUR_D_PWM, vitesse);
    digitalWrite(MOTEUR_D_H1, LOW);
    digitalWrite(MOTEUR_D_H2, HIGH);
  } else if (vitesse < 0) {
    analogWrite(MOTEUR_D_PWM, -vitesse);
    digitalWrite(MOTEUR_D_H1, HIGH);
    digitalWrite(MOTEUR_D_H2, LOW);
  } else {
    analogWrite(MOTEUR_D_PWM, 0);
    digitalWrite(MOTEUR_D_H1, LOW);
    digitalWrite(MOTEUR_D_H2, HIGH);
  }
}

// ============================================================
//  MOUVEMENTS
// ============================================================
void avantToute()      { motorGauche(VITESSE_PLEINE);    motorDroit(VITESSE_PLEINE);    }
void avantLent()       { motorGauche(VITESSE_LENTE);     motorDroit(VITESSE_LENTE);     }
void arriereToute()    { motorGauche(-VITESSE_PLEINE);   motorDroit(-VITESSE_PLEINE);   }
void arret()           { motorGauche(VITESSE_ARRET);     motorDroit(VITESSE_ARRET);     }
void pivotDroite()     { motorGauche(VITESSE_ROTATION);  motorDroit(-VITESSE_ROTATION); }
void pivotGauche()     { motorGauche(-VITESSE_ROTATION); motorDroit(VITESSE_ROTATION);  }
void reculCoinGauche() { motorGauche(VITESSE_ARRET);     motorDroit(-VITESSE_PLEINE);   }
void reculCoinDroite() { motorGauche(-VITESSE_PLEINE);   motorDroit(VITESSE_ARRET);     }
void avanceCoinDroite(){ motorGauche(VITESSE_PLEINE);    motorDroit(VITESSE_ARRET);     }
void avanceCoinGauche(){ motorGauche(VITESSE_ARRET);     motorDroit(VITESSE_PLEINE);    }

// ============================================================
//  LECTURES CAPTEURS
// ============================================================
bool bordGauche()     { return solValues[0] < SEUIL_SOL; }
bool bordDroite()     { return solValues[1] < SEUIL_SOL; }
bool irAvant()        { return digitalRead(IR_AVANT);               }
bool irAvantDroite()  { return digitalRead(IR_AVANT_DROITE);        }
bool irAvantGauche()  { return digitalRead(IR_AVANT_GAUCHE);        }
bool irGauche()       { return digitalRead(IR_GAUCHE);              }
bool irDroite()       { return digitalRead(IR_DROITE);              }

// ============================================================
//  SÉQUENCE DÉPART — délai réglementaire 5 s (Art. 5)
// ============================================================
void countdownDepart() {
  digitalWrite(LED_BORD, HIGH); digitalWrite(LED_ADVERSAIRE, HIGH); delay(1000);
  digitalWrite(LED_BORD, LOW);  digitalWrite(LED_ADVERSAIRE, LOW);  delay(1000);
  digitalWrite(LED_BORD, HIGH); digitalWrite(LED_ADVERSAIRE, HIGH); delay(1000);
                                 digitalWrite(LED_ADVERSAIRE, LOW);  delay(1000);
  digitalWrite(LED_BORD, LOW);                                       delay(1000);
  enDepart = false;
}

// ============================================================
//  MODE TEST — diagnostic capteurs sans bouger
// ============================================================
void modeTest() {
  arret();
  qtrSol.read(solValues);
  digitalWrite(LED_BORD,       (bordGauche() || bordDroite()) ? HIGH : LOW);
  digitalWrite(LED_ADVERSAIRE, (irAvant() || irAvantDroite() || irAvantGauche()
                                 || irGauche() || irDroite())  ? HIGH : LOW);
}

// ============================================================
//  MODE COMBAT — gestion des bords
// ============================================================
void gestionBords() {
  qtrSol.read(solValues);
  bool bg = bordGauche();
  bool bd = bordDroite();

  if (bg && bd) {
    digitalWrite(LED_BORD, HIGH);
    arriereToute();  delay(DELAI_RECUL_BORD_MS);
    digitalWrite(LED_BORD, LOW);
    pivotGauche();   delay(DELAI_PIVOT_BORD_MS);
    avantLent();
    return;
  }
  if (bg) {
    digitalWrite(LED_BORD, HIGH);
    reculCoinGauche(); delay(DELAI_RECUL_COIN_MS);
    digitalWrite(LED_BORD, LOW);
    avanceCoinDroite(); delay(DELAI_PIVOT_COIN_MS);
    avantLent();
    return;
  }
  if (bd) {
    digitalWrite(LED_BORD, HIGH);
    reculCoinDroite(); delay(DELAI_RECUL_COIN_MS);
    digitalWrite(LED_BORD, LOW);
    avanceCoinGauche(); delay(DELAI_PIVOT_COIN_MS);
    avantLent();
    return;
  }

  digitalWrite(LED_BORD, LOW);
}

// ============================================================
//  MODE COMBAT — recherche et attaque de l'adversaire
// ============================================================
void gestionAdversaire() {
  if (irAvant()) {
    digitalWrite(LED_ADVERSAIRE, HIGH);
    avantToute();
    derniereDirection = 0;
    return;
  }
  if (irAvantDroite() || irDroite()) {
    digitalWrite(LED_ADVERSAIRE, HIGH);
    pivotDroite();
    derniereDirection = 1;
    return;
  }
  if (irAvantGauche() || irGauche()) {
    digitalWrite(LED_ADVERSAIRE, HIGH);
    pivotGauche();
    derniereDirection = 2;
    return;
  }

  // Adversaire perdu : cherche dans la dernière direction connue
  digitalWrite(LED_ADVERSAIRE, LOW);
  switch (derniereDirection) {
    case 0: avantLent();   break;
    case 1: pivotDroite(); break;
    case 2: pivotGauche(); break;
  }
}

// ============================================================
//  MODE COMBAT
// ============================================================
void modeCombat() {
  if (enDepart) { countdownDepart(); return; }
  gestionBords();
  gestionAdversaire();
}

// ============================================================
//  ARDUINO
// ============================================================
void setup() {
  pinMode(MOTEUR_G_PWM, OUTPUT);
  pinMode(MOTEUR_G_H1,  OUTPUT);
  pinMode(MOTEUR_G_H2,  OUTPUT);
  pinMode(MOTEUR_D_PWM, OUTPUT);
  pinMode(MOTEUR_D_H1,  OUTPUT);
  pinMode(MOTEUR_D_H2,  OUTPUT);

  qtrSol.setTypeRC();
  qtrSol.setSensorPins((const uint8_t[]){SOL_GAUCHE, SOL_DROITE}, 2);

  pinMode(IR_AVANT,        INPUT);
  pinMode(IR_AVANT_DROITE, INPUT);
  pinMode(IR_AVANT_GAUCHE, INPUT);
  pinMode(IR_GAUCHE,       INPUT);
  pinMode(IR_DROITE,       INPUT);

  pinMode(LED_BORD,       OUTPUT);
  pinMode(LED_ADVERSAIRE, OUTPUT);

  pinMode(SWITCH_MODE, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SWITCH_MODE) == LOW) {
    modeTest();
  } else {
    modeCombat();
  }
}
