/*
- Credit from: บุญเลิศ แซ่เจี่ย
- contact: https://www.facebook.com/profile.php?id=100004186566129
*/

#include "Output.h"

class Output335:public Output
{
  public:
    void On();
    void Off();
    Output335(uint8_t,bool);
};
  void Output335::On()
  {
    pinMode(Pin(),OUTPUT);
    Status(ActiveLevel() ? HIGH : LOW);
  }
  void Output335::Off()
  {
    pinMode(Pin(),INPUT);
    Status(ActiveLevel() ? LOW : HIGH);
  }
  Output335::Output335(uint8_t pin,bool activeLevel = LOW):Output(pin,activeLevel)
  {
    pinMode(Pin(),INPUT);
  }
