/*
 * pixels.c
 *
 *  Created on: Oct 16, 2014
 *      Author: thomas
 */

#include "pixels.h"

// based directly from strandtest.ino, the example file supplied with Adafruit Neopixel libraries.
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_RGB Pixels are wired for RGB bitstream
// NEO_GRB Pixels are wired for GRB bitstream
// NEO_KHZ400 400 KHz bitstream (e.g. FLORA pixels)
// NEO_KHZ800 800 KHz bitstream (e.g. High Density LED strip)

//Adafruit_NeoPixel strips[NUM_PIXEL_STRIPS] = {
//		Adafruit_NeoPixel(NUM_PIXELS, pinPixels[0], NEO_GRB + NEO_KHZ800),
//		Adafruit_NeoPixel(NUM_PIXELS, pinPixels[1], NEO_GRB + NEO_KHZ800),
//		Adafruit_NeoPixel(NUM_PIXELS, pinPixels[2], NEO_GRB + NEO_KHZ800)
//};

uint8_t pinPixels[NUM_STRIPS] = {8, 12, 13};

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_PIXELS, pinPixels[0], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_PIXELS, pinPixels[1], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_PIXELS, pinPixels[2], NEO_GRB + NEO_KHZ800);

//Adafruit_NeoPixel* left = &strip1;
//Adafruit_NeoPixel* right = &strip2;
//Adafruit_NeoPixel* sub = &strip3;

Adafruit_NeoPixel* strips[3] = { &strip1, &strip2, &strip3 };

void initPixels() {

  	for (int i = 0; i < NUM_STRIPS; i++) {
  		pinMode(pinPixels[i], OUTPUT);
		strips[i]->begin();
		strips[i]->show(); // Initialize all pixels to 'off'
	}
}

//// Input a value 0 to 255 to get a color value.
//// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if (WheelPos < 85) {
		return strip1.Color(255 - WheelPos * 3, WheelPos * 3, 0);
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip1.Color(0, 255 - WheelPos * 3, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return strip1.Color(WheelPos * 3, 0, 255 - WheelPos * 3);
	}
}

//// Fill the dots one after the other with a color
//void colorWipe(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
//	for (uint16_t i = 0; i < strip.numPixels(); i++) {
//		strip.setPixelColor(i, c);
//		//strip.show();
//		//delay(wait);
//	}
//        strip.show();
//}
//void rainbow(Adafruit_NeoPixel strip, uint8_t wait) {
//	uint16_t i, j;
//	for (j = 0; j < 256; j++) {
//		for (i = 0; i < strip.numPixels(); i++) {
//			strip.setPixelColor(i, Wheel(strip, (i + j) & 255));
//		}
//		strip.show();
//		delay(wait);
//	}
//}
//// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(Adafruit_NeoPixel strip, uint8_t wait) {
//	uint16_t i, j;
//	for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
//		for (i = 0; i < strip.numPixels(); i++) {
//			strip.setPixelColor(i,
//					Wheel(strip, ((i * 256 / strip.numPixels()) + j) & 255));
//		}
//		strip.show();
//		delay(wait);
//	}
//}


// Fill the dots one after the other with a color
void setStrip(Adafruit_NeoPixel s, uint8_t r, uint8_t g, uint8_t b) {
	for (uint16_t i = 0; i < s.numPixels(); i++) {
		s.setPixelColor(i, r, g, b);
		//delay(wait);
	}
	s.show();
}

void setPixel(uint8_t s, uint16_t p, uint32_t c){
	strips[s]->setPixelColor(p, c);
}

void stripShow(uint8_t s){
	strips[s]->show();
}

void advanceAll(float wheelAdvance){
	for(int i = 0; i < NUM_STRIPS; i++){
		//setStrip(*strips[i], r, g, b);
		Adafruit_NeoPixel* strip = strips[i];
		for(uint16_t j = 0; j < strip->numPixels(); j++){
			uint32_t t = strip->getPixelColor(j);
			uint8_t r = (t >> 16) & 0xFF;
			uint8_t g = (t >> 8) & 0xFF;
			uint8_t b = t & 0xFF;
			strip->setPixelColor(j, Wheel(wheelAdvance));
		}
	}
}

void advanceWheel(uint32_t color, float advance){



}

void setAll(uint8_t r, uint8_t g, uint8_t b) {

	for(int i = 0; i < NUM_STRIPS; i++){
		setStrip(*strips[i], r, g, b);
	}
}
