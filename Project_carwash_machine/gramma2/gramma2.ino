/*
 * Author: Baby
 * Last modify: Jan 01,2021
 * 
 * -this is almost complete. just add EEPROM thing then it is complete
 * -this file I already add another button for increase time limit in setup function.
 * -I already add rom things.
 * -basically it finished. but it's not complete yet. 
 * -waiting for pcb to modify code again.(we have to change an relay parts.
 * 
 * Contact: 
 *    Twitter- @itmebabysmiley
 *    gitHub- https://github.com/itsmebabysmiley?tab=repositories
*/  
 
 #include <Wire.h>
 #include <LiquidCrystal_I2C.h>
 #include <EEPROM.h>

const int relay = D8;
const int coin_signal = D5;
const int LED = D3;
const int sw1 = D6;
const int sw2 = D7;

boolean check = false;

int coin_state = 0;
int button_state = 0;
int coin = 0;
int count = 0;
// time
int _sec = 0;
int _min = 0;
int _hr = 0;
unsigned long _time;
unsigned long prev_time = 0;
int limit_sec = 0; //
int limit_min = 0;
int limit_hr = 0;
int max_sec = 0;
int limit_time = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    EEPROM.begin(512);
    pinMode(sw1, INPUT);
    pinMode(sw2, INPUT);
    pinMode(relay, OUTPUT);
    pinMode(LED, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(coin_signal), getCoin, FALLING);
    
    /* LED CHECK STATUS */
    digitalWrite(LED, HIGH); delay(500);
    digitalWrite(LED, LOW);
    digitalWrite(LED, HIGH); delay(500);
    digitalWrite(LED, LOW);
    /* END CHECK STATUS */
    
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("0 Bath");
    int eeAddress = 0;
    int eeeAddress = 0;
    //put only first time.
    /*
      EEPROM.put(eeAddress,0);
      eeAddress += sizeof(int); 
      EEPROM.put(eeAddress,30);
      EEPROM.commit();
    */
    //get time from rom
    EEPROM.get(eeeAddress,limit_min);
    eeeAddress += sizeof(int);
    EEPROM.get(eeeAddress,limit_sec);
    limit_time = (limit_min*60) + limit_sec;
    Serial.println(limit_time);
}
/**
 *        >>>SUPPOSE LED IS THE RELAY<<<
 * -the led will turn on when coin is more than 5 bath.
 * -the led will turn on until it reach to the time limit. 
 *  then it will turn off and reset everything to be ready to next input.
 *  
 * -if admin(owner whatever) push the button for 5 seconds if will jump to set up menu.
 */
void loop()
{
    //digitalWrite(led, 0);
    digitalWrite(relay, LOW);
    
    button_state = digitalRead(sw1);
    if (button_state == HIGH)
    {
        Serial.print("Time: ");
        _time = millis();
        //start again.
        if (prev_time == 0)
            prev_time = _time;
        Serial.println(_time); //prints time when pushing
        delay(1000);           
        if (_time - prev_time > 3000) //if push more than 5 seconds
        {   
            //String s = "time: " + String(_time) + "prev_time: " + String(prev_time);
            //Serial.println(s);
            doSetTime();
            prev_time = 0;  //to start again.
        }
    }
    else //reset time if it didn't reach 5 seconds.
    {
        prev_time = 0;
        _time = 0;
    }
    if (coin >= 5)
    {
        //digitalWrite(led, 1);
        digitalWrite(relay, HIGH);
        //Serial.println(relay1.Status());
        String s = "time:" +String(_min)+":"+String(_sec);
        Serial.println(s);
        lcd.setCursor(0,1);
        lcd.print(s);

        if (limit_min == _min && limit_sec == _sec)
        {
            //digitalWrite(led, 0);
            digitalWrite(relay, LOW);
            _reset_();
        }
        _sec++;
        if (_sec == 60)
        {
            _min += 1;
            _sec = 0;
        }
        delay(1000);
    }
}
/**
 * -this function  will active when coin signal interrupt whatever I don't know.
 * -increase amount of coin and also increase time limit.
 * -convert minute to second because mainly I use second to do stuff.
 * 
 */
ICACHE_RAM_ATTR void getCoin()
{
    coin += 5;
    Serial.print(coin);
    Serial.println("bath");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(coin);
    lcd.print(" Bath");
    
    //max_sec = (limit_min*60) + limit_sec;
    max_sec += limit_time;
    limit_min = int(max_sec / 60);
    limit_sec = max_sec % 60;
    String s = "Limit time:" + String(limit_min)+":"+String(limit_sec);
    Serial.println(s);
    lcd.print(limit_min)+lcd.print(":");+lcd.print(limit_sec);
}

/**
 * reset everyting to be ready to next input coin.
 */
void _reset_()
{
    _sec = 0;
    _min = 0;
    _hr = 0;
    max_sec = 0;
    coin = 0;
    count = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(coin);
    lcd.print(" Bath");
}

/**
 * -set up menu for timer.
 * -push button for 5 seconds to save and exit the setup menu.
 * -push button will increase 30 seconds.
 * -this one will show infomation on lcd screen.
 * 
 */
void doSetTime()
{
    int temp_sec = (limit_min * 60) + limit_sec;
    check = false; //increse user do setup more than 1 time in 1 time. hahah
    lcd.clear();
    lcd.print("Set up menu");
    Serial.println("Set up menu");
    delay(4000);
    String s = "Now: " + String(limit_min) + ":" + String(limit_sec) + "(" + String(temp_sec) + ")";
    Serial.println(s);
    lcd.setCursor(0,1);
    lcd.print(s);
    /*
   * I created the infinity loop because I want to stay like this forever fak why I am telling this.
   * if it hasn't loop it will not work because we have to wait for user to set time.
   */
    while (true)
    {
               //button was pushed.
            int count_2stop = 0;
            char save[] = {'s','a','v','e'};
            /*push button for 5 second to save and exit the setup menu. */
            while (digitalRead(sw1) == HIGH)
            {
                Serial.println(save[count_2stop++]);
                delay(1000);
                if (count_2stop == 4)
                {   int eeAddress = 0;
                    int eeeAddress = 0;
                    int temp_limit_min;
                    int temp_limit_sec;
                    EEPROM.get(eeAddress,temp_limit_min);
                    eeAddress += sizeof(int);
                    EEPROM.get(eeAddress,temp_limit_sec);
                    //check if old time is not same as new time. save rom life.
                    if(temp_limit_min != limit_min && temp_limit_sec != limit_sec){
                      Serial.println("New time added");
                      EEPROM.put(eeeAddress,limit_min);
                      eeeAddress += sizeof(int); 
                      EEPROM.put(eeeAddress,limit_sec);
                      EEPROM.commit();
                    }
                    
                    lcd.clear();
                    Serial.println("SAVED!!");
                    lcd.print("SAVED!!");
                    delay(1000);
                    lcd.clear();
                    lcd.print("Reset...");
                    Serial.println("Reset..");
                    ESP.restart();
//                    return;
                }
            }
            /* end exit menu. */
        if(digitalRead(sw2) == HIGH){
            check = true;
        }
        /* maximum time limit is 10 minute */
        //delay for fix da bug.
        delay(200); //signal maybe. if I don't have this it's error. cuz signal maybe.
        if (check == true)
        {
            check = false; //to stop the continue increasing time(1 push +30).
            temp_sec += 30;
            limit_min = temp_sec / 60;
            limit_sec = temp_sec % 60;
            //show new time.
            s = "Now: " + String(limit_min) + ":" + String(limit_sec) + "(" + String(temp_sec) + ")";
            Serial.println(s);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Set up menu");
            lcd.setCursor(0,1);
            lcd.print(s);
        }
        //reset time if it's 10 minute.
        if (temp_sec == 600)
            temp_sec = 0; 
        /* end increase time */ 
    }// end while
}
