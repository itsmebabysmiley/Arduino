int sw1 = D0;
int sw2 = D6;
int sw3 = D7;
int relay1 = D3;
int relay2 = D8;
int sw1_state = HIGH;
int sw2_state = HIGH;

int coin = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  //pinMode(sw3, INPUT);
  attachInterrupt(digitalPinToInterrupt(sw3), getCoin, RISING );
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(sw1, LOW);
  digitalWrite(sw2, LOW);
  digitalWrite(sw3, LOW);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}
boolean c = true;
boolean k = true;
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Insert coin");
  if(c){
    Serial.println("Insert coin");
    c = false;
  }
  while(coin>0){
    delay(50);
    if(k){
      Serial.printf("coin: %d\n", coin);
      Serial.println("Choose water(1) or foam(2)");  
      k = false;
    }
    if(digitalRead(sw1)){
      digitalWrite(relay1, HIGH);
      while(digitalRead(sw1)){
        delay(50);
      }
      digitalWrite(relay1, LOW);
      water();
      Serial.println("hi");
      k = true;
      if(coin <= 0 ){
        c = true; 
      }
    }//switch 1
    
  }//while coin

}

void water(){
  delay(1000);
  int cTime = 0;
  int pTime = millis();
  while(coin > 0 ){
    digitalWrite(relay1, HIGH);
    cTime = millis();
    if(digitalRead(sw1)){
      while(digitalRead(sw1)){
        delay(50);
      }
      digitalWrite(relay1, LOW);
      Serial.println("Paused");
      return;
    }
    if(cTime-pTime >= 1000){
      pTime = cTime;
      Serial.printf("previous: %d current: %d \n",pTime,cTime);
      coin --;
      Serial.println(coin);
      delay(50);
    }
  }//while coin
  digitalWrite(relay1, LOW);
}


ICACHE_RAM_ATTR void getCoin(){
  coin = 10;
}
