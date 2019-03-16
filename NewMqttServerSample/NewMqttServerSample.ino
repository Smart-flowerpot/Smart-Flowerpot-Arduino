#include <ESP8266WiFi.h>;
#include <PubSubClient.h>;
 
const char* ssid = "ETUNET-asistan";
const char* password =  "tobb1234";
const char* mqttServer = "m24.cloudmqtt.com";
const int mqttPort = 16309;
const char* mqttUser = "cissktzx";
const char* mqttPassword = "zZ0msIVHewh2";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
  client.publish("test", "Hello from ESP8266");
  client.subscribe("test");
  client.subscribe("led");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  String temp = topic;
  if(temp.equals("test")){
    Serial.print("Message:");
    for (int i = 0; i<length; i++) {
      Serial.print((char)payload[i]);
    }
  }
  else if(temp.equals("led")){
      String s = "";
      for (int i = 0; i<length; i++) {
        s += (char)payload[i];
      }
      if(s.equals("on"))
        digitalWrite(2,LOW);
      else
        digitalWrite(2,HIGH);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}
 
void loop() {
  client.loop();
}
