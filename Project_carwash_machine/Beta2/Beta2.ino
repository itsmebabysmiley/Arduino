#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// pin
int sensor = D5;
int led = D6;
// idaf
int coin = 0;
boolean check = false;
int count = 0;
boolean state = false;

// time
int _sec = 0;
int _min = 0;
int _hr  = 0;

int limit_sec = 20;   //
int limit_sec2 = 20;  // same as limit_sec just kinda constant;
int limit_min = 0;
int limit_hr = 0;
int max_sec = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  digitalWrite(led, 1);
  attachInterrupt(digitalPinToInterrupt(sensor), getCoin, RISING);
  delay(1000);
  Serial.println("Hello! Bitch");
  lcd.print("HELLO");
  digitalWrite(led, 0);

}

void loop() {
    digitalWrite(led, 0);
  if(coin == 5){
    digitalWrite(led, 1);
    Serial.print("time: ");
    Serial.print(_min);Serial.print(":");
    Serial.println(_sec);

    if(limit_min == _min && limit_sec == _sec){
      _reset_();
    }
     _sec ++;
    if(_sec == 60){
      _min += 1;
      _sec = 0;
    }
    delay(1000);
  }
}
// active when coin passed sensor.
ICACHE_RAM_ATTR void getCoin() { 
  Serial.println("5 bath");
  coin = 5;
  max_sec += limit_sec2;
  limit_min = int(max_sec/60);
  limit_sec = max_sec%60;
  Serial.println(max_sec);
  Serial.println(limit_min);
  Serial.println(limit_sec);
  Serial.print("Limit time: ");Serial.print(limit_min);Serial.print(":");Serial.println(limit_sec);
}
//reset everyting to be ready to next input coin.
void _reset_(){
  _sec = 0;
  _min = 0;
  _hr  = 0;
  limit_sec = 20;
  limit_min = 0;
  limit_hr = 0;
  max_sec = 0;
  coin = 0;
  count = 0;
  
}
