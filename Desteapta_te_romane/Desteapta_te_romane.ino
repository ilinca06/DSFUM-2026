//lab 4

// Desteapta-te, romane!  -  imnul Romaniei 

#define PIN_BUZZER 3     // pinul la care este conectat buzzer-ul
#define UNITATE    60    
#define NR_STROFE  4     

#define si       247     // Si3 - de sub cheia Sol
#define Mi       330     // Mi4
#define Fa_diez  370     // Fa#4
#define Sol      392     // Sol4
#define La       440     // La4
#define Si       494     // Si4
#define DO       523     // Do5
#define RE       587     // Re5
#define MI       659     // Mi5

int octava = 1;          // 2 sau 4 daca buzzer-ul se aude slab 

#define NR_PERECHI(sir) (sizeof(sir) / sizeof(sir[0]) / 2)

// anacruza: "Des-"
const int anacruza[] = {
  si,8
};

// masurile 1-10
const int inceput[] = {
  Mi,12,   Fa_diez,4,  Sol,8,      La,8,          // teap-ta-te ro-
  Si,16,   Mi,8,       Mi,8,                       // ma-ne din
  DO,12,   Si,4,       La,8,       La,8,          // som-nul cel de
  RE,12,   DO,4,       Si,8,       Si,8,          // moar-te In
  MI,12,   RE,4,       DO,4,       Si,4,   La,8,  // ca-re te-a-dan
  Si,8,    Sol,16,     La,8,                       // ci-ra bar
  Si,12,   La,4,       Sol,8,      Fa_diez,8,     // ba-rii de ti-
  Mi,12,   Fa_diez,4,  Sol,8,      La,8,          // ra-ni bar
  Si,8,    La,4,       Sol,4,      Fa_diez,8,  Sol,8,  // ba-rii de ti-
  Mi,24,   Mi,8                                    // ra-ni! A-
};

// refrenul "Acum ori niciodata..." (9 masuri) - se canta de doua ori
const int refren[] = {
  Mi,12,   MI,4,       MI,8,       MI,8,          // cum ori nici-o-
  MI,16,   RE,8,       RE,8,                       // da-ta cro-
  MI,12,   RE,4,       DO,4,       Si,4,   La,8,  // ies-te-ti al-ta
  RE,12,   DO,4,       Si,8,       Si,8,          // soar-te La
  MI,12,   RE,4,       DO,4,       Si,4,   La,8,  // ca-re sa se-n-
  Si,8,    Sol,16,     La,8,                       // chi-ne si
  Si,12,   La,4,       Sol,8,      Fa_diez,8,     // cru-zii tai dus-
  Mi,12,   Fa_diez,4,  Sol,8,      La,8,          // ma-ni si
  Si,8,    La,4,       Sol,4,      Fa_diez,8,  Sol,8   // cru-zii tai dus-
};

// masura dintre cele doua refrene
const int punte[] = {
  Mi,24,   Mi,8                                    // ma-ni! A-
};

// finalul "1.2.3.": Mi cu punct + anacruza strofei urmatoare
const int final_1_2_3[] = {
  Mi,24,   si,8                                    // ma-ni! (2. A-)
};

// finalul "4."
const int final_4[] = {
  Mi,24                                            // ma-ni!
};

void canta(const int partitura[], int nrPerechi) {
  for (int i = 0; i < nrPerechi; i++) {
    int frecventa = partitura[i * 2] * octava;
    int durata = partitura[i * 2 + 1] * UNITATE;   // in milisecunde
    tone(PIN_BUZZER, frecventa, durata * 9 / 10);  
    delay(durata);
    noTone(PIN_BUZZER);
  }
}

void setup() {
  delay(1000);
  canta(anacruza, NR_PERECHI(anacruza));

  for (int strofa = 1; strofa <= NR_STROFE; strofa++) {
    canta(inceput, NR_PERECHI(inceput));
    canta(refren, NR_PERECHI(refren));
    canta(punte, NR_PERECHI(punte));
    canta(refren, NR_PERECHI(refren));

    if (strofa < NR_STROFE) {
      canta(final_1_2_3, NR_PERECHI(final_1_2_3));
    } else {
      canta(final_4, NR_PERECHI(final_4));
    }
  }
}

void loop() {

}
