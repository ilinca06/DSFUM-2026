// lab 2 prob 5

int pinNonPWM = 8;
unsigned long timpAnterior = 0;
int valoarePWM = 0; // intre 0 și 255
int perioada = 2000; // 2000 microsecunde = 2 milisecunde 

void setup() 
{
  pinMode(pinNonPWM, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  //citim valoarea (0-255) 
  if (Serial.available() > 0)
  {
    int val = Serial.parseInt();
    if (val > 0 || val == 0)
    {
      valoarePWM = constrain(val, 0, 255);
    }
  }

  //Calculam cat timp sta pe HIGH si cat pe LOW
  unsigned long timpHigh = (valoarePWM * perioada) / 255;
  unsigned long timpCurent = micros();
  unsigned long timpScurs = timpCurent - timpAnterior;

  //generam semnalul PWM manual 
  if (timpScurs < timpHigh) 
  {
    digitalWrite(pinNonPWM, HIGH);
  } else if (timpScurs < perioada) 
  {
    digitalWrite(pinNonPWM, LOW);
  } else 
  {
    //resetam ciclul dupa 2000 de microsecunde
    timpAnterior = timpCurent;
  }
}