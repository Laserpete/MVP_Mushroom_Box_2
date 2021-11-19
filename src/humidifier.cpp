#include <Arduino.h>

#include "header.h"

void setupHumidifier() {
  pinMode(HUMIDIFIER_PIN, OUTPUT);
  digitalWrite(HUMIDIFIER_PIN, LOW);
  Serial.println("Humidifier setup");
}

bool controlHumidifier(SensorData getSensorData) {
  if (getSensorData.humidity <= HUMIDITY_SETTING) {
    digitalWrite(HUMIDIFIER_PIN, HIGH);
    setFanSpeed(FAN_HUMIDIFY_DUTY_CYCLE);
    Serial.println("Humidifier On");
    return true;

  } else {
    digitalWrite(HUMIDIFIER_PIN, LOW);
    setFanSpeed(FAN_IDLE_DUTY_CYCLE);
    Serial.println("Humidifier Off");
    return false;
  }
};
