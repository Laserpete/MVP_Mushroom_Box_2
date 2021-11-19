/* Controller for MVP Mushroom Box 2.

  Featrues include heated wick humidifier and LED lights and LCD display

  LEDs controlled by real time clock, humidifier controlled by feedback loop
  from HTU21D

  Max current draw for version 1 was 3.3 amps (Heated wick)
  Current power draw measured at PSU output is 12V 2.3A

*/

#include <Arduino.h>
#include <Wire.h>

#include "header.h"

#define LOOP_ITERATION_TIME 1
unsigned long lastLoop = 0;
bool humidifierIsOn;

void setup() {
  Serial.begin(115200);
  setupClock();
  setupHumidifier();
  setupFan();
  setupLEDstrips();
  setupLCD();
  setupHTU21D();
}

void loop() {
  DateTime dateTime = getCurrentTimeFromRTC();
  if (dateTime.unixtime() >= (lastLoop + LOOP_ITERATION_TIME)) {
    lastLoop = dateTime.unixtime();

    serialPrintCurrentTime(dateTime);
    setLEDBrightness(getSunBrightness(dateTime));

    SensorData sensorData = getSensorData();
    humidifierIsOn = controlHumidifier(sensorData);
    whatToDisplayOnLCD(sensorData, dateTime, humidifierIsOn);
  }
}