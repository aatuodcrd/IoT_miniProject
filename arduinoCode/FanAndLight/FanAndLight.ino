#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureAxTLS.h>
#include <TM1637Display.h>
#include <FirebaseArduino.h>

ESP8266WiFiMulti WiFiMulti;

//------ Config WiFi ------
#define SSID_1 "WIFI_NAME"
#define PASS_1 "WIFI_PASSWORD"

// FIREBASE NAME/SECRET Config 
#define PROJECT_IO "firebaseProjectName"
#define DATA_SECRET "FirebaseSecret"

// LED
#define BUTTONFAN D1
#define FAN_LED_PIN D0
#define BUTTONLIGHT D6
#define LIGHT_LED_PIN D5

void setup() {
  Serial.end();
  Serial.begin(115200);

  pinMode(FAN_LED_PIN, OUTPUT);
  pinMode(BUTTONFAN, INPUT_PULLUP);
  pinMode(LIGHT_LED_PIN, OUTPUT);
  pinMode(BUTTONLIGHT, INPUT_PULLUP);

  SetWiFi();
  Firebase.begin(PROJECT_IO, DATA_SECRET);
}

void loop() {
  CheckWiFi();

  String fanOldStatus = Firebase.get("Data/fanStatus");
  String lightOldStatus = Firebase.get("Data/lightStatus");

  if (fanOldStatus == "on"){
    digitalWrite(FAN_LED_PIN, HIGH); 
  } else if (fanOldStatus == "off"){
    digitalWrite(FAN_LED_PIN, LOW); 
  }
  // Handle button 4 press with debouncing
  if (digitalRead(BUTTONFAN) == LOW) {
    if (fanOldStatus == "off") {
      digitalWrite(FAN_LED_PIN, HIGH);
      Firebase.set("Data/fanStatus", "on");
    } else if (fanOldStatus == "on") {
      digitalWrite(FAN_LED_PIN, LOW);
      Firebase.set("Data/fanStatus", "off");
    }
  }

  if (lightOldStatus == "on"){
    digitalWrite(LIGHT_LED_PIN, HIGH); 
  } else if (lightOldStatus == "off"){
    digitalWrite(LIGHT_LED_PIN, LOW); 
  }

  // Handle button 4 press with debouncing
  if (digitalRead(BUTTONLIGHT) == LOW) {
    if (lightOldStatus == "off") {
      digitalWrite(LIGHT_LED_PIN, HIGH);
      Firebase.set("Data/lightStatus", "on");
    } else if (lightOldStatus == "on") {
      digitalWrite(LIGHT_LED_PIN, LOW);
      Firebase.set("Data/lightStatus", "off");
    }
  }
}

void CheckWiFi(){
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
}

void SetWiFi(){
  WiFiMulti.addAP(SSID_1, PASS_1);  
  WiFiMulti.addAP("AndroidAP", "ifmd0883");
  delay(2000);  
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
  }
}