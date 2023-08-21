#include "FastLED.h"

#define LED_PIN 0
#define LED_NUM 1

bool relayOn = true;

CRGB leds[LED_NUM];

void setup(void){
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(50);

  // 9600 speed is needed for HW-655 to work
  Serial.begin(9600);
  pinMode(  2 , INPUT_PULLUP);
}


void turnOn() {
  Serial.write("\xa0\x01"); // byte sequence for opening relay
  Serial.write(0x00);   // apparently because of the 0x00
  Serial.write(0xa1);   // you need to send on multiple lines

  FastLED.clear();
  leds[0] = CRGB::Green;
  FastLED.show();
  relayOn = false;
}

void turnOff() {
  Serial.write("\xa0\x01\x01\xa2"); // byte sequence for closing relay

  FastLED.clear();
  leds[0]= CRGB::Red;
  FastLED.show();
  relayOn = true;
}

void toggle() {
  if (relayOn) {
      turnOn();
  }
  else {
      turnOff();
  }
}

void loop(void){
Serial.println("toggle");
 toggle();
 delay (3000);

}