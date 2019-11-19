/*
   THINKEDINTHESEA
   #PiFUN

 * ****** rev061119
   first release
 * ****************

   ATTINY84 PINS
   -------------
   PIN  ARDUINOPIN   TYPE             ALIAS        RPI-PIN        DESCRIPTION
   --------------------------------------------------------------------------------------------------------------------------
   13   0            INPUT            RPI          BCM 23         segnale di vitalità del raspberry. Attivo alto
   12   1            OUTPUT           JRIGHT       BCM 22         movimento destro attivato dallo stick. Attivo basso
   11   2            OUTPUT           JLEFT        BCM 27         movimento sinistro attivato dallo stick. Attivo basso
   10   3            OUTPUT           JDOWN        BCM 17         movimento giu attivato dallo stick. Attivo basso
   9    4            OUTPUT           JUP          BCM 7          movimento su attivato dallo stick. Attivo basso
   8    5            INPUT            POWER        ######         pulsante di accensione. Attivo basso
   7    6            ANALOG-IN        XINPUT       ######         ingresso analogico asse X dello stick
   6    7            ANALOG-IN        YINPUT       ######         ingresso analogico asse Y dello stick
   5    8            OUTPUT           MOSFET       ######         comando del mosfet per alimentazione al raspberry
   2    10           OUTPUT           WD           BCM 10         verso il raspberry, serve per comandare shutdown/reboot
   --------------------------------------------------------------------------------------------------------------------------
*/
//
//definiamo le costanti
const int RPI = 0;
const int JRIGHT = 1;
const int JLEFT = 2;
const int JDOWN = 3;
const int JUP = 4;
const int POWER = 5;
const int MOSFET = 8;
const int WD = 10;
const int XINPUT = A6;
const int YINPUT = A7;
//variabili per memorizzare il valore di XINPUT ed YINPUT
int Xval = 0;
int Yval = 0;
//variabili per contatori di tempo
int TEMPO = 0;
//indica quanto tempo in secondi dobbiamo attendere il segnale di vitalità del raspberry
int MAXWDWAIT = 50;
//
//variabile usata per i vari cicli. Se messa ad 1 scavalca il ciclo iniziale
int REBOOT = 0;

void setup() {
  //dichiariamo i pin/*
   THINKEDINTHESEA
   #PiFUN

 * ****** rev061119
   first release
 * ****************

   ATTINY84 PINS
   -------------
   PIN  ARDUINOPIN   TYPE             ALIAS        RPI-PIN        DESCRIPTION
   --------------------------------------------------------------------------------------------------------------------------
   13   0            INPUT            RPI          BCM 23         segnale di vitalità del raspberry. Attivo alto
   12   1            OUTPUT           JRIGHT       BCM 22         movimento destro attivato dallo stick. Attivo basso
   11   2            OUTPUT           JLEFT        BCM 27         movimento sinistro attivato dallo stick. Attivo basso
   10   3            OUTPUT           JDOWN        BCM 17         movimento giu attivato dallo stick. Attivo basso
   9    4            OUTPUT           JUP          BCM 4          movimento su attivato dallo stick. Attivo basso
   8    5            INPUT            POWER        ######         pulsante di accensione. Attivo basso
   7    6            ANALOG-IN        XINPUT       ######         ingresso analogico asse X dello stick
   6    7            ANALOG-IN        YINPUT       ######         ingresso analogico asse Y dello stick
   5    8            OUTPUT           MOSFET       ######         comando del mosfet per alimentazione al raspberry
   2    10           OUTPUT           WD           BCM 10         verso il raspberry, serve per comandare shutdown/reboot
   --------------------------------------------------------------------------------------------------------------------------
*/
//
//definiamo le costanti
const int RPI = 0;
const int JRIGHT = 1;
const int JLEFT = 2;
const int JDOWN = 3;
const int JUP = 4;
const int POWER = 5;
const int MOSFET = 8;
const int WD = 10;
//ingressi analogici dello stick
int XINPUT = A6;
int YINPUT = A7;
//variabili per memorizzare il valore di XINPUT ed YINPUT
int Xval = 0;
int Yval = 0;
//soglie di isteresi dello stick
int HL = 460;
int HH = 600;
//variabili per contatori di tempo
int TEMPO = 0;
//indica quanto tempo in secondi dobbiamo attendere il segnale di vitalità del raspberry
int MAXWDWAIT = 50;
//
//variabile usata per i vari cicli. Se messa ad 1 scavalca il ciclo iniziale
int REBOOT = 0;

void setup() {
  //dichiariamo i pin
  pinMode (RPI, INPUT);
  pinMode (JRIGHT, OUTPUT);
  pinMode (JLEFT, OUTPUT);
  pinMode (JDOWN, OUTPUT);
  pinMode (JUP, OUTPUT);
  pinMode (POWER, INPUT);
  pinMode (MOSFET, OUTPUT);
  pinMode (WD, OUTPUT);
  //
  //assicuriamoci che il mosfet sia aperto
  digitalWrite(MOSFET, LOW);
}

void loop() {
  //ripetiamo finchè non viene premuto il pulsante di power
  while (digitalRead(POWER) == HIGH){
    //bla bla bla
  }
  //
  //qualcuno ha premuto, comandiamo il mosfet
  digitalWrite(MOSFET, HIGH);
  //inviamo la nostra vitalità al raspberry
  digitalWrite(WD, HIGH);
  //
  //adesso dobbiamo attendere il segnale RPI di vitalità dal raspberry
  //utilizziamo la funzione checkRPI()
  checkRPI();
  //
  //se la variabile REBOOT è 0 allora abbiamo ricevuto correttamente il segnale di vitalità dal raspberry
  //se messa ad 1 allora siamo andati in timeout e ritorniamo all'inizio del loop
  if (REBOOT == 0){
    //adesso possiamo iniziare con lo stick
    //facciamo un ciclo che dura fintanto che riceve la vitalità dal raspberry
    //prende i 2 valori analogici
    //comanda i relativi output bassi
    //in ultimo sente se il pulsante di power viene premuto
    //
    //
    //sentimo la vitalità del raspberry. Se viene meno aspettiamo 20 secondi
    //per capire se è stato comandato un riavvio
    while (digitalRead(RPI) == HIGH){
      //prendiamo i valori analogici
      //campiona a 10bit quindi prende valori da 0 a 1023
      //lasciamo isteresi nel range 500 <-> 524
      Xval = analogRead(XINPUT);
      delay(100);
      Yval = analogRead(YINPUT);
      //delay(100);
      //li confrontiamo e comandiamo gli output
      if ((Xval > HL) && (Xval < HH)){
        digitalWrite(JLEFT, LOW);
        digitalWrite(JRIGHT, LOW);
      }
      if (Xval < HL) {
        digitalWrite(JLEFT, HIGH);
        digitalWrite(JRIGHT, LOW);
      } 
      if (Xval > HH){
        digitalWrite(JLEFT, LOW);
        digitalWrite(JRIGHT, HIGH);
      }
      //////
      //
      if ((Yval > HL) && (Yval < HH)){
        digitalWrite(JUP, LOW);
        digitalWrite(JDOWN, LOW);
      }
      if (Yval < HL) {
        digitalWrite(JUP, HIGH);
        digitalWrite(JDOWN, LOW);
      } 
      if (Yval > HH){
        digitalWrite(JUP, LOW);
        digitalWrite(JDOWN, HIGH);
      }
      //////////////////////////////////////////
      //sentiamo il pulsante di power
      if (digitalRead(POWER) == LOW){
        //pulsante premuto
        //mettiamo la nostra vitalità bassa così raspberry effettua lo shutdown
        digitalWrite(WD, LOW);
      }
    }
    //perso la vitalità aspettiamo 10 secondi e vediamo se si riprende
    while (digitalRead(RPI) == LOW){
      TEMPO = 1;
      delay(1000);
      TEMPO++;
      if (TEMPO > 10){
        //passati 10 secondi spegniamo
        digitalWrite(MOSFET, LOW);
        break;
      }
    }
  }
}
//
//
//funzione checkRPI
//attende per un determinato tempo il segnale di vitalità dal raspberry
//se non lo riceve apre il mosfet
void checkRPI(){
  TEMPO = 1;
  //cicliamo finchè RPI non è alto
  while (digitalRead(RPI) == LOW){
    //aumentiamo la variabile tempo
    delay(1000);
    TEMPO++;
    //confrontiamo TEMPO con MAXWDWAIT per sapere se siamo in timeout
    if (TEMPO > MAXWDWAIT){
      //siamo in timeout apriamo il mosfet
      digitalWrite(MOSFET, LOW);
      REBOOT = 1;
      //usciamo dal ciclo
      break;
    }
  }
}
  pinMode (RPI, INPUT);
  pinMode (JRIGHT, OUTPUT);
  pinMode (JLEFT, OUTPUT);
  pinMode (JDOWN, OUTPUT);
  pinMode (JUP, OUTPUT);
  pinMode (POWER, INPUT);
  pinMode (MOSFET, OUTPUT);
  pinMode (WD, OUTPUT);
  //
  //assicuriamoci che il mosfet sia aperto
  digitalWrite(MOSFET, LOW);
}

void loop() {
  //ripetiamo finchè non viene premuto il pulsante di power
  while (digitalRead(POWER) == HIGH){
    //bla bla bla
  }
  //
  //qualcuno ha premuto, comandiamo il mosfet
  digitalWrite(MOSFET, HIGH);
  //inviamo la nostra vitalità al raspberry
  digitalWrite(WD, HIGH);
  //
  //adesso dobbiamo attendere il segnale RPI di vitalità dal raspberry
  //utilizziamo la funzione checkRPI()
  checkRPI();
  //
  //se la variabile REBOOT è 0 allora abbiamo ricevuto correttamente il segnale di vitalità dal raspberry
  //se messa ad 1 allora siamo andati in timeout e ritorniamo all'inizio del loop
  if (REBOOT == 0){
    //adesso possiamo iniziare con lo stick
    //facciamo un ciclo che dura fintanto che riceve la vitalità dal raspberry
    //prende i 2 valori analogici
    //comanda i relativi output bassi
    //in ultimo sente se il pulsante di power viene premuto
    //
    //
    //sentimo la vitalità del raspberry. Se viene meno aspettiamo 20 secondi
    //per capire se è stato comandato un riavvio
    while (digitalRead(RPI) == HIGH){
      //prendiamo i valori analogici
      Xval = analogRead(XINPUT);
      delay(100);
      Yval = analogRead(YINPUT);
      delay(100);
      //li confrontiamo e comandiamo gli output
      //todo
      //////
      //sentiamo il pulsante di power
      if (digitalRead(POWER) == LOW){
        //pulsante premuto
        //mettiamo la nostra vitalità bassa così raspberry effettua lo shutdown
        digitalWrite(WD, LOW);
        //adesso aspettiamo che la vitalità di raspberry va bassa
        //quando succede contiamo fino a 10 secondi e poi spegniamo
      }
    }
    //perso la vitalità aspettiamo 20 secondi e vediamo se si riprende
    while (digitalRead(RPI) == LOW){
      
    }
    
  }
}
//
//
//funzione checkRPI
//attende per un determinato tempo il segnale di vitalità dal raspberry
//se non lo riceve apre il mosfet
void checkRPI(){
  TEMPO = 1;
  //cicliamo finchè RPI non è alto
  while (digitalRead(RPI) == LOW){
    //aumentiamo la variabile tempo
    delay(1000);
    TEMPO++;
    //confrontiamo TEMPO con MAXWDWAIT per sapere se siamo in timeout
    if (TEMPO > MAXWDWAIT){
      //siamo in timeout apriamo il mosfet
      digitalWrite(MOSFET, LOW);
      REBOOT = 1;
      //usciamo dal ciclo
      break;
    }
  }
}
