#include <dht11.h>; // dht11 kütüphanesini ekliyoruz.
#include <ESP8266WiFi.h>;
#include <PubSubClient.h>;


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047             // Buzzer için gereken tanımlamalar.
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody1[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0
};
int melody2[] = {
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0
};
int melody3[] = {                                   // Buzzer  ses paternleri
  NOTE_G6, NOTE_E7, NOTE_G7, 0,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
 };
 int melody4[] = {
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0
}; 

int melody5[] = {
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

int tempo1[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

int tempo2[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
 };
 
 int tempo3[] = {
  9, 9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,                        // Ses paternleri.
  12, 12, 12, 12
 };
 
 int tempo4[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
 };
 
 int tempo5[] = {
  9, 9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

int i=0;
int j=0;
int buztime =0;
int delayvalue =0;
 
const char* ssid = "ETUNET-asistan";                   //Senkronize çalışması için gereken  Wifi bağlantısı.
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

unsigned long readTime;

#define DHT11_pin 4 // DHT11_pin olarak Dijital 2'yi belirliyoruz.
#define suMotoru_pin 15
#define led 2  // internal led
#define buz 5

const char* mqttServer = "m24.cloudmqtt.com";               // Yeni eklediğimiz mqtt server ayarları.
  const int mqttPort = 16309;
    const char* mqttUser = "cissktzx";
      const char* mqttPassword = "ETUpXfdiWfMO";

dht11 DHT11_sensor; // DHT11_sensor adında bir DHT11 nesnesi oluşturduk.
WiFiClient espClient;
PubSubClient client(espClient);



void setupWifi()
{
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)                 // Wifi Bağlantısı için gereken metod.
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
}

void connectMqtt()
{
    while (!client.connected()) {
    Serial.println("Connecting to MQTT...");                                 // Mqtt bağlantısı için gereken tanımlamalar.
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
  client.subscribe("motor");
}

bool checkBound(int newValue, int prevValue, int maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

void readSensor()
{      
  
                                                  // Sensörlerin çalışması için gereken metod.
  DHT11_sensor.read(DHT11_pin);
  int new_moisture_air = (int)DHT11_sensor.humidity;
  int new_temperature_air = (int)DHT11_sensor.temperature;                //Sensör tanımlalamarı
  int new_frostbite = DHT11_sensor.dewPoint();
  int new_moisture_soil = analogRead(A0);

  String s = String(new_moisture_soil) +","+ new_moisture_air  +","+ new_temperature_air +","+ frostbite;
   Serial.println(s.c_str());
      client.publish("sensorler", s.c_str(), true);
/*
  if (checkBound(new_moisture_air, moisture_air, 1)) {
      moisture_air = new_moisture_air;
      Serial.print("New temperature:");
      Serial.println(String(moisture_air).c_str());
      client.publish("havaNem", String(moisture_air).c_str(), true);
  }
  
  if (checkBound(new_temperature_air, temperature_air, 1)) {
      temperature_air = new_temperature_air;
      Serial.print("New temperature:");
      Serial.println(String(temperature_air).c_str());
      client.publish("havaIsi", String(temperature_air).c_str(), true);
  }
    
  Serial.println(frostbite);
  
  if (checkBound(new_moisture_soil, moisture_soil, 1)) {
      moisture_soil = new_moisture_soil;
      Serial.print("New Moisture Soil:");
      Serial.println(String(moisture_soil).c_str());
      client.publish("toprakNem", String(moisture_soil).c_str(), true);
  }
  */
}

void callback(char* topic, byte* payload, unsigned int length)
{
  
  
  Serial.print("Message arrived in topic: ");                                       //MOTOR LED AYARLARI
  Serial.println(topic);
  
  String temp = topic;
    String buff = "";

  if(temp.equals("motor")){
    for (int i = 0; i<length; i++) {
      buff += (char)payload[i];
    }
    
    Serial.println("Motor status is : " + buff);
    
    if(buff.toInt() == 0 ){
      digitalWrite(suMotoru_pin ,LOW);
      sing(melody5, tempo5);
    }
    else
    {
      digitalWrite(suMotoru_pin ,HIGH);
      sing(melody4, tempo4);
    }
  }
  else if(temp.equals("led"))
  {
      for (int i = 0; i<length; i++) {
        buff += (char)payload[i];
      }
      if(buff.equals("on"))
        digitalWrite(2,LOW);
      else
        digitalWrite(2,HIGH);
  }
 
  Serial.println();
    Serial.println("-----------------------");
}

void setup()
{
  
  Serial.begin(115200);
  pinMode(suMotoru_pin , OUTPUT);   
                                                //SU MOTORU SENKRONIZE CALISMASI ICIN GEREKEN METOD
  pinMode(led,OUTPUT);
  pinMode(buz, OUTPUT);

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  setupWifi();
  
  connectMqtt();
  
  readTime = 0;
}


void sing(int melody[], int tempo[])
{
  
  i=0;
  j=0;
  
  while(i < 16)
    if(millis() > buztime + delayvalue){                       //BUZZERIN CALISMASI ICIN GEREKEN METOD
      buztime = millis();
      delayvalue = 1000 / tempo[j] * 1.30;
      tone(buz, melody[i++], 15* tempo[j++]);
    }
}

void loop()
{
  
  if (!client.connected())
  {
    connectMqtt();
  }
  client.loop();

  if(millis() > readTime+6000)
  {
    readTime = millis();
    readSensor();
    
//    sing(melody3, tempo3);
  }
}
