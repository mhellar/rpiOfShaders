#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wired2";
const char* password =  "password";
const char* mqttServer = "10.0.0.185";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

int threshold = 40;

bool touch3detected = false;
bool touch5detected = false;
bool touch6detected = false;
bool touch7detected = false;
bool touch8detected = false;
bool touch9detected = false;


void gotTouch3() {
  touch3detected = true;
}

void gotTouch5() {
  touch5detected = true;
}

void gotTouch6() {
  touch6detected = true;
}

void gotTouch7() {
  touch7detected = true;
}

void gotTouch8() {
  touch8detected = true;
}

void gotTouch9() {
  touch9detected = true;
}


void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  client.publish("hello", "Hello from ESP32");

  
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T3, gotTouch3, threshold);
  touchAttachInterrupt(T5, gotTouch5, threshold);
  touchAttachInterrupt(T6, gotTouch6, threshold);
  touchAttachInterrupt(T7, gotTouch7, threshold);
  touchAttachInterrupt(T8, gotTouch8, threshold);
  touchAttachInterrupt(T9, gotTouch9, threshold);
  yield();

}

void loop() {
  if(client.connected () != 1){
      if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  if (touch3detected) {
    touch3detected = false;
    Serial.println("Touch 3 detected");
    client.publish("hello", "a");
    delay(500);
  }
  if (touch5detected) {
    touch5detected = false;
    Serial.println("Touch 5 detected");
    client.publish("hello", "b");
    delay(500);
  }
  if (touch6detected) {
    touch6detected = false;
    Serial.println("Touch 6 detected");
    client.publish("hello", "c");
    delay(500);
  }
  if (touch7detected) {
    touch7detected = false;
    Serial.println("Touch 7 detected");
    client.publish("hello", "d");
    delay(500);
  }
  if (touch8detected) {
    touch8detected = false;
    Serial.println("Touch 8 detected");
    client.publish("hello", "e");
    delay(500);
  }
  if (touch9detected) {
    touch9detected = false;
    Serial.println("Touch 9 detected");
    client.publish("hello", "f");
    delay(500);
  }

}

