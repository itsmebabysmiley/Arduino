int buttonPin = D1;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin,INPUT); //input from button
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); //read input from D1
  if(buttonState == HIGH){
    Serial.print("ON ");
    Serial.println(buttonState);
  }
  else{
    Serial.print("OFF ");
    Serial.println(buttonState);
  }
}
