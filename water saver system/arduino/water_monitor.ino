#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FLOW_SENSOR D2
volatile int pulseCount = 0;
float flowRate = 0.0;

const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-secret-or-token"

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(FLOW_SENSOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), countPulse, FALLING);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  pulseCount = 0;
  delay(1000);
  flowRate = pulseCount * 0.00225;

  Firebase.setFloat("school1/flowRate", flowRate);
  Serial.print("Flow rate (L/min): ");
  Serial.println(flowRate);
}