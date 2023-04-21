
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal.h>
Adafruit_BMP280 bmp;  // I2C
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

float altitude;




void setup() {
  
  Serial.begin(115200);
  lcd.begin(16,2);

  bool status = bmp.begin(0X77);
  Serial.println("sensor status = "+status);
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or change I2C address!");
    while (1);
  }
  //else{
  //Serial.println("BMP280 sensor found");
  //}
}
void loop() {
  
  
  altitude = bmp.readAltitude()*3.28; 
  Serial.println(altitude);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(altitude);
  
  
  delay(2000);                         
}



 
