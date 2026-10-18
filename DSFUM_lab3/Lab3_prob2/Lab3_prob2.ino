const int latchPin = 4;
const int clockPin = 7;
const int dataPin = 8;

// forma graficelor pentru cifre
byte codCifre[10] = 
{
  0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
  0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000
};

// codurile pentru a activa fiecare din cele 4 pozitii ale ecranului
byte pozitii[4] = {241, 242, 244, 248}; 

// variabile pentru joc si statistici
int runda = 0;
unsigned long timpStart;
unsigned long timpMinim = 4294967295; // incepem cu maximul posibil
unsigned long timpMaxim = 0;
unsigned long sumaTimpi = 0;
int valoareMinima = 0;
int valoareMaxima = 0;

int numarCurent = 0;
int cifreNumar[4];  

bool jocTerminat = false;

void extrageCifre(int numar) 
{
  cifreNumar[0] = numar / 1000;          
  cifreNumar[1] = (numar / 100) % 10;    
  cifreNumar[2] = (numar / 10) % 10;     
  cifreNumar[3] = numar % 10;            
}

// multiplexare 
void afiseazaMultiplexat() 
{
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, codCifre[cifreNumar[i]]);
    shiftOut(dataPin, clockPin, MSBFIRST, pozitii[i]);
    digitalWrite(latchPin, HIGH);
    delay(2); 
  }
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  
  randomSeed(analogRead(A5)); 
  
  Serial.println("Scrie numerele de pe ecran cat mai repede.");
  delay(2000);
}

void loop() {
  if (jocTerminat == false) 
  {
    if (runda < 10) 
    {
      // daca numarul este 0, inseamna ca trebuie sa generam unul nou
      if (numarCurent == 0) 
      {
        numarCurent = random(1000, 10000); 
        extrageCifre(numarCurent);
        
        // curatam buffer-ul Serial ca sa nu citeasca Enter-uri vechi
        while(Serial.available() > 0) { Serial.read(); }
        
        timpStart = millis(); 
      }

      // tinem ecranul aprins
      afiseazaMultiplexat();

      // citim de la tastatura
      if (Serial.available() > 0) 
      {
        int input = Serial.parseInt();
        
        if (input > 0) 
        {
          if (input == numarCurent) 
          {
            unsigned long timpReactie = millis() - timpStart;
            sumaTimpi = sumaTimpi + timpReactie;
            
            // verificam daca ai batut recordul 
            if (timpReactie < timpMinim) 
            {
              timpMinim = timpReactie;
              valoareMinima = numarCurent;
            }
            if (timpReactie > timpMaxim) 
            {
              timpMaxim = timpReactie;
              valoareMaxima = numarCurent;
            }
            
            runda++;
            Serial.print("Corect! Timpul tau: ");
            Serial.print(timpReactie);
            Serial.println(" ms");
            
            numarCurent = 0; // resetam 
            delay(1000); // pauza 1 secunda intre runde
            
          } else 
          {
            Serial.println("Ai gresit, mai incearca o data!");
          }
        }
      }
    } 
    // daca am trecut de cele 10 runde, afisam clasamentul
    else 
    {
      Serial.println("JOC TERMINAT");
      Serial.print("Cel mai rapid timp: "); Serial.print(timpMinim); Serial.print(" ms (la numarul "); Serial.print(valoareMinima); Serial.println(")");
      Serial.print("Cel mai lent timp:  "); Serial.print(timpMaxim); Serial.print(" ms (la numarul "); Serial.print(valoareMaxima); Serial.println(")");
      Serial.print("Timpul mediu:       "); Serial.print(sumaTimpi / 10); Serial.println(" ms");
      
      jocTerminat = true; // oprim jocul
    }
  }
}