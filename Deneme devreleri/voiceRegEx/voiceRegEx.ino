int redPin = 9; // R petal on RGB LED module connected to digital pin 11
int greenPin = 10; // G petal on RGB LED module connected to digital pin 9
int bluePin = 11; // B petal on RGB LED module connected to digital pin 10
byte com = 0; //reply from voice recognition

void setup()
{
Serial.begin(9600);
pinMode(redPin, OUTPUT); // sets the redPin to be an output
pinMode(greenPin, OUTPUT); // sets the greenPin to be an output
pinMode(bluePin, OUTPUT); // sets the bluePin to be an output
delay(2000);
Serial.write(0xAA);
Serial.write(0x37);
delay(1000);
Serial.write(0xAA);
Serial.write(0x21);

color(255,255,255); // turn RGB LED on -- white
delay(5000);
}

void loop() // run over and over again
{
while(Serial.available())
{
com = Serial.read();
switch(com)
{
case 0x11:
color(255,255,255); // turn RGB LED on -- white
break;
case 0x12:
color(255, 0, 0); // turn the RGB LED red
break;
case 0x13:
color(0,255, 0); // turn the RGB LED green
break;
case 0x14:
color(0, 0, 255); // turn the RGB LED blue
break;
case 0x15:
color(0,0,0); // turn the RGB LED off
break;
}
}
}

void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function
{
analogWrite(redPin, red*102/255);
analogWrite(bluePin, blue*173/255);
analogWrite(greenPin, green*173/255);
}