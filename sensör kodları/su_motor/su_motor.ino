void setup() {

  pinMode(15,OUTPUT);
  
}

void loop() {
  
Serial.println("Plant Watering will begin!");
  
digitalWrite(15, HIGH);
  
  
delay(5000);

  
 digitalWrite(15, LOW);

Serial.println("Plant Watered!");
                
  
}
