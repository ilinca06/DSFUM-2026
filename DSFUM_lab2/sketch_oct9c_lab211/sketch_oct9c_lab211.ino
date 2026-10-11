//lab 2 prob 1

void setup() {
    for(byte i=8; i<=13; i++)
        pinMode(i, OUTPUT);
}

void loop() {
    for(byte nr=0; nr<=63; nr++)
    {
        int bit;
        for(bit=0; bit<6; bit++)
        {
          int valbit=bitRead(nr, bit);
          digitalWrite(8+bit, valbit);
        }
        delay(500);
        //digitalWrite(i, 1);  
        //delay(300);
        //digitalWrite(i, 0);      
    }
}