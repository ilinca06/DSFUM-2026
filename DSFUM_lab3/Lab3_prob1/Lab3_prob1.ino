const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

// codificarea cifrelor 0-9 
// 0 aprinde segmentul, 1 il stinge
byte cifre[10] = {
  0b11000000, // 0 
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000  // 9
};

// selectam un singur digit pe care sa afisam 
// valoarea 241 (0b11110001) oglindita pentru LSBFIRST
byte pozitie = 0b10001111; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 10; i++) 
  {
    digitalWrite(latchPin, LOW);
    
    // trimitem forma cifrei folosind LSBFIRST 
    shiftOut(dataPin, clockPin, LSBFIRST, cifre[i]);
    
    // forma oglindita
    shiftOut(dataPin, clockPin, LSBFIRST, pozitie);
    
    digitalWrite(latchPin, HIGH);
    
    delay(1000);
  }
}