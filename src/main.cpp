#include <Arduino.h>
#include <Hash.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "./sensors/dht.hpp"
#include "./sensors/pir.hpp"
#include "./sensors/mq9.hpp"
// access point credentials
#include "./apCfg.hpp"

// mqtt broker
constexpr char *server = "192.168.1.35";
constexpr char *topic = "esp8266";
constexpr int mqttPort = 1883;



void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.println("recived");
}

// wifi stuff
WiFiClient wifiClient;
PubSubClient client(server, mqttPort, callback, wifiClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

inline void connectWifi(String &clientName) {
  constexpr auto mac2Str = [](uint8_t *mac) {
    String result;
    for (int i = 0; i < 6; ++i) {
      result += String(mac[i], 16);
      if (i < 5)
        result += ':';
    }
    return result;
  };

  Serial.println();
  Serial.println();
  Serial.println("Connecting to");
  Serial.println(WIFI_AP);

  WiFi.begin(ap_name, ap_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += mac2Str(mac);
  clientName += "-";
  clientName += String(micros() & 0xff, 16);
}

inline void connect2MQTTBroker(const String &clientName) {
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);

  if (client.connect((char *)clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);

    if (client.publish(topic, "hello from ESP8266")) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
  } else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    //delay(128 * 1000 * 10);
    abort();
  }
}

void setup() {
  // pinMode(D0, OUTPUT);
  // pinMode(D1, INPUT);
  Serial.begin(115200);
  delay(10);
  DhtSetup();
  PirSetup();
  Mq9Setup();
  /* Connecting to MQTT Broker:
   * 1. connect to an AP and recivce the client's name using @connectWifi
   * 2. connect to MQTT broker and publish a sample message using
   * @connect2MQTTBroker
   */
  String clientName;
  connectWifi(clientName);
  connect2MQTTBroker(sha1(clientName));
}

void loop() {
  static int counter = 0;
  String payload;

  constexpr auto addDHTpayload = [](String &payload) {
    float temp, humid;
    DhtRead(temp, humid);

    payload += ",\"air temperature\":";
    payload += temp;
    payload += ",\"air humidity\":";
    payload += humid;
  };

  constexpr auto addPirpayload = [](String &payload){
    int state;
    PirRead(state);
    payload += ",\"Motion State\":";
    payload += state;
  };
  constexpr auto addMQ9payload = [](String &payload){
    int state;
    Mq9Read(state);
    payload +=",\"Gas Sensor\":";
    payload +=state;
  };

  constexpr auto publishPayload = [](const String &payload) {
    if (client.connected()) {
      Serial.print("Publishing payload: ");
      Serial.println(payload);

      if (client.publish(topic, (char *)payload.c_str())) {
        Serial.println("Publish ok");
      } else {
        Serial.println("Publish failed");
      }
    }
  };

  payload = "{";

  payload += "{\"micros\":";
  payload += micros();
  payload += ",\"counter\":";
  payload += counter;

  addDHTpayload(payload);

  addPirpayload(payload);
  
  addMQ9payload(payload);
  
  payload += "}";

  publishPayload(payload);
  ++counter;
  delay(5000);
}
