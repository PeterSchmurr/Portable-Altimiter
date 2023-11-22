//stabalize rate to only readout for an altitude change of more than 1 ft

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

// control variables
#define cutoff 2 // minimum altitude  change ( in feet) required for new rate calculation
#define delayInterval 1000 // interval in milliseconds between loop iterations

#define OLED_ADDR   0x3C
#define BME_280_ADDR 0x77

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
Adafruit_BME280 bme;

const int zeroButton = 16;// input for resetting display to 0
float altitude; // current reading from bme280
float pressure;
float zero =0; // altitude at time of zero calibration 
float delta;// current altitude minus altitude at time of zero calibration 
float reading1;
float reading2;
float reading3;
float reading4;
float reading5;
float reading6;
float reading7;
float reading8;

int sn=1;
float r;

void setup() {
  Serial.begin(115200);
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

  pressure = bme.readPressure();
  pressure = lround(pressure)-int(lround(pressure)) % 10;
  altitude = pressure*(-0.278) + 28160;
  
  
   //r=averageRate();
  
  collectFiveReadings(altitude);
  if (sn==6)
  {
      
       r = (derivativeEstimateFiveReadings(reading1,reading2,reading4,reading5));
    Serial.println("rate   " + String(r));
    sn=1;
    }

  
  //Serial.println("Serial number = " + String(sn));

  delta = altitude - zero;
  display.clearDisplay();
  display.setCursor(0,0);
  display.println (String("alt:")+ String( int(delta)));
  display.setCursor(0,18);
  //display.println (String("rate:")+ String( int(1.5)));
   display.println ("rate: "+ String(r));
  display.display();
  
  //Serial.println(String("alt:")+ String( int(delta)));

  

delay(delayInterval);                       
}

	 float derivativeEstimateFiveReadings(float x_2,float x_1, float x1,float x2)
	{
		float rate = 0.083333333*(x_2 );
		rate = rate - 0.66666666*(x_1);
		rate = rate +0.66666666*(x1);
		rate = rate -0.083333333* (x2) ;
		
		rate = rate*(1000.00/delayInterval);
		
		return round(rate);
	}
  



	// collects five altitude readings in sequence and assigns them to global variables reading1 through reading5
	void collectFiveReadings(double reading){

	  switch(sn){
	    case 1:
	    	reading1 = reading;
	    	Serial.println("reading1 = "+String(reading1));
	    	sn = 2;
	    	break;
	    case 2:
	    	reading2 = reading;
	    	Serial.println("reading2 = "+String(reading2));
	    	sn = 3;
	    	break;
	    case 3:
		      reading3 = reading;
		      Serial.println("reading3 = "+String(reading3));
		      sn = 4;
		      break;
	    case 4:
		      reading4 = reading;
		      Serial.println("reading4 = "+String(reading4));
		      sn = 5;
		      break;
	    case 5:
		      reading5 = reading;
		      Serial.println("reading5 = "+String(reading5));
		      sn = 6;
		      
	  }
	}

  
