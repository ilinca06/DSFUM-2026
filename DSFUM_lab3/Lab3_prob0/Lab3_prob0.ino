const int nrLed = 6;
int pini[nrLed] = {8, 9, 10, 11, 12, 13};
  
String animatie[nrLed] = {"off", "off", "off", "off", "off", "off"};
unsigned long timpAnim[nrLed] = {0, 0, 0, 0, 0, 0};

int valPWM[nrLed] = {0, 0, 0, 0, 0, 0};

unsigned long tStartAnim[nrLed] = {0, 0, 0, 0, 0, 0};

unsigned long tAnteriorPWM = 0;
int perioadaPWM = 2000;

void setup() {
  Serial.begin(9600);

  int i;
  for(i=0; i<nrLed; i++)
  {
    pinMode(pini[i], OUTPUT);
  }

  Serial.println("Comanda: (ex: 8,fadeinout,2000)");
}

void loop() {
  if(Serial.available() > 0)
  {
    int pin = Serial.parseInt();

    if(pin >= 8 and pin <= 13)
    {
      Serial.read();

      String tipAnim = Serial.readStringUntil(',');

      unsigned long timp = Serial.parseInt();

      int index = pin - 8;

      animatie[index] = tipAnim;
      timpAnim[index] = timp;
      tStartAnim[index] = millis();

      
    }
  }
  unsigned long timpCurentMillis = millis();

  // calculam stadiul animatiei pentru fiecare LED 
  for (int i = 0; i < nrLed; i++) 
  {
    if (animatie[i] == "off") 
    {
      valPWM[i] = 0; // stins complet
    } 
    else 
    {
      // cat timp a trecut de cand am dat comanda
      unsigned long timpScurs = timpCurentMillis - tStartAnim[i];
      
      // daca timpul e 2000, cand ajunge la 2001, timpScurs devine din nou 1
      timpScurs = timpScurs % timpAnim[i];

      if (animatie[i] == "blink") 
      {
        if (timpScurs < timpAnim[i] / 2) 
        {
          valPWM[i] = 255; // prima jumătate de timp e complet aprins
        } else 
        {
          valPWM[i] = 0;   // a doua jumătate e complet stins
        }
      } 
      else if (animatie[i] == "fadein") 
      {
        // functia map() transforma timpul curs in luminozitate 
        valPWM[i] = map(timpScurs, 0, timpAnim[i], 0, 255);
      } 
      else if (animatie[i] == "fadeout") 
      {
        // inversam valorile de luminozitate 
        valPWM[i] = map(timpScurs, 0, timpAnim[i], 255, 0);
      } 
      else if (animatie[i] == "fadeinout") 
      {
        unsigned long jumatate = timpAnim[i] / 2;
        if (timpScurs < jumatate) 
        {
          // urca spre 255 in prima jumatate de timp (fadein)
          valPWM[i] = map(timpScurs, 0, jumatate, 0, 255);
        } else 
        {
          // scade spre 0 in a doua jumatate de timp (fadeout)
          valPWM[i] = map(timpScurs, jumatate, timpAnim[i], 255, 0);
        }
      }
    }
  }

  // aplicăm luminozitate pe toti pinii folosind PWM 
  unsigned long timpCurentMicros = micros();
  unsigned long timpScursPWM = timpCurentMicros - tAnteriorPWM;

  // resetam ciclul PWM la fiecare 2 milisecunde
  if (timpScursPWM >= perioadaPWM) 
  {
    tAnteriorPWM = timpCurentMicros;
    timpScursPWM = 0;
  }

  // trimitem HIGH sau LOW catre fiecare pin in functie de cat la suta din ciclu trebuie sa stea aprins
  for (int i = 0; i < nrLed; i++) 
  {
    unsigned long timpHigh = (valPWM[i] * perioadaPWM) / 255;
    
    if (timpScursPWM < timpHigh) 
    {
      digitalWrite(pini[i], HIGH); 
    } else 
    {
      digitalWrite(pini[i], LOW);  
    }
  }
}
