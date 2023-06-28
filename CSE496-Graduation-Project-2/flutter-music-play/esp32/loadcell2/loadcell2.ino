/*
 * Complete project details at https://RandomNerdTutorials.com/esp32-load-cell-hx711/
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/

/**
lehimli yere elini koyp dene
*/
#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

float cb_factor = 5000;
void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN);
  scale.set_scale(cb_factor);
  scale.tare();
}

void loop() {
  Serial.print("Measure : ");
  Serial.println(scale.get_units());
  delay(500);
}