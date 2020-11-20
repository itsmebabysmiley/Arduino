const byte ledPin = D4;
const byte interruptPin = D1;
volatile byte state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
  Serial.println(state);
  delay(1000);
}

ICACHE_RAM_ATTR void blink() {
  state = !state;
}
