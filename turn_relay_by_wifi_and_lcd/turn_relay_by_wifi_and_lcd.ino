#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "SURIYA-2.4G";
const char* password = "0868894659";

int Relay1 = D7; 
int ch1 = 0;
WiFiServer server(80);

void setup()
{
  pinMode(Relay1, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("WIFI TEST");
  delay(2000);
  // ------------------- start connect to wifi ----------------------- \\
  Serial.print("Connecting to ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  Serial.println(ssid);
  lcd.setCursor(0,1);
  lcd.print(ssid);
  lcd.clear();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0,0);
    lcd.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  lcd.clear();

  // Start the server
  server.begin();
  Serial.println("Server started");
  lcd.setCursor(0, 0);
  lcd.print("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  lcd.setCursor(0,1);
  lcd.print("at ");
  lcd.print(WiFi.localIP());
  lcd.print("/");
}
void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

    // รับ Link ช่อง 1 

  if (request.indexOf("/LED1=ON") != -1) {
    digitalWrite(Relay1, 0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Status: On");
    ch1 = 1;
  }
  if (request.indexOf("/LED1=OFF") != -1) {
    digitalWrite(Relay1, 1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Status: Off");
    ch1 = 0;
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forget this one
  client.println("");
  client.println("");

  client.print("Led pin D1 : ");
  if (ch1 == 1) {
    client.print("On<br>");
  } else {
    client.print("Off<br>");
  }

  client.println("");
  client.println("CH1 <a href=\"/LED1=ON\"\"><button> On </button></a><a href=\"/LED1=OFF\"\"><button> OFF </button></a><br>"); 
  client.println("");
    delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
