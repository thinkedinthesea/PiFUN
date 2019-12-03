/*
   THINKEDINTHESEA
   #PiFUN

* ****** rev031219
   release 2
 * ****************

 * ****** rev061119
   release 1
 * ****************

   ATTINY84 PINS
   -------------
   PIN  ARDUINOPIN   TYPE             ALIAS        RPI-PIN        DESCRIPTION
   --------------------------------------------------------------------------------------------------------------------------
   11   2            OUTPUT           JRIGHT       BCM 22         movimento destro attivato dallo stick. Attivo basso
   10   3            OUTPUT           JLEFT        BCM 27         movimento sinistro attivato dallo stick. Attivo basso
   9    4            OUTPUT           JDOWN        BCM 17         movimento giu attivato dallo stick. Attivo basso
   8    5            OUTPUT           JUP          BCM 4          movimento su attivato dallo stick. Attivo basso
   7    6            ANALOG-IN        XINPUT       ######         ingresso analogico asse X dello stick
   6    7            ANALOG-IN        YINPUT       ######         ingresso analogico asse Y dello stick
   --------------------------------------------------------------------------------------------------------------------------
*/
//
//definiamo le costanti
const int JRIGHT = 2;
const int JLEFT = 3;
const int JDOWN = 4;
const int JUP = 5;
//ingressi analogici dello stick
int XINPUT = A6;
int YINPUT = A7;
//variabili per memorizzare il valore di XINPUT ed YINPUT
int Xval = 0;
int Yval = 0;
//soglie di isteresi dello stick
int HL = 460;
int HH = 600;

void setup() {
  //dichiariamo i pin
  pinMode (JRIGHT, OUTPUT);
  pinMode (JLEFT, OUTPUT);
  pinMode (JDOWN, OUTPUT);
  pinMode (JUP, OUTPUT);
  //
  //comandiamo gli output dello stick a riposo alti
  digitalWrite(JRIGHT, HIGH);
  digitalWrite(JLEFT, HIGH);
  digitalWrite(JUP, HIGH);
  digitalWrite(JDOWN, HIGH);
}

void loop() {
  Xval = analogRead(XINPUT);
  delay(100);
  Yval = analogRead(YINPUT);
  //delay(100);
  //li confrontiamo e comandiamo gli output
  if ((Xval > HL) && (Xval < HH)) {
    digitalWrite(JLEFT, HIGH);
    digitalWrite(JRIGHT, HIGH);
  }
  if (Xval < HL) {
    digitalWrite(JLEFT, LOW);
    digitalWrite(JRIGHT, HIGH);
  }
  if (Xval > HH) {
    digitalWrite(JLEFT, HIGH);
    digitalWrite(JRIGHT, LOW);
  }
  //////
  //
  if ((Yval > HL) && (Yval < HH)) {
    digitalWrite(JUP, HIGH);
    digitalWrite(JDOWN, HIGH);
  }
  if (Yval < HL) {
    digitalWrite(JUP, LOW);
    digitalWrite(JDOWN, HIGH);
  }
  if (Yval > HH) {
    digitalWrite(JUP, HIGH);
    digitalWrite(JDOWN, LOW);
  }
}
