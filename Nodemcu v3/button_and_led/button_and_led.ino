int button = D1;
int led = D2;
int check = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_state = digitalRead(button);
  if(button_state == 1){
    digitalWrite(led,1);
    Serial.println(button_state);
  }else{
    digitalWrite(led,0);
    Serial.println(button_state);
  }

}
