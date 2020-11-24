/**
 * Author: baby
 * Last modify: November 25,2020
 * 
 * this is just sample of coin validator with lcd show amout of coin in bath(THB).
 * How it work?
 *    it will wait for input coin. if you input coin, it will show balance and then start 
 *    timer. you can put more coin while machine is running. It'll increase your balance automatically and 
 *    also increase you time too. don't worry.
 * I use LCD display the balance but not show the time because I don't want too(it still have bug. hhh)
 *  #function
 *    LiquidCrystal_I2C lcd(0x27, 16, 2); my lcd size is 16x2
 *    lcd.begin(); initial lcd, MUST HAVE THIS FUNCTION
 *    lcd.backlight();  turn backlight on.
 *    lcd.setCursor(0, 0); set cursor at 0,0 mean first line first index. (0,1 means second line and first index.)
 *    lcd.print(text);  show text on lcd.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// pin
int sensor = D5;
int led = D6; //suppose it's relay.
// more details in functions.
int coin = 0;   //in this case I use 5 bath coin.
boolean check = false;
int count = 0;
boolean state = false;

int _sec = 0;
int _min = 0;
int _hr  = 0;

int limit_sec = 20;   //
int limit_sec2 = 20;  // same as limit_sec just kinda constant.
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
  attachInterrupt(digitalPinToInterrupt(sensor), getCoin, RISING);  //when someone is insert coin into machine it'll do getCoin()
  delay(1000);
  Serial.println("Hello! Bitch");
  lcd.print("0 Bath");
  digitalWrite(led, 0);

}
/**
 *        >>>SUPPOSE LED IS THE RELAY<<<
 * -the led will turn on when coin is more than 5 bath.
 * -the led will turn on until it reach to the time limit. 
 * then it will turn off and reset everything to be ready to next input.
 */
void loop() {
    digitalWrite(led, 0);
  if(coin >= 5){
    digitalWrite(led, 1);
    Serial.print("time: ");
    Serial.print(_min);Serial.print(":");
    Serial.println(_sec);
    //I didn't check hours because I think I don't have to but if in the future need it,,, just add it.
    //time reach limit call _reset_().
    if(limit_min == _min && limit_sec == _sec){
      _reset_();
    }
    
     _sec ++;
     
    if(_sec == 60){
      _min += 1;
      _sec = 0;
    }
    delay(1000);  //kinda timer here. but it's not percise.
  }
}
/**
 * Active when the coin passed the sensor.
 * -increase balance coin.
 * -increase the limit of time(second).
 * -then print whatever you want.
 */
ICACHE_RAM_ATTR void getCoin() { 
  coin += 5;
  Serial.print(coin);Serial.println("bath");
  lcd.setCursor(0,0);
  lcd.print(coin);
  lcd.print(" Bath");
  max_sec += limit_sec2;
  limit_min = int(max_sec/60);
  limit_sec = max_sec%60;
  Serial.println(max_sec);
  Serial.println(limit_min);
  Serial.println(limit_sec);
  Serial.print("Limit time: ");Serial.print(limit_min);Serial.print(":");Serial.println(limit_sec);
}
/*
 * reset everyting to be ready to next input coin.
 * I just put every variable in here haha.
 */
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
  lcd.setCursor(0,0);
  lcd.print(coin);
  lcd.print(" Bath");
}
