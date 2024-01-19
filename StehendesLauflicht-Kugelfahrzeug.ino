// Autor: Peter

#include <Adafruit_NeoPixel.h>

#define NEO_PIXEL_PIN 11
#define NEO_PIXEL_LED_COUNT 24

// Ist NICHT abhänig von der Rotation
uint32_t led_muster[NEO_PIXEL_LED_COUNT];

Adafruit_NeoPixel neo_pixel(NEO_PIXEL_LED_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  neo_pixel.begin();
}

void rgb_muster();
void muster_anwenden(int rotationAngle);

float rotation_degrees = 45;
void loop() {
    rgb_muster();
    
    rotation_degrees += 0.05;
    muster_anwenden((int)rotation_degrees);
}

void rgb_muster() {
  uint32_t red = neo_pixel.Color(255, 0, 0);
  uint32_t green = neo_pixel.Color(0, 255, 0);
  uint32_t blue = neo_pixel.Color(0, 0, 255);
  uint32_t white = neo_pixel.Color(255, 255, 255);
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
  	int j = i % 4;
    if (j == 0)
      led_muster[i] = red;
    else if (j == 1)
      led_muster[i] = green;
    else if (j == 2)
      led_muster[i] = white;
    else
      led_muster[i] = blue;
  }
}

// Steuer LED-Strip an, um 'rotationAngle' gedreht
void muster_anwenden(int rotation_degrees) {
  float anglePerLED = NEO_PIXEL_LED_COUNT / 360.f;
  int led_offset = (int)(anglePerLED * rotation_degrees);
  for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
    int led_index = (i + led_offset % NEO_PIXEL_LED_COUNT + NEO_PIXEL_LED_COUNT) % NEO_PIXEL_LED_COUNT;
    neo_pixel.setPixelColor(i, led_muster[led_index]);
  }
  
  neo_pixel.show();
}
