#include "StehendesLauflicht.h"

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

void StehendesLauflicht::setup() {
	neo_pixel.begin();
	neo_pixel.setBrightness(50);
	neo_pixel.clear();
}

void StehendesLauflicht::update(const Vec2& position, float orientation_radians) {
	neo_pixel.clear();

	const Farbe rot = neo_pixel.Color(255, 0, 0);
	const Farbe gruen = neo_pixel.Color(0, 255, 0);
	for (int i = 0; i < NEO_PIXEL_LED_COUNT; i++) {
		Vec2 licht_position = position + lichter_abtaende[i].rotiert(orientation_radians);
		neo_pixel.setPixelColor(i, schachbrett_farbe(licht_position, 6.f, rot, gruen));
	}
	neo_pixel.show();
}

StehendesLauflicht::Farbe StehendesLauflicht::schachbrett_farbe(const Vec2& pos, float scale, Farbe farbe1, Farbe farbe2) {
	// 'volatile' MUSS hier sein, ansonsten wird flip wegoptimisiert und ist immer true
	// ähnlicher bug: https://stackoverflow.com/questions/67359667/how-to-prevent-c-compiler-optimising-variable
	volatile bool flip = ((int)(pos.x / scale) + (int)(pos.y / scale)) % 2 == 0;
	return flip ? farbe1 : farbe2;
}
