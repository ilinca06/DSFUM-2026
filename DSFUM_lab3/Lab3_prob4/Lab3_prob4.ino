const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

// codificarea literelor A, b, C, d, E, F
// biti calculati in logica inversa (0 aprins, 1 stins) 
// si apoi OGLINDITI complet pentru a functiona corect cu LSBFIRST
byte litere[6] = {
  0b00010001, // A (forma normala era 10001000)
  0b11000001, // b (forma normala era 10000011)
  0b01100011, // C (forma normala era 11000110)
  0b10000101, // d (forma normala era 10100001)
  0b01100001, // E (forma normala era 10000110)
  0b01110001  // F (forma normala era 10001110)
};

// pozitia cea mai din stanga (cifra 1)
// forma normala 241 (11110001) oglindita pentru LSBFIRST
byte pozitieStanga = 0b10001111; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // parcurgem cele 6 litere
  for (int i = 0; i < 6; i++) {
    
    // blocam registrul
    digitalWrite(latchPin, LOW);
    
    // trimitem desenul literei folosind LSBFIRST 
    shiftOut(dataPin, clockPin, LSBFIRST, litere[i]);
    
    // trimitem selectorul pentru pozitia din stanga
    shiftOut(dataPin, clockPin, LSBFIRST, pozitieStanga);
    
    digitalWrite(latchPin, HIGH);
    
    delay(5000);
  }
}