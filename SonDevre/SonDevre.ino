#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#include <ESP8266WiFi.h>

const char* ssid = "ETUNET-asistan";
const char* password = "tobb1234";
unsigned char status_water_engine = 0;
WiFiServer server(80); 
int DHT11_pin=2; // DHT11_pin olarak Dijital 2'yi belirliyoruz.
int suMotoru=15;
dht11 DHT11_sensor; // DHT11_sensor adında bir DHT11 nesnesi oluşturduk.
 
void setup()
{
  Serial.begin(115200);
  pinMode(15,OUTPUT);
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
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());       //asdasdasdasda
}
 
void loop()
{
  digitalWrite(15,HIGH);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  int chk = DHT11_sensor.read(DHT11_pin);
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/EngineOff") != -1)
  {
    status_water_engine = 0;   
    digitalWrite(15 , LOW);
    Serial.println("Engine OFF");
  }
  else if(req.indexOf("/EngineOn") != -1)
  {
    status_water_engine = 1;
    digitalWrite(15 , HIGH);
    Serial.println("Engine ON");
  }
  
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>Water Engine Status</h1>\r\n";
  web += "<p>\r\n";
  if(status_water_engine == 1)
      web += "Engine is On\r\n";
  else
      web += "Engine is Off\r\n";
  web += "</p>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/EngineOn\">\r\n";
  web += "<button>Engine On</button >\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  
  web += "<a href=\"/EngineOff\">\r\n";
  web += "<button>Engine Off</button >\r\n";
  web += "</a>\r\n";

  client.println(web);
  
  client.println("Nem Orani (%): <br>");
  client.println((float)DHT11_sensor.humidity, 2);
 
  client.println("Sicaklik (Celcius): <br>");
  client.println((float)DHT11_sensor.temperature, 2);
 
  client.println("Sicaklik (Kelvin): <br>");
  client.println(DHT11_sensor.kelvin(), 2);
  
  client.println("Sicaklik (Fahrenheit): <br>");
  client.println(DHT11_sensor.fahrenheit(), 2);
 
  client.println("Cig Olusma Noktasi: <br>");
  client.println(DHT11_sensor.dewPoint(), 2);
  client.println("<br>------------------");
  client.println("<br>------------------<br>");
  client.println(analogRead(A0)); 

  client.print("</body>\r\n");
  client.print("</html>\r\n");
  
}
