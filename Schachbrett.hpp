// Autor: Peter

#pragma once

#include "Vec2.hpp"

using Farbe = uint32_t;

class Schachbrett {
public:
	Schachbrett(Farbe farbe1, Farbe farbe2, float scale)
    : farbe1(farbe1), farbe2(farbe2), scale(scale) {}

  Farbe farbe_bei_punkt(const Vec2& position) const {
    Vec2 scaled_position = Vec2(position.x / scale, position.y / scale);
    bool flip = ((int)scaled_position.x + (int)scaled_position.y) % 2 == 0;
    return flip ? farbe1 : farbe2;
  }

private:
  Farbe farbe1, farbe2;
  float scale = 1.f;
};
