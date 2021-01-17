int sw1 = D0;
int sw2 = D6;
int sw3 = D7;
int relay1 = D3;
int relay2 = D8;
int coin_signal = D5;

int coin = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
//  attachInterrupt(digitalPinToInterrupt(sw3), getCoin, RISING );
  pinMode(coin_signal, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(sw1, LOW);
  digitalWrite(sw2, LOW);
  digitalWrite(sw3, LOW);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}
boolean a = false;
boolean c = true;
boolean k = true;
boolean d = false;
boolean sw1_state = true;
boolean sw2_state = true;
int count = 0;
boolean check = true;
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Insert coin");
  L1:
  int coin_s = digitalRead(coin_signal);
  if(coin_s){
    coin += 5;
    delay(40);
    coin_s = 0;
    d = true;
  }
  if(d){
    Serial.printf("coin: %d\n", coin);
    Serial.println("Choose water(1) or foam(2)"); 
    Serial.print("sw1 state=");Serial.println(sw1_state);
    Serial.print("sw2 state=");Serial.println(sw2_state);
    d = false;
  }
  if((digitalRead(sw1) || digitalRead(sw2)) && coin > 0){
    d = true;
    if(digitalRead(sw1)){
      while(digitalRead(sw1)){
        delay(50);
      }
      sw1_state = true;
      //water();
      doCountTime("water", sw1, relay1, 3);
      k = true;
      if(coin <= 0 ){
        c = true; 
      }
      if(sw1_state && sw2_state){
        goto L1;
      }
    }//switch 1
    if(digitalRead(sw2)){
      while(digitalRead(sw2)){
        delay(50);
      }
      sw2_state = true;
      //foam();
      doCountTime("foam", sw2, relay2, 1);
      k = true;
      if(coin <= 0 ){
        c = true; 
      }
      if(sw1_state && sw2_state){
        goto L1;
      }
    }//switch2
    if(digitalRead(sw3)){
      setting();
    }
  }//if 3 condition 
}//loop

void doCountTime(String type,int sw ,int relay, int _time){
  delay(1000);
  Serial.println(type);
  int cTime = 0;
  int pTime = millis();
  int sec = 0;
  while(coin > 0 ){
    digitalWrite(relay, HIGH);
    cTime = millis();
    if(digitalRead(sw)){
      while(digitalRead(sw)){
        delay(50);
      }
      digitalWrite(relay, LOW);
      Serial.println("Paused");
      if(type.equals("water")){
        sw1_state = true;
      }else{
        sw2_state = true;
      }
      return;
    }
    if(cTime-pTime >= 1000){
      Serial.printf("previous: %d current: %d \n",pTime,cTime);
      pTime = cTime;
      sec++;
      delay(50);
    }
    if(sec == _time){
      sec = 0;
      coin --;
      Serial.println(coin);
    }
  }//while coin
  digitalWrite(relay, LOW);
  if(type.equals("water")){
    sw1_state = true;
  }else{
    sw2_state = true;
  }
}//docounttime

void setting(){
  Serial.println("Setting");
  delay(1000);
  
}
