// lab 2 prob 6

int pinNonPWM = 8;

//efectul Fade 
unsigned long timpAnteriorFade = 0;
int intervalFade = 15; 
int valoarePWM = 0;
int fadeAmount = 5;

unsigned long timpAnteriorPWM = 0;
int perioadaPWM = 2000; // 2 milisecunde per ciclu luminos

void setup() 
{
  pinMode(pinNonPWM, OUTPUT);
}

void loop() 
{
  unsigned long timpCurentMillis = millis();
  unsigned long timpCurentMicros = micros();

  //calculam noua valoare a luminozitatii (de la 0 la 255)
  if (timpCurentMillis - timpAnteriorFade >= intervalFade) 
  {
    timpAnteriorFade = timpCurentMillis;
    valoarePWM = valoarePWM + fadeAmount;
    
    if (valoarePWM <= 0 || valoarePWM >= 255) 
    {
      fadeAmount = -fadeAmount;
    }
  }

  //PWM: aplicam valoarea calculata mai sus pe pinul 8
  unsigned long timpHigh = (valoarePWM * perioadaPWM) / 255;
  unsigned long timpScursPWM = timpCurentMicros - timpAnteriorPWM;

  if (timpScursPWM < timpHigh) 
  {
    digitalWrite(pinNonPWM, HIGH); // tine LED-ul aprins o fractiune de timp
  } else if (timpScursPWM < perioadaPWM) 
  {
    digitalWrite(pinNonPWM, LOW);  // tine LED-ul stins restul ciclului
  } else 
  {
    timpAnteriorPWM = timpCurentMicros; // resetam ciclul PWM
  }
}