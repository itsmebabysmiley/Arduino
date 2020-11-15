#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPin = D7;
int buttonState = 0;
int i = 1;
void start_up(){
  Serial.println("Time limit 30s.");
  lcd.setCursor(0, 0);
  lcd.print("Time limit 30s.");
  lcd.blink();
  delay(800);
  Serial.println("Time start in");
  lcd.clear();
  lcd.print("Time start in");
  lcd.setCursor(0, 1);
  Serial.print("3");
  lcd.print("3");
  delay(500);
  Serial.print(".");
  lcd.blink();
  lcd.print(" ");
  delay(500);
  Serial.print("2");
  lcd.print("2");
  delay(500);
  lcd.blink();
  lcd.print(" ");
  Serial.print(".");
  delay(500);
  Serial.println("1");
  lcd.print("1");
  lcd.blink();
  delay(1000);
  lcd.noBlink();
  lcd.clear();
}
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  pinMode(buttonPin,INPUT); //input from button
  Serial.begin (9600);
  delay(2000);
  
  start_up();

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); //read input from D1
  // push button to stop time and release to continue.
  if(buttonState == HIGH){
    Serial.println("Stop");
    lcd.setCursor(0,0);
    lcd.print("Stop ");
  }
  else{
    Serial.println("Start");
    lcd.setCursor(0,0);
    lcd.print("Start");
    lcd.setCursor(0,1);
    lcd.print(i);
    Serial.println(i);
    i += 1;
    delay(1000);
  }
  // reset time when it reach to 30 seconds.
  if(i > 30){
    Serial.println("Reset");
    lcd.setCursor(0,0);
    lcd.print("Reset");
    lcd.blink();
    delay(1000);
    lcd.noBlink();
    lcd.clear();
    i = 1;
  }
  

}
