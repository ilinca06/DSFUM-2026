int stareLed = 0; 
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Citire date
  if (Serial.available() > 0) {
    char optiune = Serial.read();
    
    if (optiune == '1') {
      Serial.println("pornit");
      stareLed = 1;
    } 
    else if (optiune == '2') {
      Serial.println("oprit");
      stareLed = 2;
    } 
    else if (optiune == '3') {
      Serial.println("blink");
      stareLed = 3;
    }
  }

  // executare functii in functie de stare curenta
  if (stareLed == 1) {
    digitalWrite(ledPin, HIGH); // aprinde ledul de la pinul 13
  } 
  else if (stareLed == 2) {
    digitalWrite(ledPin, LOW);  // stinge ledul de la pinul 13
  } 
  else if (stareLed == 3) {
    digitalWrite(ledPin, HIGH);
    delay(10000);               // blink la 10 secunde
    digitalWrite(ledPin, LOW);
    delay(10000);
  }
}