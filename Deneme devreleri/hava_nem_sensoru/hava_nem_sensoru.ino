#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
 
int DHT11_pin=2; // DHT11_pin olarak Dijital 2'yi belirliyoruz.
dht11 DHT11_sensor; // DHT11_sensor adında bir DHT11 nesnesi oluşturduk.
 
void setup()
{
  Serial.begin(115200);
}
 
void loop()
{
  int chk = DHT11_sensor.read(DHT11_pin);
 
  Serial.print("Nem Orani (%): ");
  Serial.println((float)DHT11_sensor.humidity, 2);
 
  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)DHT11_sensor.temperature, 2);
 
  Serial.print("Sicaklik (Kelvin): ");
  Serial.println(DHT11_sensor.kelvin(), 2);
  
  Serial.print("Sicaklik (Fahrenheit): ");
  Serial.println(DHT11_sensor.fahrenheit(), 2);
 
  Serial.print("Cig Olusma Noktasi: ");
  Serial.println(DHT11_sensor.dewPoint(), 2);
  Serial.println("------------------");
  
  // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
  delay(2000);
 
}
