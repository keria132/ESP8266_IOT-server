// #include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define WIFI_SSID "Tobik_Hata"
#define WIFI_PASSWORD "P4npYfYS"

IPAddress local_IP(192, 168, 0, 100);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

AsyncWebServer server(80);

int handleDevice (AsyncWebServerRequest *request);

void setup() {
  Serial.begin(115200);

  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  };

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.println(WiFi.localIP());
  delay(1000);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  server.on("/style.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.min.css", "text/css");
  });
  server.on("/script.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.min.js", "text/javascript");
  });

  server.on("/device", HTTP_POST, handleDevice);
}

void loop() {
  
}

int handleDevice(AsyncWebServerRequest *request) {
  
}

// class Device {
//   public:
//     String IP_adress;
//     String name;
//     String role;
//     boolean status;
// };