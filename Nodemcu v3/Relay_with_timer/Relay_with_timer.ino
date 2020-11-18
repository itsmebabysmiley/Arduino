int Relay1 = D5;
int count = 1;
int limits_time;
void setup()
{
  pinMode(Relay1, OUTPUT); 
  Serial.begin(9600);
  delay(3000);
  Serial.println("Time start in");
  delay(1000);
  Serial.print("3");
  delay(1000);
  Serial.print(" 2");
  delay(1000);
  Serial.print(" 1");
  limits_time = 10;
}
void loop()
{
  Serial.print(count);
  if(count > 10){
      Serial.println("Relay off");
      digitalWrite(Relay1, 1);
      Serial.print("Reset in");
      delay(1000);
      Serial.print("3");
      delay(1000);
      Serial.print(" 2");
      delay(1000);
      Serial.print(" 1");
      count = 1;
    
  }
  else{
      Serial.println("Relay on");
      digitalWrite(Relay1, 0);
  }
  delay(1000);
  count++;
  
}
