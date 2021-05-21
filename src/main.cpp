/* Controller for MVP Mushroom Box 2.

  Featrues include heated wick humidifier and LED lights and LCD display

  LEDs controlled by real time clock, humidifier controlled by feedback loop
  from HTU21D

  Max current draw for version 1 was 3.3 amps

*/

#include <Arduino.h>
#include <Wire.h>

#include "header.h"

#define LOOP_TIME 1000
unsigned long lastLoop = 0;
bool humidifierIsOn;

void setup() {
  Serial.begin(115200);
  setupClock();
  setupHumidifier();
  setupLEDstrips();
  setupLCD();
  setupHTU21D();
}

void loop() {
  if (millis() >= (lastLoop + LOOP_TIME)) {
    // State machine image on discord chat with Tim

    // Implement noblocking sunrise & sunset
    // int brightness = getSunBrightness(time, lastTimeChanged,
    // currentSunBrightness); setBrightness(brightness)

    // Should I start the sunrise?
    // If it is started, andf it is time, call sunrise and increment
    // sunrise(getSunState());

    lastLoop = millis();
    SensorData sensorData = getSensorData();
    DateTime dateTime = getCurrentTimeFromRTC();

    dayNight(timeControlLEDstrips(dateTime));
    humidifierIsOn = controlHumidifier(sensorData);
    whatToDisplayOnLCD(sensorData, dateTime, humidifierIsOn);
  }
}