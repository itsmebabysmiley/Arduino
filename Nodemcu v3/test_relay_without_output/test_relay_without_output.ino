int Relay1 = D7; // กำหนดขาใช้งาน
void setup()
{
  pinMode(Relay1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา D0 เป็น OUTPUT
  Serial.begin(9600);
}
void loop()
{
  Serial.println("Relay off");
  digitalWrite(Relay1, 1);
  delay(2000); // ดีเลย์ 1000ms
  Serial.println("Relay on");
  digitalWrite(Relay1, 0);
  delay(2000); // ดีเลย์ 1000ms
}
