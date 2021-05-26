#include <Arduino.h>

#include "header.h"

void setupHumidifier() {
  pinMode(HEATED_WICK_PIN, OUTPUT);
  pinMode(EXTRA_OPTOCOUPLED_PIN, OUTPUT);
  digitalWrite(HEATED_WICK_PIN, LOW);
  Serial.println("Humidifier setup");
}

bool controlHumidifier(SensorData getSensorData) {
  if (getSensorData.humidity <= HUMIDITY_SETTING) {
    digitalWrite(HEATED_WICK_PIN, HIGH);
    digitalWrite(EXTRA_OPTOCOUPLED_PIN, HIGH);
    Serial.println("Humidifier On");
    return true;

  } else {
    digitalWrite(HEATED_WICK_PIN, LOW);
    Serial.println("Humidifier Off");
    return false;
  }
};
