
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
int dis_ausweichen;
int i = 0;
void setup() {
  pinMode(M1_v, OUTPUT);
  pinMode(M1_r, OUTPUT);
  pinMode(M2_v, OUTPUT);
  pinMode(M2_r, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


  anhalten();
}

void loop() {
  trigger();
  geradeaus(0);
  if (distance < 8){
    ausweichen();
  }

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

// Funktion zum Vorwärtsfahren
void lenken(int lr,int grad) {// l = 1, r = 0
  digitalWrite(M1_v, 1 - lr);
  digitalWrite(M1_r, lr);
  digitalWrite(M2_v, lr);
  digitalWrite(M2_r, 1 - lr);
  delay(grad*13.111111111111111);
  anhalten();
}
// Funktion zum Stoppen
void anhalten() {
  digitalWrite(M1_v, LOW);
  digitalWrite(M1_r, LOW);
  digitalWrite(M2_v, LOW);
  digitalWrite(M2_r, LOW);
}

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
  Zeit/2 → nur eine Strecke soll berechnet werden
  Umrechnung in cm
  */
  distance = (time / 2) * 0.03432;
  //int sensorValue = digitalRead(line_track);
}
void ende() {
  anhalten();
  while(true){}
}
void ausweichen(){
  lenken(0,90);
  while (dis_ausweichen < 10){
    i++;
    lenken(0,90);
    anhalten();
    trigger();
    if (distance < 8){

      ende();
    }
    geradeaus(1);
    lenken(1,90);
    anhalten();
    trigger();
    dis_ausweichen = distance;
  }
  while (dis_ausweichen < 10){
    lenken(0,90);
    anhalten();
    trigger();
    if (distance < 8){
      ende();
    }
    geradeaus(1);
    lenken(1,90);
    anhalten();
    trigger();
    dis_ausweichen = distance;
  }
  while (i > 0){
    trigger();
    if (distance < 8){
      ende();
    }
    geradeaus(1);
    anhalten();
  }
}
