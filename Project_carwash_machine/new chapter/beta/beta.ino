#include <Arduino.h>
#include <TM1637Display.h>

#define CLK D1
#define DIO D2
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };
const uint8_t SEG_COIN[] = {
  SEG_A | SEG_F | SEG_E | SEG_D,//C
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,//O
  SEG_F | SEG_E,//i
  SEG_C | SEG_E | SEG_G//n
};
const uint8_t SEG_SET[]{
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D, //s
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_G, //e
  SEG_A | SEG_B | SEG_C,//t
  SEG_A
};
TM1637Display display(CLK, DIO);

int sw1 = D0;
int sw2 = D6;
int sw3 = D7;
int relay1 = D3;
int relay2 = D8;
int relay3 = D4;
int coin_signal = D5;
unsigned long prevTime = 0;
unsigned long curTime = 0;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
int coin = 0;
int coin_state = HIGH;
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
  pinMode(relay3, OUTPUT);
  digitalWrite(sw1, LOW);
  digitalWrite(sw2, LOW);
  digitalWrite(sw3, LOW);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, HIGH);
  prevTime = millis();
  display.setBrightness(0x00);
}
boolean a = false;
boolean k = true;
boolean d = false;
boolean sw1_state = true;
boolean sw2_state = true;
int count = 0;
boolean check = true;
void loop() {
  // put your main code here, to run repeatedly:
  //Blink 7 segments
  curTime = millis();
  if(curTime-prevTime >= 1000){
    prevTime = curTime;
    int blinkk = (curTime/1000)%2;
    Serial.println(blinkk);
    if(blinkk){
      display.setSegments(SEG_COIN); //Coin
    }else{
      if(coin <= 0){
        display.setSegments(data); //88:88
      }else{
        display.showNumberDec(coin);
      }
      
    }
  }
  L1:
  if(coin_state == HIGH){
    int coin_s = digitalRead(coin_signal);
    if(coin_s){
      coin += 5;
      delay(100);
      coin_s = 0;
      d = true;
      display.showNumberDec(coin);
    }
  }
  
  if(d){
    Serial.printf("coin: %d\n", coin);
    Serial.println("Choose water(1) or foam(2)"); 
    d = false;
  }
  if((digitalRead(sw1) || digitalRead(sw2)) && coin > 0){
    d = true;
    coin_state = LOW;
    digitalWrite(relay3, LOW);
    if(digitalRead(sw1)){
      while(digitalRead(sw1)){
        delay(50);
      }
      sw1_state = true;
      doCountTime("water", sw1, relay1, 3);
      k = true;
    }//switch 1
    if(digitalRead(sw2)){
      while(digitalRead(sw2)){
        delay(50);
      }
      sw2_state = true;
      doCountTime("foam", sw2, relay2, 1);
      k = true;
    }//switch2
    if(coin <= 0 ){
      coin_state = HIGH; 
      digitalWrite(relay3, HIGH);
    }
    if(sw1_state && sw2_state){
      coin_state = HIGH;
      digitalWrite(relay3, HIGH);
      display.clear();
      goto L1;
    }
  }//main if.
  if(digitalRead(sw3)){
      setting();
      display.clear();
  } 
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
      return;
    }
    if(cTime-pTime >= 1000){
      Serial.printf("previous: %d current: %d \n",pTime,cTime);
      pTime = cTime;
      sec++;
      delay(50);
      if(sec == _time){
        sec = 0;
        coin --;
        Serial.println(coin);
      }
      int blinkk = (cTime/1000)%2;
      if(blinkk){
        if(type.equals("water")){
          display.showNumberDec(coin,false,2,2);
        }else{
          if(coin>=10){
            display.showNumberDec(coin,false,2,0);
          }else{
            display.showNumberDec(coin,false,1,0);
          }
          
        }
        
      }else{
        display.setSegments(blank);
      }
    }
    
  }//while coin
  digitalWrite(relay, LOW);
}//docounttime

void setting(){
  int water_min = 0;
  int foam_min = 0;
  Serial.println("Setting");
  display.setSegments(SEG_SET);
  delay(1000);
  Serial.println("Water");
  display.clear();
  display.showNumberDec(water_min);
  while(1){
    delay(50);
    if(digitalRead(sw1)){
      water_min++;
      water_min = water_min%100;
      Serial.printf("water: %d\n", water_min);
      display.showNumberDec(water_min,false,2,2);
      delay(100);
    }
    if(digitalRead(sw2)){
      while(digitalRead(sw2)){
        delay(50);
      }
      Serial.println("Confirm");
      break;
    }
  }//while water
  Serial.println("foam");
  display.clear();
  if(foam_min>=10){
    display.showNumberDec(foam_min,false,2,0);
  }else{
    display.showNumberDec(foam_min,false,1,0);
  }
    
  while(1){
    delay(50);
    if(digitalRead(sw1)){
      foam_min++;
      foam_min = foam_min%100;
      Serial.printf("foam: %d\n", foam_min);
      if(foam_min>=10){
        display.showNumberDec(foam_min,false,2,0);
      }else{
        display.showNumberDec(foam_min,false,1,0);
      }
      delay(100);
    }
    if(digitalRead(sw2)){
      while(digitalRead(sw2)){
        delay(50);
      }
      Serial.println("Confirm");
      break;
    }
  }//while foam
  Serial.printf("water: %d  foam: %d", water_min, foam_min);
  d = true;
  for(int i = 0; i <5; i++){
    if(i%2==0){
      if(foam_min>=10){
        display.showNumberDec(foam_min,false,2,0);
        display.showNumberDec(water_min,false,2,2);
      }else{
        display.showNumberDec(foam_min,false,1,0);
        display.showNumberDec(water_min,false,2,2);
      }
    }else{
      display.setSegments(blank);
    }
    delay(500);
  }
  
  
  
}
