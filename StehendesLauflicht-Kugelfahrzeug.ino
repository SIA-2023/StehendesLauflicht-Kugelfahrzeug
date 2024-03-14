// Autor: Peter

#include "AutoPositionierung.h"
AutoPositionierung auto_positionierung;

#include "StehendesLauflicht.h"
StehendesLauflicht stehendes_lauflicht;

#include "Motor.h"
Motor left_motor, right_motor;

void setup() {
	left_motor.init(7, 8, 10, true);
	right_motor.init(5, 6, 9);
	stehendes_lauflicht.setup();
	auto_positionierung.setup();
}

void loop() {  
	int ml = 100;
	int mr = 200;
	left_motor.set_speed(ml);
	right_motor.set_speed(mr);
	auto_positionierung.motor_ansteurerung(ml, mr);

	auto_positionierung.update();

	stehendes_lauflicht.update(auto_positionierung.auto_position, auto_positionierung.Orientation_radians);
}