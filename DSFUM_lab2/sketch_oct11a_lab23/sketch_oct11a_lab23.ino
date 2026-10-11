// lab  2 prob 3

int ledPin =  9; //primul cu ~
int brightness = 0; //pleaca cu luminozitete 0
int fade = 5; //amplifica sau scade luminozitetea cu 5(max 255)

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    //aplicam luminozitatea curenta pe pinul ledului
    analogWrite(ledPin, brightness);

    //modificam luminozitatea
    brightness = fade + brightness;

    if(brightness <= 0 or brightness >=255)
    {
      fade = -fade;
    }

    delay(30);
}