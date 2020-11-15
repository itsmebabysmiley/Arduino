//source code
//https://www.arduino.cc/reference/en/language/functions/time/millis/
unsigned long _time;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  Serial.print("Time: ");
  _time = millis();
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(_time); //prints time since program started
  delay(1000);          // wait a second so as not to send massive amounts of data
  Serial.print("Time: ");
  _time = millis();
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(_time);
  delay(1000);
}
