//lab 2 prob 2

void setup() {
  
  Serial.begin(9600);
  
  for (byte i=8; i<=13; i++)
  {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  int nr;
  nr=Serial.parseInt();
  //Serial.print("am primit nr: ");
  Serial.println(nr);
  int bit;
  for(bit=0; bit<6; bit++)
  {
    int valbit=bitRead(nr, bit);
    digitalWrite(8+bit, valbit);
    delay(500);
  }
  //delay(500);
}
