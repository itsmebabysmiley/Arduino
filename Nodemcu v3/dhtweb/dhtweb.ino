#include "DHT.h"
#include <ESP8266WiFi.h>

const char* ssid = "SURIYA-2.4G";
const char* password = "0868894659";
// Web Server on port 80
WiFiServer server(80);

DHT dht;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(D2); // data pin 2

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(2000);

  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && blank_line) {
          // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
          float h = dht.getHumidity();
          // Read temperature as Celsius (the default)
          float f = dht.getTemperature();
          // Check if any reads failed and exit early (to try again).
          if (isnan(h) || isnan(f)) {
            Serial.println("Failed to read from DHT sensor!");
          }
          else {
            // Computes temperature values in Celsius + Fahrenheit and Humidity
            // You can delete the following Serial.print's, it's just for debugging purposes
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print(" %\t Temperature: ");
            Serial.print(f);
            Serial.print(" *F\n");
          }
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // your actual web page that displays temperature and humidity
          String s = "<!DOCTYPE html><html><head><title>Temp web</title></head><body><h1>ESP8266 - Temperature and Humidity</h1><div> <p><p style=\"font-size: 20px; display:inline; \"><b>Temperature in Celsius: </b></p><span style=\"font-size: 18px;color: red \">"+String(f)+"</span></p><p><p style=\"font-size: 20px; display:inline; \"><b>Humidity: </b></p><span style=\"font-size: 18px;color: red \">"+String(h)+"</span></p></div></body></html>";
          client.println(s);
          break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
