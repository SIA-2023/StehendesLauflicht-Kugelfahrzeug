// Autor: Peter

#pragma once

struct Vec2 {
  float x = 0.f, y = 0.f;

  Vec2(float x = 0.f, float y = 0.f)
    : x(x), y(y) {}

  Vec2 operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
  }

  Vec2 rotiert(float radians) const {
    float c = cos(radians);
    float s = sin(radians);
    return Vec2(c * x - s * y, s * x + c * y);
  }
};