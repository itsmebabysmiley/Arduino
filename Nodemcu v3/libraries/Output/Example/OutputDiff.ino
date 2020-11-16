#include "Output335.h"
#define RELAY 14

Output335 relay1(RELAY);  //D5 NodeMCU V3, Relay active LOW

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  delay(2000);
  relay1.On();
  Serial.println(relay1.Status());
  delay(2000);
  relay1.Off();
  Serial.println(relay1.Status());

}
