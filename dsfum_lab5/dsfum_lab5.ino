const int buzzerPin = 3;

void sunaAlarma()
{
  tone(buzzerPin, 440);   //nota do
  delay(300);
  noTone(buzzerPin);  //opreste sunet

  delay(100);

  tone(buzzerPin, 523);   //nota la
  delay(300);
  noTone(buzzerPin);    //opreste sunet
}

//pini ecran
const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

//0 = ceas, 1 = cronometru
int nodAfisaj = 0;

//timp ceas
long secundeCeas = 0;
bool ceasSetat = false;  //comada de pornire

//timp cronometru
long secundeCronometru = 0;
bool cronometruSetat = false;
bool cronometruPornit = false;   //daca e pornit sau daca a ajuns la 0

//nr secunde(fara delay)
unsigned long timpTrecut = 0;

void citesteComenzi()
{
  if(Serial.available() > 0)
  {
    String comanda = Serial.readStringUntil('\n');  //citim pana la enter
    comanda.trim();

    int val1 = 0;   //ore 
    int val2 = 0;   //minute

    if(comanda == "clock")
    {
      modAfisaj = 0;
    }
    else if(comanda == "stopwatch")
    {
      modAfisaj = 1;
    }
    
    //daca nu e setat ceasul
    else if (comanda.startsWith("clock ") && ceasSetat == false)
    {
      if(sscanf(comanda.c_str(), "clock %d:%d", val1, val2) == 2)
      {
         secundeCeas = val1 * 3600 + val2 *60;
         ceasSetat = true;
      }
    }

    //daca nu e setat cronometrul
    else if(comanda.startswith("stopwatch ") and cronometruSetat == false)
    {
      if(sscanf(comanda.c_str(), "stopwatch %d:%d", val1, val2) == 2)
      {
        secundeCronometru = val1 * 60 + val2;
        cronometruSetat = true;
        cronometruPornit = true;
      }
    }
  }
}

void numaraTimpul() {
  unsigned long timpulAcum = millis();
  
  if (timpulAcum - timpTrecut >= 1000) { // a trecut 1 secunda
    timpTrecut = timpulAcum; // pt urm sec
    
    // ceasul creste cu o secunda
    if (ceasSetat == true) {
      secundeCeas = secundeCeas + 1;
    }

    // cronometrul scade cu o secunda
    if (cronometruPornit == true && secundeCronometru > 0) {
      secundeCronometru = secundeCronometru - 1;
      
      // daca a ajuns la 0, suna
      if (secundeCronometru == 0) {
        sunaAlarma(); 
        cronometruPornit = false; 
      }
    }
  }
}

const byte numere[] = {
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

const byte pozitii[] = { 
  0b10000000, // cifra 1
  0b01000000, // cifra 2
  0b00100000, // cifra 3
  0b00010000  // cifra 4
};

// trimite semnalul catre ecran folosind pinii shield-ului
void afiseazaCifra(byte cifra, byte pozitie) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, cifra);
  shiftOut(dataPin, clockPin, MSBFIRST, pozitie);
  digitalWrite(latchPin, HIGH);
}

// calculeaza ce cifre trebuie afisate din secundele curente
void deseneazaEcran() {
  int valoareStanga = 0; // pentru ore sau minute
  int valoareDreapta = 0; // pentru minute sau secunde
  
  if (modAfisaj == 0) { 
    // daca suntem pe Ceas: afisam ore si minute
    valoareStanga = (secundeCeas / 3600) % 24; 
    valoareDreapta = (secundeCeas / 60) % 60;  
  } else { 
    // daca suntem pe cronometru: afisam minute si secunde
    valoareStanga = (secundeCronometru / 60) % 60; 
    valoareDreapta = secundeCronometru % 60;       
  }
  
  int cifra1 = valoareStanga / 10;
  int cifra2 = valoareStanga % 10;
  int cifra3 = valoareDreapta / 10;
  int cifra4 = valoareDreapta % 10;

  // afisare cifre
  afiseazaCifra(numere[cifra1], pozitii[0]); 
  delay(2);
  afiseazaCifra(numere[cifra2], pozitii[1]); 
  delay(2);
  afiseazaCifra(numere[cifra3], pozitii[2]); 
  delay(2);
  afiseazaCifra(numere[c4], pozitii[3]); 
  delay(2);
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  citesteComenzi();
  numaraTimpul();
  deseneazaEcran();
}
