// lab 2 prob 7

const int nrLeduri = 6;

// vectori: fiecare pozitie (de la 0 la 5) corespunde unui LED
int pini[nrLeduri] = {8, 9, 10, 11, 12, 13};
int valoarePWM[nrLeduri] = {0, 50, 100, 150, 200, 250}; // puncte de pornire diferite
int fadeAmount[nrLeduri] = {5, 5, 5, 5, 5, 5};
int intervalViteza[nrLeduri] = {10, 15, 20, 25, 30, 35}; // fiecare LED are viteza proprie de fade

unsigned long timpAnteriorFade[nrLeduri] = {0, 0, 0, 0, 0, 0};
unsigned long timpAnteriorPWM = 0;
const int perioadaPWM = 2000;

void setup() 
{
  for (int i = 0; i < nrLeduri; i++) 
  {
    pinMode(pini[i], OUTPUT);
  }
}

void loop() {
  unsigned long timpCurentMillis = millis();
  unsigned long timpCurentMicros = micros();

  // Fade este independent pentru fiecare LED
  for (int i = 0; i < nrLeduri; i++) {
    if (timpCurentMillis - timpAnteriorFade[i] >= intervalViteza[i]) {
      timpAnteriorFade[i] = timpCurentMillis;
      valoarePWM[i] = valoarePWM[i] + fadeAmount[i];
      
      if (valoarePWM[i] <= 0 || valoarePWM[i] >= 255) {
        fadeAmount[i] = -fadeAmount[i];
      }
    }
  }

  // calculam ciclul comun pentru PWM
  unsigned long timpScursPWM = timpCurentMicros - timpAnteriorPWM;
  if (timpScursPWM >= perioadaPWM) {
    timpAnteriorPWM = timpCurentMicros;
    timpScursPWM = 0;
  }

  // aplicam starea HIGH/LOW pe toate cele 6 LED-uri simultan
  for (int i = 0; i < nrLeduri; i++) {
    unsigned long timpHigh = (valoarePWM[i] * perioadaPWM) / 255;
    if (timpScursPWM < timpHigh) {
      digitalWrite(pini[i], HIGH);
    } else {
      digitalWrite(pini[i], LOW);
    }
  }
}