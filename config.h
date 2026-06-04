#pragma once
#include <Arduino.h>

// ============================================================
//  CONFIGURATION ROBOT MINI-SUMO — TECHNOBOT 2026
// ============================================================

// ------------------------------------------------------------
//  BROCHES MOTEURS
// ------------------------------------------------------------
#define MOTEUR_G_PWM   6   // PWM vitesse moteur gauche
#define MOTEUR_G_H1    5   // direction moteur gauche (H1)
#define MOTEUR_G_H2    7   // direction moteur gauche (H2)

#define MOTEUR_D_PWM   3   // PWM vitesse moteur droit
#define MOTEUR_D_H1    2   // direction moteur droit  (H1)
#define MOTEUR_D_H2    4   // direction moteur droit  (H2)

// ------------------------------------------------------------
//  BROCHES CAPTEURS IR ADVERSAIRE (sorties digitales)
// ------------------------------------------------------------
#define IR_AVANT        A5
#define IR_AVANT_DROITE A1
#define IR_AVANT_GAUCHE A3
#define IR_GAUCHE       A4
#define IR_DROITE       10

// ------------------------------------------------------------
//  BROCHES CAPTEURS DE SOL
//  SOL_GAUCHE : capteur analogique — A6 est analogique uniquement (Uno/Nano)
//  SOL_DROITE : QTR-1RC, requiert une broche digitale
// ------------------------------------------------------------
#define SOL_GAUCHE  A6
#define SOL_DROITE  11

// ------------------------------------------------------------
//  BROCHE LED DIAGNOSTIC
// ------------------------------------------------------------
#define LED_ADVERSAIRE  9

// ------------------------------------------------------------
//  BROCHE SWITCH MODE
// ------------------------------------------------------------
#define SWITCH_MODE     A2  // LOW = mode test, HIGH = mode combat

// ------------------------------------------------------------
//  SEUILS CAPTEURS DE SOL
//  Polarités opposées selon le type de capteur :
//    analogique gauche : bord blanc si >= SEUIL_SOL_ANALOG
//    QTR-RC droit      : bord blanc si <  SEUIL_SOL_RC
// ------------------------------------------------------------
#define SEUIL_SOL_ANALOG  300
#define SEUIL_SOL_RC      300

// ------------------------------------------------------------
//  VITESSES MOTEURS (PWM 0-255)
// ------------------------------------------------------------
#define VITESSE_PLEINE   255
#define VITESSE_RAPIDE   200
#define VITESSE_MOYENNE  150
#define VITESSE_LENTE    100
#define VITESSE_ROTATION  60
#define VITESSE_ARRET      0

// ------------------------------------------------------------
//  TIMINGS (millisecondes)
// ------------------------------------------------------------
#define DELAI_DEPART_MS       5000
#define DELAI_RECUL_BORD_MS   1000
#define DELAI_PIVOT_BORD_MS    350
#define DELAI_RECUL_COIN_MS    250
#define DELAI_PIVOT_COIN_MS    250
