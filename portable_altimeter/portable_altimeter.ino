#include <LiquidCrystal.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_BME280 bme;  // I2C
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12); using the mega board that came with the kit Eric gave me
  // initialize the LCD library with the GPIO numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

const int zeroButton = 4;// input for resetting display to 0 

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
    
  bool status = bme.begin();
//  if (!status) {
//    Serial.println("Could not find a valid BMP280 sensor, check wiring or change I2C address!");
//    while (1);
//  }
  //lcd.print("Altitude");
}
void loop() {
lcd.setCursor(0, 1);
//lcd.print(bme.readPressure()/3386 + 0.77); 
lcd.print(bme.readAltitude(1021)*3.3);
delay(2000);                         
}
