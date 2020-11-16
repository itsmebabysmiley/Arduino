/*
- Credit from: บุญเลิศ แซ่เจี่ย
- contact: https://www.facebook.com/profile.php?id=100004186566129
*/
#include "Arduino.h"
#include "Output.h"

uint8_t Output::Pin()                         {return _pin;}
void Output::Pin(uint8_t pin)                 {_pin = pin;}  
bool Output::ActiveLevel()                    {return _activeLevel;}
void Output::ActiveLevel(bool activeLevel)    {_activeLevel = activeLevel;}
bool Output::Status()                         {return _status;}
void Output::Status(bool deviceStatus)        {_status = deviceStatus;}

void Output::On()
{
  if(ActiveLevel())
  {
    Status(HIGH);
    digitalWrite(Pin(),Status());    
  }
  else
  {
    Status(LOW);
    digitalWrite(Pin(),Status());    
  }
}

void Output::Off()
{
  if(ActiveLevel())
  {
    Status(LOW);
    digitalWrite(Pin(),Status());
  }
  else
  {
    digitalWrite(Pin(),Status());    
  }
}

void Output::Toggle()
{
  Status(!Status());
  digitalWrite(Pin(),Status());
}

Output::Output(uint8_t pin,bool activeLevel = LOW)
{
  Pin(pin);
  ActiveLevel(activeLevel);
  Status(!activeLevel);
  pinMode(Pin(),OUTPUT);
}
