#pragma once

#include "Arduino.h"
#include "Vec2.hpp"

class AutoPositionierung {
public:
	void setup();
	void motor_ansteurerung(int motor_left, int motor_right);
	void update();

	Vec2 auto_position;
	float Orientation_radians = 0.f;

private:
	unsigned long prev_millis = 0;
	unsigned long current_millis = 0;
	int ml, mr; // motor ansteuerung 0-255
	float Vr=0;                     //Geschwindigkeit rechts in m/s
	float Vl=0;                     //Geschwindigkeit links in m/s
	unsigned int t;                 //Dauer des letzten Programmdurchlaufs
	float k=0.525;                  //Faktor k zur groben Korrektur
	float r=1;                      //Faktor r zur Feinkorrektur für Reibung etc
	int current_orient=0;                  //Orientation des Fahrzeugs (in 0.1°)
	int prev_orient=0;                  //letzte Orientation des Fahrzeugs (in 0.1°)
	int Orientation;               //tatsächliche Orientation in °
	float b=0.13;                   //Abstand der Räder in m
	float a;                      //Differenz der Geschwindigkeiten
};