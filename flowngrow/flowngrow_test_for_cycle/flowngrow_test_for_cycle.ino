// included libraries
#include <Wire.h>
#include "RTClib.h"

// pump connection pins
int pump1 = 5;  
int pump2 = 3;
int pump3 = 6;
int pumbad[] = {pump1, pump2, pump3};
// led pin
int led = 7; 

// moisture sensor pins
int pott1 = A1; 
int pott2 = A2;
int pott3 = A3;
int potid[]={pott1, pott2, pott3};
// water level sensor pin
int veemootja = A0;

// variables for various functions
// water level
int veetase = 0;
// dry soil threshold
int drysoil = 600;
// moisture levels
int moist1 = 0;
int moist2 = 0;
int moist3 = 0;
int niiskused[]={moist1, moist2, moist3};

// rtc setup
RTC_DS1307 rtc;

// variables for calculating clock
int period = 5;
unsigned long time_now = 0;

// variables for smoothing purposes
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average




void setup() {
  // start serial monitor for debugging purposes
  Serial.begin(9600);

  // notify if rtc is not found
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  // notfiy if rtc is not running
  if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   
   // sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }

 // initialize all the smoothing readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  //pin setups
  pinMode(led, OUTPUT);
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
  pinMode(pott1, INPUT);
  pinMode(pott2, INPUT);
  pinMode(pott3, INPUT);
  pinMode(veemootja, INPUT);
  
}

void loop() {
/*'  vesi();
  
  DateTime now = rtc.now();
    if(now.unixtime() > time_now + period){
        time_now = now.unixtime(); 
        //check moisture in every pot
        for (int i=0; i<=2; i++){
            niiskused[i] = kontroll(i);
            if (niiskused[i]>=drysoil){
                digitalWrite(pumbad[i], HIGH);
                delay(3000);
                digitalWrite(pumbad[i], LOW);
            }
        }
    }
}

void vesi (){
  int veetase = digitalRead(veemootja);
  if (veetase == HIGH) {
    digitalWrite(led, LOW);
  } 
  else {
    digitalWrite(led, HIGH);
  }
*/
pumbatest();
}
//code for pump testing, uncomment if needed
void pumbatest(){
  digitalWrite(pump1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);        // wait for a second
  Serial.println("pump1");
  digitalWrite(pump1, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  digitalWrite(pump2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  Serial.println("pump2");
  digitalWrite(pump2, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  digitalWrite(pump3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  Serial.println("pump2");
  digitalWrite(pump3, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
}
//code for checing moisture, reads 10 times, each after 10min, outputs average value
int kontroll(int i){
  
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(potid[i]);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  niiskused[i] = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.print(potid[i]);
  Serial.print(": ");
  Serial.println(niiskused[i]);
  delay(2000);        // delay in between reads for stability
  return(niiskused[i]);
}
