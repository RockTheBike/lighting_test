// Do not remove the include below
#include "lighting_test.h"

#define VERSION "Rock the Bike Speaker Lighting 1.0"

#define ENABLE_PROTECT 0
#define ENABLE_PIXELS 1
#define ENABLE_SENSE 1
#define DEBUG 0

#if ENABLE_PIXELS
#include "pixels.h"
#include <Adafruit_NeoPixel.h>

#endif

#define BLINK_INTERVAL 500
#define DISPLAY_INTERVAL 1000
#define PIXEL_INTERVAL 500

#define PIN_LED 13

#define COLOR_WHEEL_DURATION 3000.0

#if ENABLE_SENSE
#define PIN_VOLTS_P A0
#define PIN_VOLTS_M A1

#define AVG_CYCLES 100.0
#define VOLT_INTERVAL 10
#define VOLTS_LOW 15.0

#define VOLTCOEFF 13.179 // correct value for new blue arbduino v2
#define AMPCOEFF 8.0682 // 583 - 512 = 71; 71 / 8.8 amps = 8.0682
#define AMPOFFSET 512.0 // when current sensor is at 0 amps this is the ADC value
#endif

//typedef unsigned long ulong;
unsigned long time = 0;
unsigned long lastVolt = 0;
unsigned long lastDisplay = 0;
unsigned long lastBlink = 0;
unsigned long lastPixels = 0;

#if ENABLE_SENSE
unsigned int voltAdc = 0;
float voltAdcAvg = 0.0;
float voltsP = 0.0;
float voltsM = 0.0;
float volts = 0.0;
#endif

boolean isBlinking = false;

//The setup function is called once at startup of the sketch
void setup() {

#if ENABLE_PIXELS
  	initPixels();
#endif

#if ENABLE_SENSE
	pinMode(PIN_VOLTS_P, INPUT); // voltage ADC
	pinMode(PIN_VOLTS_M, INPUT); // voltage ADC
#endif

	pinMode(PIN_LED, OUTPUT);

	Serial.begin(115200);
}

//int blinkCount = 0;
void doBlink(){

	isBlinking = !isBlinking;
	digitalWrite(PIN_LED, isBlinking);

}

#if ENABLE_SENSE
float averageF(float val, float avg){
	if(avg == 0)
		avg = val;
	return (val + (avg * (AVG_CYCLES - 1))) / AVG_CYCLES;
}

float adc2volts(float adc){
	return adc / VOLTCOEFF;
}

void doVolts(){
	voltAdc = analogRead(PIN_VOLTS_P);
	float tVolts = adc2volts(voltAdc);
	voltsP = averageF(tVolts, voltsP);
	//voltAdc = analogRead(PIN_VOLTS_M);
	//tVolts = adc2volts(voltAdc);
	//voltsM = averageF(tVolts, voltsM);
}
#endif

#if ENABLE_PIXELS

float wheelPosition = 0.0;
unsigned long prevWheelTime = 0;
unsigned long diffWheelTime = 0;

float hue1 = 0.0;
float hue2 = 1.0 / 6.0; // 0/3 == red,  1/3 == green,  2/3 == blue

void advancePixels(){
	diffWheelTime = time - prevWheelTime;
	prevWheelTime = time;
	float wheelAdvance = (float)diffWheelTime / (float)COLOR_WHEEL_DURATION;
	hue1 += wheelAdvance;
	hue2 += wheelAdvance;
	for(int i = 0; i < NUM_STRIPS; i++){
		//Adafruit_NeoPixel* strip = strips[0];
		for(int j = 0; j < NUM_PIXELS; j++){
			// set each half of strip to a different hue
			if(j < NUM_PIXELS / 2){
				setPixel(i,j,Wheel(hue1));
				//strip->setPixelColor(j, Wheel(hue1));
			} else {
				setPixel(i,j,Wheel(hue2));
			}
		}
		stripShow(i);
	}
}



void doPixels(){

#if ENABLE_SENSE
	// check if we're below minimum volts, and blink, otherwise, proceed
	//volts = voltsP + voltsM;

	if(voltsP < VOLTS_LOW)
	{
		if(isBlinking){
			setAll(255, 0, 0);
		}
		else {
			setAll(0, 0, 0);
		}
		return;
	}
#endif

	advancePixels();
}
#endif

void doDisplay(){
	Serial.print("volts: ");
	Serial.print(volts);
	Serial.print(", voltsP: ");
	Serial.print(voltsP);
	Serial.print(", voltsM: ");
	Serial.print(voltsM);
	Serial.println();
}

// The loop function is called in an endless loop
void loop() {

	time = millis();

	if(time - lastBlink > BLINK_INTERVAL){
		lastBlink = time;
		doBlink();
	}

	if(time - lastDisplay > DISPLAY_INTERVAL){
		lastDisplay = time;
		doDisplay();
	}

#if ENABLE_SENSE
	if(time - lastVolt > VOLT_INTERVAL){
		lastVolt = time;
		doVolts();
	}
#endif

#if ENABLE_PIXELS
	if(time - lastPixels > PIXEL_INTERVAL){
		lastPixels = time;
		doPixels();
	}
#endif

// Some example procedures showing how to display to the pixels:
//	colorWipe(strip1, strip1.Color(255, 105, 0), 5); // Orange
//	colorWipe(strip2, strip2.Color(255, 255, 0), 5); // Yellow
//	colorWipe(strip3, strip3.Color(0, 255, 0), 5); // Green
//	colorWipe(strip4, strip4.Color(0, 0, 255), 5); // Blue
//	colorWipe(strip5, strip5.Color(80, 0, 80), 5); // Violet

}
