#pragma once

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Vec2.hpp"

#define NEO_PIXEL_PIN 11
#define NEO_PIXEL_LED_COUNT 24

class StehendesLauflicht {
public:
	void setup();
	void update(const Vec2& position, float orientation_radians);

private:
	Adafruit_NeoPixel neo_pixel = Adafruit_NeoPixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

	using Farbe = uint32_t;
	static Farbe schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2);
};