int LEDD4 = D1;
void setup() {
  pinMode(LEDD4, OUTPUT); //set D1 to be output
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDD4, HIGH);
  delay(1000);
  digitalWrite(LEDD4, LOW); 
  delay(1000);
  
}
