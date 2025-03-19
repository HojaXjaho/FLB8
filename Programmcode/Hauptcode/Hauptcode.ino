// Pins für den L293D
const int M1_v = 2; // IN1 (vorwärts)
const int M1_r = 3; // IN2 (rückwärts)
const int M2_v = 4; // IN3 (vorwärts)
const int M2_r = 5; // IN4 (rückwärts)

// Pins für den HC-SR04
const int trig = 6;
const int echo = 7;
//Variablen für die Distanz und Zeit
long time;
long distance;

const int sw = 980;

void setup() {
  pinMode(M1_v, OUTPUT);
  pinMode(M1_r, OUTPUT);
  pinMode(M2_v, OUTPUT);
  pinMode(M2_r, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


  anhalten(false);
}

void loop() {
  trigger();
  lineFollow();
/*  if (distance < 8){
    anhalten(false);
  }
*/
}

// Funktion zum Vorwärtsfahren
void geradeaus(int time) {
  digitalWrite(M1_v, HIGH);
  digitalWrite(M1_r, LOW);
  digitalWrite(M2_v, HIGH);
  digitalWrite(M2_r, LOW);
  delay(time);
}

// Funktion zum Rückwärtsfahren
void zur_ck(int time) {
  digitalWrite(M1_v, LOW);
  digitalWrite(M1_r, HIGH);
  digitalWrite(M2_v, LOW);
  digitalWrite(M2_r, HIGH);
  delay(time);
}

// Funktion zum Lenken, links = 1; rechts = 0
void lenken(int lr/*l=1, r=0*/,int grad) {
  digitalWrite(M1_v, 1 - lr);
  digitalWrite(M1_r, lr);
  digitalWrite(M2_v, lr);
  digitalWrite(M2_r, 1 - lr);
  delay(grad*13.111111111111111);
}
// Funktion zum Stoppen
void anhalten(bool warteBisFalse) {
  digitalWrite(M1_v, LOW);
  digitalWrite(M1_r, LOW);
  digitalWrite(M2_v, LOW);
  digitalWrite(M2_r, LOW);
  while(warteBisFalse){}
}
//Funktion zum Ultraschallsensor auslesen
void trigger(){
  // Sender kurz ausschalten um Störungen des Signals zu vermeiden
  digitalWrite(trig, LOW);
  delay(10);
  // Signal für 10 Mikrosekunden senden
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  // Sender ausschalten
  digitalWrite(trig, LOW);
  // pulseIn → Zeit messen, bis das Signal zurückkommt
  time = pulseIn(echo, HIGH);
  /*
  Entfernung in cm berechnen
  Zeit/2 -> nur eine Strecke soll berechnet werden
  Umrechnung in cm
  */
  distance = (time / 2) * 0.03432;
}
/*//Funktion zum umfahren eines Hindernisses
void umfahren() {
  lenken(0, 90);  // rechts
  geradeaus(1500);// geradeaus
  lenken(1, 90);  // links
  geradeaus(3000);// geradeaus
  lenken(1, 90);  // links
  geradeaus(1500);// geradeaus
  lenken(0, 90);  // rechts
}*/
//Funktion zum beenden des Codes
void ende() {
  anhalten(false);   // Fahrt stoppen, dass es nicht ewig in eine Richtung läuft
  while(true){} // eine unendliche Schleife, damit der Rest des Codes nicht mehr drankommt. (Den Arduino Uno R3 kann man nicht ausschalten.)
}
void lineFollow() {
  if                            // wenn rechter Liniensensor bemerkt Linie → lenke nach rechts bis Mitte erkennt die Linie
  (analogRead(A0)>980 && 
  analogRead(A1)<980 && 
  analogRead(A2)<980){
    while(analogRead(A1)<980&&analogRead(A0)>980){
      lenken(0, 0);
    }
  }
  else if                       // wenn mittlerer Liniensensor bemerkt Linie → fahre geradeaus bis Mitte keine Linie erkennt
  (analogRead(A0)<980 && 
  analogRead(A1)>980 && 
  analogRead(A2)<980){
    while(analogRead(A1)>980){
      geradeaus(0);
    }
  }
  else if                       // wenn linker Liniensensor bemerkt Linie → lenke nach links bis Mitte erkennt die Linie
  (analogRead(A0)<980 && 
  analogRead(A1)<980 && 
  analogRead(A2)>980){
    while(analogRead(A1)<980&&analogRead(A2)>980){
      lenken(1, 0);
    }
  }
  else if  
  (analogRead(A0)<980 && 
  analogRead(A1)>980 && 
  analogRead(A2)>980){
    while(analogRead(A2)>980){
      lenken(1, 0);
    }
  }
  else if  
  (analogRead(A0)>980 && 
  analogRead(A1)>980 && 
  analogRead(A2)<980){
    while(analogRead(A0)>980){
      lenken(0, 0);
    }
  }
  else if 
  (analogRead(A0)<980 && 
  analogRead(A1)<980 && 
  analogRead(A2)<980){
    #ifndef stsz
      #define stsz millis()
    #endif
    if (millis()-stsz>2999){
      #undef stsz
      anhalten(analogRead(A0)<sw||analogRead(A1)<sw||analogRead(A2)<sw);
    }
  }
  else if (analogRead(A0)>sw||analogRead(A1)>sw||analogRead(A2)>sw){
    #undef stsz
  }
  else{geradeaus(0);}
}
void umfahren(){
  //int umfahrZufall = random(0,2);
  lenken(/*umfahrZufall*/0, 90);
  umfahrGeradeaus();
  lenken(1,90);
  umfahrGeradeaus();
}

void umfahrGeradeaus(){
  unsigned long start = millis();
  while(millis() - start < 3000){
  geradeaus(0);
  if (analogRead(A0)>sw||analogRead(A1)>sw||analogRead(A2)>sw){
    if (analogRead(A0)>sw||analogRead(A2)>sw){
      while((analogRead(A0)>980||analogRead(A2)>980)&&analogRead(A1)<980){
        lenken(0,0);
      }
    }
    return;
    }
  }
}

