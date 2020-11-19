int button = D1;
int led = D2;
int check = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.println(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

    for(int i=0; i<10; i++){
      digitalWrite(led,i%2);
      Serial.println(i%2);
      delay(1000);
    }
}
