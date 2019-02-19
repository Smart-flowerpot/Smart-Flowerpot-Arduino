#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#include <ESP8266WiFi.h>

const char* ssid = "ETUNET-asistan";
const char* password = "tobb1234";

const int plant_id = 1;
const String plant_name = "menekşe";
const String plant_type = "aerhurasia";
int status_water_engine = 0;
int moisture_air = 0;   // yüzde olarak veriyor
int moisture_soil = 0;  // 0-1024 arası (yüzdeye çevirildi)
int temperature_air = 0;  // celcius
int frostbite = 0;   // çiğ oluşma noktası yüzde
int light = 0;

const char* host = "eventsappp.live";
String path_post = "";
String path_get = "";

int DHT11_pin = 2; // DHT11_pin olarak Dijital 2'yi belirliyoruz.
int suMotoru_pin = 15;
dht11 DHT11_sensor; // DHT11_sensor adında bir DHT11 nesnesi oluşturduk.
 
void setup()
{
  Serial.begin(115200);
  pinMode(suMotoru_pin , OUTPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
void loop()
{
  if(status_water_engine == 1){
    digitalWrite(suMotoru_pin , LOW);
    status_water_engine = 0;  
  }
  
  DHT11_sensor.read(DHT11_pin);
  moisture_air = (int)DHT11_sensor.humidity;
  temperature_air = (int)DHT11_sensor.temperature; 
  frostbite = DHT11_sensor.dewPoint();
  moisture_soil = analogRead(A0);
  Serial.println(moisture_air);
  Serial.println(temperature_air);
  Serial.println(moisture_soil);
  Serial.println(frostbite);
 
  path_post = String("/SmartFlowerpot/update_plant.php?plant_id=")+plant_id+"&light="+light+"&temperature="+temperature_air+"&moisture_air="+moisture_air+"&moisture_soil="+moisture_soil+"&frostbite="+frostbite+"&water="+status_water_engine+"&name="+plant_name+"&type="+plant_type;
  path_get = String("/SmartFlowerpot/get_plant.php?id=")+plant_id;
  
  WiFiClient client;


  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    client.print(String("POST ") + path_post + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" + 
           "Connection: close\r\n\r\n");

    Serial.println("[Response post:]");
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


 Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Response get:]");
    client.print(String("GET ") + path_get + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" + 
           "Connection: close\r\n\r\n");

    Serial.println("[Response:]");
  
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        String w = line.substring(line.lastIndexOf(":")+2, line.length()-2);
        if(w.equals("1")){
          status_water_engine = 1;
        }
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
