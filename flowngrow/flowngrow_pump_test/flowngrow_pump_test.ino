// pump connection pins
int pump1 = 5;  
int pump2 = 3;
int pump3 = 6;

void setup() {
  //set pumps to output
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);

  
  digitalWrite(pump1, HIGH);  //turn on pump
  delay(2000);                //wait 2 seconds
  digitalWrite(pump1, LOW);   //turn off pump
  delay(1000);                //wait 1 second
  digitalWrite(pump2, HIGH);
  delay(2000);
  digitalWrite(pump2, LOW);
  delay(1000);
  digitalWrite(pump3, HIGH);
  delay(2000);
  digitalWrite(pump3, LOW);
  delay(1000);
}

void loop() {
 //no loop in this code, reset to try again

}
