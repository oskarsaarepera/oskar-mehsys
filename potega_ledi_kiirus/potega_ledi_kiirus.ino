void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 /* // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):*/
int butstate = digitalRead(2);

if (butstate == 1){
  digitalWrite(9, HIGH); 
  delay (150); 
  digitalWrite(9, LOW); 
  delay (150); 
}
else {
  digitalWrite(9, HIGH); 
  delay (500); 
  digitalWrite(9, LOW); 
  delay (500); 
}
  
}
