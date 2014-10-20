/*
 * pixels.h
 *
 *  Created on: Oct 16, 2014
 *      Author: thomas
 */

#ifndef PIXELS_H_
#define PIXELS_H_

#define NUM_STRIPS 3  // number of strips of LEDs
#define NUM_PIXELS 60  // number LEDs per strip
#define IND_INTERVAL 500
#define IND_BLINK_INTERVAL 300
#define IND_VOLT_LOW 30.0
#define IND_VOLT_HIGH 50.0

#define STATE_OFF 0
#define STATE_ON 1
#define STATE_BLINK_LOW 2
#define STATE_BLINK_HIGH 3
#define STATE_RAMP 4
#define STATE_RESET 5

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


// externed function declarations
#ifdef __cplusplus
extern "C" {
#endif
void initPixels();
void setPixel(uint8_t strip, uint16_t pixel, uint32_t color);
void stripShow(uint8_t strip);
void setAll(uint8_t r, uint8_t g, uint8_t b);
uint32_t Wheel(byte WheelPos);
#ifdef __cplusplus
} // extern "C"
#endif

//internal function declarations
//extern Adafruit_NeoPixel* strips[];


#endif /* PIXELS_H_ */
