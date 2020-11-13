#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buttonPin = D1;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
  lcd.print("Click"); //พิมพ์ข้อความ "LCD1602 I2c Test"

  pinMode(buttonPin, INPUT); //input from button
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); //read input from D0
  if(buttonState == HIGH){
    Serial.print("click on");
    Serial.println(buttonState);
  }
  else{
    Serial.print("click off");
    Serial.println(buttonState);
  }
}
