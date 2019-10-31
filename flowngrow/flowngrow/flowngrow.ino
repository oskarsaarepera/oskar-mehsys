// included libraries
#include <Wire.h>
#include "RTClib.h"

// pump connection pins
int pump1 = 5;  
int pump2 = 3;
int pump3 = 6;

// led pin
int led = 7; 

// moisture sensor pins
int pott1 = A1; 
int pott2 = A2;
int pott3 = A3;

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

// rtc setup
RTC_DS1307 rtc;

// variables for calculating clock
int period = 3600;
unsigned long time_now = 0;

// variables for smoothing purposes
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total




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
  vesi();
  
  DateTime now = rtc.now();
    if(now.unixtime() > time_now + period){
        time_now = now.unixtime(); 
        
        //check moisture in first pot
        moist1 = kontroll1();
        if (moist1>=drysoil){
          digitalWrite(pump1, HIGH);
          delay(2000);  
          digitalWrite(pump1, LOW);
        }

        //check moisture in second pot
        moist2 = kontroll2();
        if (moist2>=drysoil){
          digitalWrite(pump2, HIGH);
          delay(2000*1.44);   //coeficient dependant on pot height, determined by testing
          digitalWrite(pump2, LOW);
        }

        //check moisture in third pot
        moist3 = kontroll3();
        if (moist3>=drysoil){
          digitalWrite(pump3, HIGH);
          delay(2000*1.66);   //coeficient dependant on pot height, determined by testing
          digitalWrite(pump3, LOW);
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
}

//code for pump testing, uncomment if needed
/*
void pumbatest(){
  digitalWrite(pump1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(pump1, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  digitalWrite(pump2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(pump2, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  digitalWrite(pump3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(pump3, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
}
*/

//code for checking moisture. Reads 10 times, each after 10sec, outputs average value
int kontroll1(){
  //cycle that goes around 10 times
  for (readIndex = 0; readIndex<numReadings; readIndex++){
      //add moisture values to the array "readings"
      readings[readIndex] = analogRead(pott1);
      //add the reading to the total:
      total = total + readings[readIndex];
      //delay between readings to get an average over a longer period of time
      delay(10); //10 second delay
      }
      
  //calculate the average
  moist1 = total / numReadings;
  //send it to the computer for debugging
  Serial.print("esimene pott: ");
  Serial.print(moist1);
  
  //write variables back to 0 for next checking
  readIndex = 0;     // the index of the current reading
  total = 0;         // the running total
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {  //the array of readings
    readings[thisReading] = 0;
  }
  
  //return the calculated value to decide if watering is needed
  return(moist1);
}


//same code as previous but without comments and changed variables
int kontroll2(){
  for (readIndex = 0; readIndex<numReadings; readIndex++){
      readings[readIndex] = analogRead(pott2);
      total = total + readings[readIndex];
      delay(10);
      }
      
  moist2 = total / numReadings;
  Serial.print("esimene pott: ");
  Serial.print(moist2);
  
  readIndex = 0;
  total = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  return(moist2);
}


//same code as previous but without comments and changed variables
int kontroll3(){
  for (readIndex = 0; readIndex<numReadings; readIndex++){
      readings[readIndex] = analogRead(pott3);
      total = total + readings[readIndex];
      delay(10);
      }
      
  moist3 = total / numReadings;
  Serial.print("esimene pott: ");
  Serial.print(moist3);
  
  readIndex = 0;
  total = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  return(moist3);
}
