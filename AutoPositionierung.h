#pragma once

#include "Vec2.hpp"

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
Vec2 auto_position;
float Orientation_radians = 0.f;

void bestimme_position() {
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
