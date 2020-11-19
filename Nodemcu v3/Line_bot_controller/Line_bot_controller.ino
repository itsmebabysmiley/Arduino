// https://medium.com/isync/line-bot-%E0%B8%84%E0%B8%A7%E0%B8%9A%E0%B8%84%E0%B8%B8%E0%B8%A1-esp32-arduino-655a4ea4fdd6
#include <ESP8266WiFi.h>
#include <iSYNC.h>

WiFiClient client;
iSYNC iSYNC(client);

String ssid = "SURIYA-2.4G";
String pass = "0868894659";

String iSYNC_USERNAME = "snzzare";
String iSYNC_KEY = "5fb695bb5e614c07a2d91a77";
String iSYNC_AUTH = "5fb695995e614c07a2d91a74"; //auth project

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  Serial.print("[iSYNC]-> ");
  for (int i = 0; i < length; i++){
    msg+=(char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if(msg.startsWith("LINE:"))msg = msg.substring(5);

  /* command control */
  if(msg.equals("เปิดไฟ")){
      digitalWrite(D2,1);
      iSYNC.mqPub(iSYNC_KEY,"ได้เลยจ๊ะพี่จ๋า");   //Publish
  }else if(msg.equals("ปิดไฟ")){
      digitalWrite(D2,0);
      iSYNC.mqPub(iSYNC_KEY,"ได้เลยจ๊ะพี่จ๋า");   //Publish
  }
}

void connectMQTT(){
  while(!iSYNC.mqConnect()){
    Serial.println("Reconnect MQTT...");
    delay(3000);
  }
  iSYNC.mqPub(iSYNC_KEY,"พร้อมรับคำสั่งแล้วจ๊ะพี่จ๋า");   //Publish on Connect
// iSYNC.mqSubProject(); //subscribe all key in your project
  iSYNC.mqSub(iSYNC_KEY); //subscribe key
}

void setup() {
  Serial.begin(115200);
  Serial.println(iSYNC.getVersion());

  pinMode(D2,OUTPUT);  // led on/off set output
  digitalWrite(D2,1);
  delay(1000);
  digitalWrite(D2,0);

  iSYNC.begin(ssid,pass);
  iSYNC.mqInit(iSYNC_USERNAME,iSYNC_AUTH);
  iSYNC.MQTT->setCallback(callback);
  connectMQTT();
}

void loop() {
  if (!iSYNC.mqConnected())connectMQTT();
  iSYNC.mqLoop();
}
