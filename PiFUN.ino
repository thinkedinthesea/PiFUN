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
   11   2            OUTPUT           JRIGHT       BCM 22         right stick. Active low
   10   3            OUTPUT           JLEFT        BCM 27         left stick. Active low
   9    4            OUTPUT           JDOWN        BCM 17         down stick. Active low
   8    5            OUTPUT           JUP          BCM 4          up stick. Active low
   7    6            ANALOG-IN        XINPUT       ######         x analog input
   6    7            ANALOG-IN        YINPUT       ######         y analog input
   --------------------------------------------------------------------------------------------------------------------------
*/
//
//declarations
const int JRIGHT = 2;
const int JLEFT = 3;
const int JDOWN = 4;
const int JUP = 5;
//analog stick input
int XINPUT = A6;
int YINPUT = A7;
//store the value of XINPUT and YINPUT
int Xval = 0;
int Yval = 0;
//thresholds for stick
int HL = 460;
int HH = 600;

void setup() {
  //
  pinMode (JRIGHT, OUTPUT);
  pinMode (JLEFT, OUTPUT);
  pinMode (JDOWN, OUTPUT);
  pinMode (JUP, OUTPUT);
  //
  //all output high
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
  //compare with thresholds values and activate outputs
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
