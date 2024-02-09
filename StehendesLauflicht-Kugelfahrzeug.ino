// Autor: Peter

#include <Adafruit_NeoPixel.h>

#include "Vec2.hpp"
#include "AutoConfig.hpp"

// zum testen
#include "Motor.h"
Motor left_motor, right_motor;
unsigned long prev_millis = 0;

Adafruit_NeoPixel neo_pixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

Vec2 auto_position;
float auto_orientation = 0.f;

using Farbe = uint32_t;
Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2);

void setup() {
  // zum testen
  left_motor.init(7, 8, 10, true);
  right_motor.init(5, 6, 9);

  neo_pixel.begin();
  neo_pixel.setBrightness(50);
  neo_pixel.clear();

  prev_millis = millis();
}

void loop() {
  unsigned long current_millis = millis();
  float delta_time = (current_millis - prev_millis) * 0.001f;
  prev_millis = current_millis;
  
  // test motor ansteuerung
  left_motor.set_speed(250);
  right_motor.set_speed(250);
  float motor_speed = 10.f; // 10cm/s
  
  auto_position.y += motor_speed * delta_time;
  
  neo_pixel.clear();
  
  const Farbe farbe1 = neo_pixel.Color(255, 0, 0);
  const Farbe farbe2 = neo_pixel.Color(0, 0, 0);
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    Vec2 licht_position = auto_position + lichter_abtaende[i].rotiert(auto_orientation);
    neo_pixel.setPixelColor(i, schachbrett_farbe(licht_position, 6.f, farbe1, farbe2));
  }
  neo_pixel.show();
}

Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2) {
  // 'volatile' MUSS hier sein, ansonsten wird flip wegoptimisiert und ist immer true
  // ähnlicher bug: https://stackoverflow.com/questions/67359667/how-to-prevent-c-compiler-optimising-variable
  volatile bool flip = ((int)(pos.x / scale) + (int)(pos.y / scale)) % 2 == 0;
  return flip ? farbe1 : farbe2;
}
