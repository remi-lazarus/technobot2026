// Capteurs ligne blanche (analogiques)
const int LB_G  = 8;
//const int LB_D  = A7;
const int SEUIL_LIGNE = 200; // < seuil = ligne blanche détectée (à calibrer en mode test)

void setup() {
  pinMode(8, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("LB_G="); Serial.println(digitalRead(LB_G));
  delay(1000);
}