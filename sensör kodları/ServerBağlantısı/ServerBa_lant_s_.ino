#include <ESP8266WiFi.h>

const char* ssid = "ETUNET-asistan";
const char* password = "tobb1234";

const char* host = "omercalisma123.xyz";
const char* path = "/SmartFlowerpot/add_plant.php?light=85&temperature=74&moisture=32&water=13&name=a&type=AT";

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("POST ") + path + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" + 
           "Connection: close\r\n\r\n");


    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}
