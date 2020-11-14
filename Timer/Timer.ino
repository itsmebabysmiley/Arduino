#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Ticker  count_time1;
int h = 0, minn = 0, sec = 0, i = 0;

int limit_h = 0;
int limit_minn = 0;
int limit_sec = 10;
//source from:
//http://www.thaidbselec.com/article/93/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99-timer-interrupt-nodemcu-%E0%B8%97%E0%B8%B3%E0%B8%99%E0%B8%B2%E0%B8%AC%E0%B8%B4%E0%B8%81%E0%B8%B2%E0%B8%88%E0%B8%B1%E0%B8%9A%E0%B9%80%E0%B8%A7%E0%B8%A5%E0%B8%B2
void c_time(){
  i++;
  if(i >= 10){
    sec++;
    i = 0; 
  }
  if(sec >= 60){
    minn++;
    sec = 0;
  }
  if(minn >= 60){
    h++;
    minn = 0;
  }
}

void setup() {
  Serial.begin(9600);
  count_time1.attach(0.1, c_time);     //Interrupt ทุกๆ 0.1 วินาที
  lcd.begin();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0, 0);
  Serial.print("Timer ");
  Serial.println();
  lcd.print("Timer ");
  lcd.setCursor(0,1);
  if(h <= limit_h && minn <= limit_minn && sec < limit_sec){
    Serial.print(h); Serial.print(":");
    lcd.print(h);lcd.print(":");
    Serial.print(minn); Serial.print(":");
    lcd.print(minn);lcd.print(":");
    Serial.print(sec); Serial.print(":");
    lcd.print(sec);lcd.print(":");
    Serial.print(i); Serial.print(":");
    lcd.print(i);lcd.print(":");
    Serial.println();
 }
  else{
    Serial.println();
    Serial.print("Stop");
    lcd.setCursor(0,1);
    lcd.print("Stop        ");
  }
 
}
