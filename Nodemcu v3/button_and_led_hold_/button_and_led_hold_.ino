int button = D1;
int led = D2;
int check = 1;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led,1);
  delay(1000);
  digitalWrite(led,0);
}
void loop()
{
  int button_state = digitalRead(button);
  if(button_state == 1){
    if(check == 1) 
      check = 0;
    else 
      check = 1;
    delay(300);
  }
  digitalWrite(led,check);
  Serial.println(check);
}
