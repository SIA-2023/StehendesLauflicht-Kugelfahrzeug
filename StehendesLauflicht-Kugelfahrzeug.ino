// Autor: Peter

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "Vec2.hpp"

#define NEO_PIXEL_PIN 11
#define NEO_PIXEL_LED_COUNT 24

Adafruit_NeoPixel neo_pixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// abstand aller lichter zu der Mitte des Autos
Vec2 lichter_abtaende[NEO_PIXEL_LED_COUNT] = {
  // vorne
  Vec2(60.f, -60.f),
  Vec2(36.6f, -60.f),
  Vec2(13.3f, -60.f),
  Vec2(-13.3f, -60.f),
  Vec2(-36.6f, -60.f),
  Vec2(-60.f, -60.f),

  // hinten
  Vec2(60.f, 60.f),
  Vec2(36.6f, 60.f),
  Vec2(13.3f, 60.f),
  Vec2(-13.3f, 60.f),
  Vec2(-36.6f, 60.f),
  Vec2(-60.f, 60.f),

  // links
  Vec2(-60.f, 60.f),
  Vec2(-60.f, 36.6f),
  Vec2(-60.f, 13.3f),
  Vec2(-60.f, -13.3f),
  Vec2(-60.f, -36.6f),
  Vec2(-60.f, -60.f),

  // rechts
  Vec2(60.f, 60.f),
  Vec2(60.f, 36.6f),
  Vec2(60.f, 13.3f),
  Vec2(60.f, -13.3f),
  Vec2(60.f, -36.6f),
  Vec2(60.f, -60.f),
};

Vec2 auto_position;
float auto_orientation = 0.f;

using Farbe = uint32_t;
Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  Serial.begin(9600);
  Serial.println("Hello");

  neo_pixel.begin();
  neo_pixel.setBrightness(100);
  neo_pixel.clear();
}

void loop() {
  neo_pixel.clear();
  
  const Farbe farbe1 = neo_pixel.Color(255, 255, 255);
  const Farbe farbe2 = neo_pixel.Color(0, 0, 0);
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    Vec2 licht_position = auto_position + lichter_abtaende[i].rotiert(auto_orientation);
    neo_pixel.setPixelColor(i, schachbrett_farbe(licht_position, 30.f, farbe1, farbe2));
  }
  neo_pixel.show();
}

Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2) {
  // 'volatile' MUSS hier sein, ansonsten wird flip wegoptimisiert und ist immer true
  // ähnlicher bug: https://stackoverflow.com/questions/67359667/how-to-prevent-c-compiler-optimising-variable
  volatile bool flip = ((int)(pos.x / 30.f) + (int)(pos.y / 30.f)) % 2 == 0;
  return flip ? farbe1 : farbe2;
}
