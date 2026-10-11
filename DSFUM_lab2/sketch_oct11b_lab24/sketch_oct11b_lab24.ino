// lab  2 prob 4

int ledPin =  9; //primul cu ~
int brightness = 0; //pleaca cu luminozitete 0
int fade = 5; //amplifica sau scade luminozitetea cu 5(max 255)

//folosim millis in loc de delay
unsigned long timpAnterior = 0;
int intervalViteza = 30;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Introdu un nr pentru intervalViteza: ");
}

void loop() {
    if(Serial.available() > 0)
    {
      int valoare = Serial.parseInt();

      // ne asiguram ca viteza sa nu fie 0 din greseala
      if(valoare > 0)
      {
        intervalViteza = valoare;
        Serial.print("Viteza noua: ");
        Serial.print(intervalViteza);
      }
    }
    
    //verificam cat timp a trecut
    unsigned long timpCurent = millis();
    
    //vedem daca a trecut un timp egal sau peste timpul interval pe care il vrem
    if (timpCurent - timpAnterior >= intervalViteza)
    {
      //salvam noul timp
      timpAnterior = timpCurent;
      //aplicam luminozitatea curenta pe pinul ledului
      analogWrite(ledPin, brightness);

      //modificam luminozitatea
      brightness = fade + brightness;

      if(brightness <= 0 or brightness >=255)
      {
        fade = -fade;
      }
    }
}