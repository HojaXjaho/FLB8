// Pins für den L293D
const int M1_v = 2; // IN1 (vorwärts)
const int M1_r = 3; // IN2 (rückwärts)
const int M2_v = 4; // IN3 (vorwärts)
const int M2_r = 5; // IN4 (rückwärts)

void setup() {
  pinMode(M1_v, OUTPUT);
  pinMode(M1_r, OUTPUT);
  pinMode(M2_v, OUTPUT);
  pinMode(M2_r, OUTPUT);


  anhalten();
}

void loop() {
  geradeaus(3000);

  lenken(1,90);
  geradeaus(3000);

  lenken(0,180);
  geradeaus(3000);

  ende();
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
}
// Funktion zum Stoppen
void anhalten() {
  digitalWrite(M1_v, LOW);
  digitalWrite(M1_r, LOW);
  digitalWrite(M2_v, LOW);
  digitalWrite(M2_r, LOW);
}
void ende() {
  anhalten();
  while(true){}
}
