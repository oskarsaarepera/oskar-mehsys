void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
int butstate = digitalRead(2); //loeb nupu väärtust, 1 või 0.
Serial.println(butstate);
if (butstate == 1){
  digitalWrite(9, HIGH); 
  //delay (100); 
}

else{
  digitalWrite(9, LOW); 
  //delay (100); 
}


}
