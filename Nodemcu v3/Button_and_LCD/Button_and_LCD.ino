#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPin = D7; //input from D7
int button_state = 0;
void setup()
{
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Start"); 
}
void loop() {

  button_state = digitalRead(buttonPin); //read input from D7
  if(button_state == 1){
    Serial.print("clicking");
    lcd.setCursor(0, 0);
    lcd.print("Clicking ");
    lcd.setCursor(0, 1);
    lcd.print("Clicking ");
    Serial.println();
  }
  else{
    Serial.print("No action");
    lcd.setCursor(0, 0);
    lcd.print("No action ");
    lcd.setCursor(0, 1);
    lcd.print("No action ");
    Serial.println();
  }
}
