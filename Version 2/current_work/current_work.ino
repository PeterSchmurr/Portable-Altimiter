#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

#define OLED_ADDR   0x3C
#define BME_280_ADDR 0x77

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
Adafruit_BME280 bme;

const int zeroButton = 15;// input for resetting display to 0
float altitude; // current reading from bme280
float zero =0; // altitude at time of zero calibration 
float delta;// current altitude minus altitude at time of zero calibration 
float reading1;
float reading2;
int sn=1;
int r;

void setup() {
  
  Serial.begin(9600);
  pinMode(zeroButton,OUTPUT);  
  bool sensorStatus = bme.begin(BME_280_ADDR);
  Serial.println("sensor status = "+sensorStatus);
  if (!sensorStatus) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
    while (1);
     Serial.println("2");  
  }
  else{
  Serial.println("BME280 sensor found");
  }

  bool displayStatus = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  Serial.println("OLED status = "+displayStatus);
  if (!displayStatus) {
    Serial.println("Could not find a valid OLED display, check wiring or change I2C address!");
    while (1);
  }
  else{
  
 Serial.println("OLED display found");
  }
  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
}


void loop() {
  if(digitalRead (zeroButton)==HIGH)
  {
    zero =  bme.readAltitude(1013.25)*3.28;
    digitalWrite (zeroButton,LOW);
  }
  altitude = bme.readAltitude(1013.25)*3.28;
  if (sn=3)
  {
    r = int(rate(reading2,reading1));
    Serial.println("rate   " + String(r));
    sn=1;
  }
  
  delta = altitude - zero;
  display.clearDisplay();
  display.setCursor(0,0);
  display.println (String("alt:")+ String( int(delta)));
  display.setCursor(0,18);
  //display.println (String("rate:")+ String( int(1.5)));
   display.println ("rate: "+ String(r));
  display.display();
  
  Serial.println(String("alt:")+ String( int(delta)));

  

delay(500);                         
}
//consumes two altitude readings and returns the difference between the two
int rate(float altitude1, float altitude2)
{
  return int(altitude1 - altitude2)/120;
  
}

// collectts two altitude readings in sequence and assigns them to variables reading1 and reading2
void collectReadings(float reading){

  if (sn=1)
  {
    reading1 = reading;
    sn = 2;
  }
  else if(sn=2)
  {
    reading2 = reading;
    sn = 3;
  }
  else
  {
    sn = 1;
  }
}
