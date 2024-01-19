// Autor: Peter

#include <Adafruit_NeoPixel.h>
#include "Schachbrett.hpp"

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

Vec2 auto_positino;
float auto_orientation = 0.f;

Schachbrett schachbrett(Adafruit_NeoPixel::Color(255, 255, 255), Adafruit_NeoPixel::Color(100, 100, 100), 10.f);

void setup() {
  neo_pixel.begin();
}

void loop() {
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    Vec2 licht_position = auto_positino + lichter_abtaende[i].rotiert(auto_orientation);
    neo_pixel.setPixelColor(i, schachbrett.farbe_bei_punkt(licht_position));
  }
  
  neo_pixel.show();
}