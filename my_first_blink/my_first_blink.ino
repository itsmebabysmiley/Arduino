#define LED D4 // Nodemcu v2 ใช้ D0 , Nodemcu v3 ใช้ D4
void setup()
{
pinMode(LED,OUTPUT);
}
void loop()
{
digitalWrite(LED,HIGH);
delay(250);
digitalWrite(LED,LOW);
delay(250);
}
