#include <LiquidCrystal.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_BME280 bme;  // I2C
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12); using the mega board that came with the kit Eric gave me
  // initialize the LCD library with the GPIO numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

const int zeroButton = 4;// input for resetting display to 0
int altitude; // current reading from bme280
int zero; // altitude at time of zero calibration 
int delta;// current altitude minus altitude at time of zero calibration 


void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);

  pinMode(zeroButton, INPUT);// 
    
  bool status = bme.begin();
//  if (!status) {
//    Serial.println("Could not find a valid BMP280 sensor, check wiring or change I2C address!");
//    while (1);
//  }
  //lcd.print("Altitude");
}
void loop() {
  if(digitalRead (zeroButton)==HIGH);
  {
    zero = bme.readPressure()/3386 + 0.77;
  }
  altitude = bme.readPressure()/3386 + 0.77;
  delta = altitude - zero;
  lcd.clear();
  lcd.setCursor(0, 1);
//lcd.print(bme.readPressure()/3386 + 0.77); 
lcd.print(zero);
delay(500);                         
}

/*
          lcd.clear();
          lcd.print("Enter Password");
          digitalRead(zeroButton);
          digitalWrite(zeroButton,LOW);
*/
 
