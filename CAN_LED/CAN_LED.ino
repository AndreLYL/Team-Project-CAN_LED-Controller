//#include <due_can.h>

#include <FastLED.h>

#define LED_PIN  7
#define NUM_LEDS  10

#define Serial SerialUSB

CRGB leds [NUM_LEDS];

void setup() {
  // WS2812 initialization
   FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);

    //Serial.begin(115200);



   //CAN Bus initialization
  
  
}

void loop() {

  //Serial.println("Hello Word");
  
  leds[0]=CRGB(255, 0, 0);
  FastLED.show();
  delay(500);
  leds[1]=CRGB(0, 255, 0);
  FastLED.show();
  delay(500);
  leds[2]=CRGB(0, 0, 255);
  FastLED.show();
  delay(500);
  leds[3]=CRGB(110, 0, 0);
  FastLED.show();
  delay(500);
  leds[4]=CRGB(0, 110, 0);
  FastLED.show();
  delay(500);
  leds[5]=CRGB(0, 0, 110);
  FastLED.show();
  delay(500);
}
