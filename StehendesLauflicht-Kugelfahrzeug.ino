// Autor: Peter

#include "Checkerboard.hpp"
#include <Adafruit_NeoPixel.h>

#define NEO_PIXEL_PIN 11
#define NEO_PIXEL_LED_COUNT 24

Adafruit_NeoPixel neo_pixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

Checkerboard checkerboard;

void setup() {
  neo_pixel.begin();
}

void loop() {
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    neo_pixel.setPixelColor(i, // todo: white);
  }
  
  neo_pixel.show();
}
