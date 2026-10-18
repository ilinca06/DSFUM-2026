const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

const int btnA1 = A1; // incrementare
const int btnA2 = A2; // decrementare
const int btnA3 = A3; // resetare

// forma grafica pentru cifrele 0-9 
// adaugam o pozitie in plus (indexul 10) care reprezinta "complet stins"
byte codCifre[11] = 
{
  0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000, // 9
  0b11111111  // 10 toate segmentele stinse
};

// codurile pentru cele 4 pozitii ale ecranului 
byte pozitii[4] = {241, 242, 244, 248};

int counter = 0;

bool stareA1Anterioara = HIGH;
bool stareA2Anterioara = HIGH;
bool stareA3Anterioara = HIGH;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // butoanele pe Shield sunt setate sa trimita LOW cand sunt apasate
  pinMode(btnA1, INPUT_PULLUP);
  pinMode(btnA2, INPUT_PULLUP);
  pinMode(btnA3, INPUT_PULLUP);
}

void afiseazaNumar(int numar) 
{
  int cifre[4];
  
  cifre[0] = numar / 1000;          
  cifre[1] = (numar / 100) % 10;    
  cifre[2] = (numar / 10) % 10;     
  cifre[3] = numar % 10;            
  
  // ascundem zerourile din fata inlocuindu-le cu indexul 10 
  if (numar < 1000) cifre[0] = 10;
  if (numar < 100)  cifre[1] = 10;
  if (numar < 10)   cifre[2] = 10;
  
  // mentinem ecranul aprins folosind multiplexarea
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, codCifre[cifre[i]]);
    shiftOut(dataPin, clockPin, MSBFIRST, pozitii[i]);
    digitalWrite(latchPin, HIGH);
    delay(2);
  }
}

void loop() {

  bool stareA1 = digitalRead(btnA1);
  bool stareA2 = digitalRead(btnA2);
  bool stareA3 = digitalRead(btnA3);

  // daca butonul e apasat ACUM (LOW), dar la tura trecuta NU ERA (HIGH) -> a fost un "click" nou
  if (stareA1 == LOW && stareA1Anterioara == HIGH) 
  {
    if (counter < 9999) 
    {
      counter++;
    }
  }

  // click pentru decrementare
  if (stareA2 == LOW && stareA2Anterioara == HIGH) 
  {
    if (counter > 0) 
    {
      counter--;
    }
  }

  // click pentru resetare
  if (stareA3 == LOW && stareA3Anterioara == HIGH) 
  {
    counter = 0;
  }

  stareA1Anterioara = stareA1;
  stareA2Anterioara = stareA2;
  stareA3Anterioara = stareA3;

  afiseazaNumar(counter);
}