//http://maker.ifttt.com/trigger/button_pressed/with/key/5BZuRTbT2qVHnyHaDN-Iq by gmail
//http://maker.ifttt.com/trigger/sw_on/with/key/5BZuRTbT2qVHnyHaDN-Iq by line notify
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
int led = D1;
int button = D2;
//String url = "http://maker.ifttt.com/trigger/button_pressed/with/key/5BZuRTbT2qVHnyHaDN-Iq";
String url = "http://maker.ifttt.com/trigger/sw_on/with/key/5BZuRTbT2qVHnyHaDN-Iq";
const char* ssid = "SURIYA-2.4G";
const char* password = "0868894659";
// function call http request to IFTTT to sent and email.
void htttpRequest() {
  HTTPClient http;
  //---- start http ----
  http.begin(url);
  Serial.println("[HTTP] GET...");
  int http_code = http.GET(); // send a request GET

  //check code that web server response.
  if (http_code > 0) {
    Serial.print("Response code:");
    Serial.print(http_code);
    //if response is fine. It will get HTTP_CODE_OK(code is 200)
    if (http_code == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  //if response is error.
  else {
    Serial.print("[HTTP] GET Failed....");
    Serial.print(http_code);
    Serial.println(http.errorToString(http_code).c_str());
  }
  http.end();
  //---- End http ----
  delay(2000);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  delay(1000);

  //----wifi begin----
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //----End wifi----
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_state = digitalRead(button);
  if (button_state == 1) {
    digitalWrite(led, 1);
    Serial.println("Switch was pressed. Send request to IFTTT.");
    htttpRequest();
  } else {
    digitalWrite(led, 0);
    Serial.println(button_state);
  }
  delay(100);
}
