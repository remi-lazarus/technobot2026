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
//  BROCHES CAPTEURS IR ADVERSAIRE
// ------------------------------------------------------------
#define IR_AVANT        A0
#define IR_AVANT_DROITE A1
#define IR_AVANT_GAUCHE A3
#define IR_GAUCHE       8
#define IR_DROITE       12

// ------------------------------------------------------------
//  BROCHES CAPTEURS DE SOL (détection bord blanc du Dohyo)
//  QTR-1RC : nécessite des broches digitales (pas A6/A7)
// ------------------------------------------------------------
#define SOL_GAUCHE  11
#define SOL_DROITE  13

// ------------------------------------------------------------
//  BROCHES LEDS DE DIAGNOSTIC
// ------------------------------------------------------------
#define LED_BORD        9   // jaune — bord blanc détecté
#define LED_ADVERSAIRE  10  // bleue — adversaire détecté

// ------------------------------------------------------------
//  BROCHE SWITCH MODE
// ------------------------------------------------------------
#define SWITCH_MODE     A2  // LOW = mode test, HIGH = mode combat

// ------------------------------------------------------------
//  SEUIL CAPTEURS DE SOL
//  Valeur analogique en dessous de laquelle le sol est considéré blanc
// ------------------------------------------------------------
#define SEUIL_SOL  300  // QTR-1RC : blanc ≈ 0-200, noir ≈ 800-2500 (à calibrer)

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
#define DELAI_DEPART_MS       5000  // attente réglementaire avant départ (Art. 5)
#define DELAI_RECUL_BORD_MS   1000  // durée recul quand bord détecté des 2 côtés
#define DELAI_PIVOT_BORD_MS    350  // durée pivot après recul bord central
#define DELAI_RECUL_COIN_MS    250  // durée recul quand bord détecté d'un seul côté
#define DELAI_PIVOT_COIN_MS    250  // durée pivot après recul de coin
