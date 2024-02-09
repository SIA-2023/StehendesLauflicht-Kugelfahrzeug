// Autor: Peter

#pragma once

#define NEO_PIXEL_PIN 11
#define NEO_PIXEL_LED_COUNT 24

// Abstand aller Lichter zu der Mitte des Autos
// Auto: 10cm * 10cm
// Abstand der Ränder: 0.5cm
// Abstand zwischen Lichtern 1,8cm
Vec2 lichter_abtaende[NEO_PIXEL_LED_COUNT] = {
  // rechts
  Vec2(5.f, -4.5f),
  Vec2(5.f, -2.7f),
  Vec2(5.f, -0.9f),
  Vec2(5.f, 0.9f),
  Vec2(5.f, 2.7f),
  Vec2(5.f, 4.5f),

  // vorne
  Vec2(4.5f, 5.f),
  Vec2(2.7f, 5.f),
  Vec2(0.9f, 5.f),
  Vec2(-0.9f, 5.f),
  Vec2(-2.7f, 5.f),
  Vec2(-4.5f, 5.f),

  // links
  Vec2(-5.f, 4.5f),
  Vec2(-5.f, 2.7f),
  Vec2(-5.f, 0.9f),
  Vec2(-5.f, -0.9f),
  Vec2(-5.f, -2.7f),
  Vec2(-5.f, -4.5f),

  // hinten
  Vec2(-4.5f, -5.f),
  Vec2(-2.7f, -5.f),
  Vec2(-0.9f, -5.f),
  Vec2(0.9f, -5.f),
  Vec2(2.7f, -5.f),
  Vec2(4.5f, -5.f),
};
