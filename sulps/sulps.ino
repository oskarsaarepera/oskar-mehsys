
//pushbutton pin
const int buttonPin = A0;

//ledpinid
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;
const int led7 = 8;
const int led8 = 9;
const int led9 = 10;
const int led10 = 11;
const int led11 = 12;
const int led12 = 13;
int dummy;
int dummy2;
int dummy3;
int dummy4;
int dummy5;
int dummy6;
int dummy7;
// variables will change:
int buttonState = 0;

void setup() {
  // ledpinide mode
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led6, OUTPUT);
  pinMode (led7, OUTPUT);
  pinMode (led8, OUTPUT);
  pinMode (led9, OUTPUT);
  pinMode (led10, OUTPUT);
  pinMode (led11, OUTPUT);
  pinMode (led12, OUTPUT);
 
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
  
}

void loop() {
  int eredusMassiiv[7] = {255, 200, 120, 80, 40, 20, 0};
  int paremMassiiv[13] = {led7, led8, led9, led10, led11, led12, dummy, dummy, dummy, dummy, dummy, dummy, dummy};
  int vasakMassiiv[13] = {led6, led5, led4, led3, led2, led1, dummy, dummy, dummy, dummy, dummy, dummy, dummy};

  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  Serial.println(buttonState);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    for(int n=0; n<=14; n++){
    analogWrite(paremMassiiv[n], eredusMassiiv[0]);
    analogWrite(paremMassiiv[n-1], eredusMassiiv[1]);
    analogWrite(paremMassiiv[n-2], eredusMassiiv[2]);
    analogWrite(paremMassiiv[n-3], eredusMassiiv[3]);
    analogWrite(paremMassiiv[n-4], eredusMassiiv[4]);
    analogWrite(paremMassiiv[n-5], eredusMassiiv[5]);
    analogWrite(paremMassiiv[n-6], eredusMassiiv[6]);
    delay(75);
    }
  } 
  else {
  }
}
