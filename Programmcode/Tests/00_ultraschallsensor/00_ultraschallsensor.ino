const int trig = 2;
const int echo = 3;
//const int line_track = 7;
long time;
long distance;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
//  pinMode(line_track, INPUT);
  Serial.begin(9600);
}

void loop() {
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
  Serial.println(distance);
  //Serial.print(sensorValue); // Gibt den Sensorwert aus
}
