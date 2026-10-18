const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

// pini butoane
const int btnA1 = A1; 
const int btnA2 = A2; 
const int btnA3 = A3;

// coduri pozitii digit (stanga spre dreapta)
byte pozitii[4] = {241, 242, 244, 248};

// text cu spatii la capete pt efect fluid
String mesaj = "    dECEbAL_Si_FiUL_SAU_LOCUiESC_PE_PLAiUL_dACiEi    ";
int lungimeMesaj = mesaj.length();

// control miscare text
int fereastra = 0; 
unsigned long timpAnteriorScroll = 0;
int intervalScroll = 350; // Viteza miscare

// control pauza
bool pePauza = false;
bool stareA1Ant = HIGH, stareA2Ant = HIGH, stareA3Ant = HIGH;

// conversie litera in cod binar LED
byte literaLaByte(char litera) 
{
  switch (litera) 
  {
    case 'd': return 0b10100001;
    case 'E': return 0b10000110;
    case 'C': return 0b11000110;
    case 'b': return 0b10000011;
    case 'A': return 0b10001000;
    case 'L': return 0b11000111;
    case '_': return 0b11110111;
    case 'S': return 0b10010010;
    case 'i': return 0b11111001; 
    case 'F': return 0b10001110;
    case 'U': return 0b11000001;
    case 'O': return 0b11000000;
    case 'P': return 0b10001100;
    case ' ': return 0b11111111; 
    default:  return 0b11111111; 
  }
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(btnA1, INPUT_PULLUP);
  pinMode(btnA2, INPUT_PULLUP);
  pinMode(btnA3, INPUT_PULLUP);
}

void loop() {
  // citire stare butoane
  bool stareA1 = digitalRead(btnA1);
  bool stareA2 = digitalRead(btnA2);
  bool stareA3 = digitalRead(btnA3);

  // detectare apasare noua
  if ((stareA1 == LOW && stareA1Ant == HIGH) || (stareA2 == LOW && stareA2Ant == HIGH) || (stareA3 == LOW && stareA3Ant == HIGH)) 
  {
    pePauza = !pePauza; // schimba starea miscare/pauza
  }

  // salvare stare curenta
  stareA1Ant = stareA1;
  stareA2Ant = stareA2;
  stareA3Ant = stareA3;

  unsigned long timpCurent = millis();
  
  if (pePauza == false) 
  {
    if (timpCurent - timpAnteriorScroll >= intervalScroll) 
    {
      timpAnteriorScroll = timpCurent;
      fereastra++; 
      
      // resetare dupa parcurgerea textului
      if (fereastra > lungimeMesaj - 4) {
        fereastra = 0;
      }
    }
  }

  // afisare pe ecran
  for (int i = 0; i < 4; i++) {
    char literaCurenta = mesaj.charAt(fereastra + i);
    byte desenLitera = literaLaByte(literaCurenta);

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, desenLitera);
    shiftOut(dataPin, clockPin, MSBFIRST, pozitii[i]);
    digitalWrite(latchPin, HIGH);
    
    delay(2); 
  }
}