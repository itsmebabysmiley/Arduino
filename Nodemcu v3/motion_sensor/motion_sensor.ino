int sensor= D1;
int led = D2;
void setup(){
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int value= digitalRead(sensor);
  Serial.println(value);
  if(value == 1){
    digitalWrite(led,HIGH);
    delay(1000*3);
  }
  else{
    digitalWrite(led,LOW);
  }
}
