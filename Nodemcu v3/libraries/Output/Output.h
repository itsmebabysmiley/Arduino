/*
- Credit from: บุญเลิศ แซ่เจี่ย
- contact: https://www.facebook.com/profile.php?id=100004186566129
*/

class Output
{
  protected:
    uint8_t _pin;
    bool _activeLevel;
    bool _status;

  public:
    uint8_t Pin();
    void Pin(uint8_t);  
    bool ActiveLevel();
    void ActiveLevel(bool);
    bool Status();
    void Status(bool);
    void On();
    void Off();
    void Toggle();
    Output(uint8_t,bool);
    ~Output(){}
};
