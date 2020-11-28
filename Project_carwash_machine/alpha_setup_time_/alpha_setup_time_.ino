/**
 * Author: Baby
 * Last modify: November 25,2020
 * 
 * this file didn't include EEPROM.h 
 * this is just sample of setup menu. it kinda mess a little bit.
 * I try to write important comment on it. so if I forgot then It's my problem.
 * 
 * Contact: 
 *    Twitter- @itmebabysmiley
 *    gitHub- https://github.com/itsmebabysmiley?tab=repositories
 */

int button = D5; //GPIO
int button_state; //status of button
unsigned long _time;
unsigned long prev_time = 0;
boolean check = false; //it's just check statue of button on doSetTime()
int _min = 1;
int _sec = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button, INPUT);

}
void loop() {
  button_state = digitalRead(button);
  /* push button for 5 second to start setup menu.
    if it's possible to use inturrupt then use it.
    (it may clause problem because inturrput things maybe.)
  */
  if (button_state == HIGH) {
    Serial.print("Time: ");
    _time = millis();
    //start again.
    if (prev_time == 0) prev_time = _time;
    Serial.println(_time); //prints time
    delay(1000);          // wait a second
    if (_time - prev_time > 5000) {
      String s = "time: " + String(_time) + "prev_time: " + String(prev_time);
      Serial.println(s);
      doSetTime();
      prev_time = 0;
    }
  //reset time if it didn't reach 5 seconds.
  } else {
    prev_time = 0;
    _time = 0;
  }
  /* end setup menu */


}
/**
 * main setup function here.
 * normally I use second to do stuff.
 *  -convert minute to second. 
 *   -push 1 time to increse 30 second.
 *  -maximun is 10 minute.(if it's over 10 min reset to 0 again)
 *  -push button for 5 second to save the time and exit the setup menu.
 * 
 * check - for check status of button and fix the error I occured.
 * (I think it came from button some kind of signal)
 */
void doSetTime() {
  int max_sec = (_min * 60) + _sec; 
  check = false;  //increse user do setup more than 1 time in 1 time. hahah
  Serial.println("Set up menu");
  delay(5000);
  String s = "old: " + String(_min) + ":" + String(_sec) + "(" + String(max_sec) + ")";
  Serial.println(s);
  /*
   * I created the infinity loop because I want to stay like this forever fak why I am telling this.
   * if it hasn't loop it will not work because we have to wait for user to set time.
   */
  while (true) {
    if (digitalRead(button) == HIGH) {
      check = true;
      /*push button for 5 second to save and exit the setup menu. */
      int count_2stop = 1;
      while(digitalRead(button) == HIGH){
        Serial.println(count_2stop++);
        delay(1000);
        if(count_2stop == 5){
          Serial.println("SAVED!!");
          delay(500);
          return;
        }
      }
      /* end exit menu. */
    }
    /* increase time maximum is 10 minute */
    delay(200); //signal maybe. if I don't have this it's error. cuz signal maybe.
    if (check == true) {
      check = false;    //to stop the continue increse time(1 push +30).
      max_sec += 30;    
      _min = max_sec / 60;
      _sec = max_sec % 60;
      s = "Now: " + String(_min) + ":" + String(_sec) + "(" + String(max_sec) + ")";
      Serial.println(s);
    }
    if (max_sec == 600) max_sec = 0;  //reset time if it's 10 minute.
    /* end increase time */
  }// end while

}
