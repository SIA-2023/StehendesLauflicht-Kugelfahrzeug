#include "AutoPositionierung.h"

void AutoPositionierung::setup() {
	prev_millis = millis();
}

void AutoPositionierung::motor_ansteurerung(int motor_left, int motor_right) {
	ml = motor_left;
	mr = motor_right;
}

void AutoPositionierung::update() {
	current_millis = millis();

	t = current_millis - prev_millis;

	// position bestimmung
	current_orient=prev_orient+((Vr-Vl)/(b))*t*k*r;
	current_orient=(current_orient+7200) % 3600;
	Orientation=current_orient/10;
	Orientation_radians = Orientation * (PI / 180.f);

	// motor geschwindigkeit
	if (ml < 70 && (ml > -70) ) Vl=0;
	if (ml >= 70) Vl=0.0121*pow(ml-70, 0.64);
	if (ml <= -70) Vl=-0.0121*pow(-ml-70, 0.64);

	if (mr < 70 && (mr >= -70) ) Vr=0;
	if (mr >= 70) Vr=0.0121*pow(mr-70, 0.64);
	if (mr <= -70) Vr=-0.0121*pow(-mr-70, 0.64);
	delay(10);

	r=-1.49*abs(Vr-Vl)+1.56;
	a=abs(Vr-Vl)*100;

	float delta_time = (current_millis - prev_millis) * 0.001f;

	float d = ((Vl + Vr) / 2.f) * delta_time;
	d *= 20.f; // passt geschwindigkeit an
	auto_position.x += d * sin(Orientation_radians);
	auto_position.y += d * cos(Orientation_radians);

	prev_orient=current_orient;
	prev_millis=current_millis;
}