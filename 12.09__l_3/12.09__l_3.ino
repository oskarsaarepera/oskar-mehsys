


int x = 1;
void setup() {
 
pinMode(9,OUTPUT);
}

void loop() {
for (x=0; x<3; x=x+1){
  digitalWrite(9, HIGH); 
  delay (300); 
  digitalWrite(9, LOW); 
  delay (300); 
}
delay (700);
for (x=0; x<3; x=x+1){
  digitalWrite(9, HIGH); 
  delay (1000); 
  digitalWrite(9, LOW); 
  delay (1000);
}
for (x=0; x<3; x=x+1){
  digitalWrite(9, HIGH); 
  delay (300); 
  digitalWrite(9, LOW); 
  delay (300);
}

delay (2000);

 
}
