#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureAxTLS.h>
#include <TM1637Display.h>

ESP8266WiFiMulti WiFiMulti;

//------ Config WiFi ------
#define SSID_1 "WIFI_NAME"
#define PASS_1 "WIFI_PASSWORD"

#define BUTTONWASHER D2
#define CLK1 D1
#define DIO1 D0
TM1637Display display1(CLK1, DIO1);
bool countdown1_active = false;
unsigned long countdown1_end = 0;

// 7-segment
#define BUTTONDRYER D4
#define CLK2 D6
#define DIO2 D5
TM1637Display display2(CLK2, DIO2);
bool countdown2_active = false;
unsigned long countdown2_end = 0;

void setup() {
  Serial.end();
  Serial.begin(115200);

  pinMode(BUTTONDRYER, INPUT_PULLUP);
  pinMode(BUTTONWASHER, INPUT_PULLUP);

  SetWiFi();

  display2.setBrightness(0x0f); // Set brightness to max
  display2.showNumberDecEx(0, 0b01000000, true, 4, 0); // Initialize displays to show 0000
  display1.setBrightness(0x0f); // Set brightness to max
  display1.showNumberDecEx(0, 0b01000000, true, 4, 0); // Initialize displays to show 0000
}

void loop() {
  CheckWiFi();

  // Handle button 1 press with debouncing
  if (digitalRead(BUTTONWASHER) == LOW && !countdown1_active) {
    sendToGoogleSheet("washer01", "working", 1);
    countdown1_active = true;
    countdown1_end = millis() + (1 * 60 * 1000); // 1 minute countdown
  }

  // Update countdown for display1
  if (countdown1_active) {
    unsigned long remaining1 = (countdown1_end - millis()) / 1000;

    if (remaining1 > 0) {
      display1.showNumberDecEx(remaining1 / 60 * 100 + remaining1 % 60, 0b01000000, true, 4, 0);
    } else {
      display1.showNumberDecEx(0, 0b01000000, true, 4, 0);
      countdown1_active = false;
      sendToGoogleSheet("washer01", "stopped", 0); 
    }
  } else {
    // Reset display1 to show 0000 if not active
    display2.showNumberDecEx(0, 0b01000000, true, 4, 0);
  }

  // Handle button 2 press with debouncing
  if (digitalRead(BUTTONDRYER) == LOW && !countdown2_active) {
    sendToGoogleSheet("dryer01", "working", 1);
    countdown2_active = true;
    countdown2_end = millis() + (1 * 60 * 1000); // 1 minute countdown
  }
  
  // Update countdown for display2
  if (countdown2_active) {
    unsigned long remaining2 = (countdown2_end - millis()) / 1000;

    if (remaining2 > 0) {
      display2.showNumberDecEx(remaining2 / 60 * 100 + remaining2 % 60, 0b01000000, true, 4, 0);
    } else {
      display2.showNumberDecEx(0, 0b01000000, true, 4, 0);
      countdown2_active = false;
      sendToGoogleSheet("dryer01", "stopped", 0); 
    }
  } else {
    // Reset display2 to show 0000 if not active
    display2.showNumberDecEx(0, 0b01000000, true, 4, 0);
  }
}

void sendToGoogleSheet(String washerId, String status, int timeSpent){
  axTLS::WiFiClientSecure client;
  const char* HOST = "script.google.com";
  const char* GScriptId = "Google_Script_ID";  
  String url32 = String("/macros/s/") + GScriptId + "/exec?" + "sts_val=" + "write" + "&WASHERID=" + washerId + "&STATUS=" + status + "&TIMESPENT=" + String(timeSpent) + "&IMAGE=" + "000";
  if (client.connect(HOST, 443)) {
    client.println("GET " + String(url32) + " HTTP/1.0"); //HTTP/1.0 OK sent GoogleSheet
    client.println("Host: " + String(HOST));
    client.println("User-Agent: ESP8266\r\n");
    client.println("Connection: close\r\n\r\n");
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(url32.length()));
    client.println();
    client.print("\r\n\r\n");
    Serial.print("Response...");
  }
  Serial.println("Write OK !!!");        
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