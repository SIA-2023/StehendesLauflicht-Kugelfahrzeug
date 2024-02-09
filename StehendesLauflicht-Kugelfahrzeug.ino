// Autor: Peter

#include <Adafruit_NeoPixel.h>

#include "Vec2.hpp"
#include "AutoConfig.hpp"


Adafruit_NeoPixel neo_pixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

Vec2 auto_position;
float auto_orientation = 0.f;

using Farbe = uint32_t;
Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");

  neo_pixel.begin();
  neo_pixel.setBrightness(100);
  neo_pixel.clear();
}

void loop() {
  auto_position.y += 0.1f;
  delay(10);
  
  neo_pixel.clear();
  
  const Farbe farbe1 = neo_pixel.Color(255, 255, 255);
  const Farbe farbe2 = neo_pixel.Color(0, 0, 0);
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    Vec2 licht_position = auto_position + lichter_abtaende[i].rotiert(auto_orientation);
    neo_pixel.setPixelColor(i, schachbrett_farbe(licht_position, 10.f, farbe1, farbe2));
  }
  neo_pixel.show();
}

Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2) {
  // 'volatile' MUSS hier sein, ansonsten wird flip wegoptimisiert und ist immer true
  // ähnlicher bug: https://stackoverflow.com/questions/67359667/how-to-prevent-c-compiler-optimising-variable
  volatile bool flip = ((int)(pos.x / scale) + (int)(pos.y / scale)) % 2 == 0;
  return flip ? farbe1 : farbe2;
}
