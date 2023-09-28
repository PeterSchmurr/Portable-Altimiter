//#include <LiquidCrystal.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_BME280 bme;  // I2C
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12); using the mega board that came with the kit Eric gave me
  // initialize the LCD library with the GPIO numbers of the interface pins
//LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

const int zeroButton = 32;// input for resetting display to 0
float altitude; // current reading from bme280
float zero =0; // altitude at time of zero calibration 
int delta;// current altitude minus altitude at time of zero calibration 


void setup() {
  //Wire.begin(
  Serial.begin(9600);
  //lcd.begin(16, 2);

  pinMode(zeroButton, INPUT_PULLDOWN);// 
    
  bool status = bme.begin(0X77);
  Serial.println("sensor status = "+status);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
    while (1);
  }
  else{
  Serial.println("BME280 sensor found");
  }
 //digitalWrite (zeroButton,LOW);
}
void loop() {
  if(digitalRead (zeroButton)==HIGH)
  {
    zero =  bme.readAltitude(1)*3.28;
    digitalWrite (zeroButton,LOW);
  }
  Serial.println("zeroButton value");
  Serial.println(digitalRead (zeroButton));
    altitude = bme.readAltitude(1)*3.28;
  delta = altitude - zero;
  Serial.println(String("zero:  ") + String(zero));
  //Serial.println(zero);
  Serial.println(String("altitude:  ") + String(altitude));
  // Serial.println(altitude);
  Serial.println("delta + " + delta);
  //Serial.println(delta);
  //Serial.println("delta = "+delta);
  //lcd.clear();
  //lcd.setCursor(0, 1);
//lcd.print(bme.readPressure()/3386 + 0.77); 
//lcd.print(delta);
delay(500);                         
}

/*
          lcd.clear();
          lcd.print("Enter Password");
          digitalRead(zeroButton);
          digitalWrite(zeroButton,LOW);
*/
 
