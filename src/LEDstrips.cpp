#include <Arduino.h>

#include "header.h"

bool sunHasRisen, sunHasSet, dayTime = false;
int lastLEDStripChangeTime = 0;

void setupLEDstrips() {
  ledcSetup(LED_STRIP_CHANNEL, 1000, 8);
  ledcAttachPin(LED_STRIP_PIN, LED_STRIP_CHANNEL);
  ledcAttachPin(UV_STRIP_PIN, LED_STRIP_CHANNEL);
  Serial.println("LED strips setup");
}
int determineSunriseTime() {
  return (12 - (HOURS_OF_LIGHT / 2) + DAYTIME_OFFSET);
}

int determineSunsetTime() {
  return (12 + (HOURS_OF_LIGHT / 2) + DAYTIME_OFFSET);
}

int getSunBrightness(DateTime now) {
  static int currentBrightness;
  // If it is time for sunrise, iterate the light level upwards
  if (now.hour() == determineSunriseTime()) {
    if (currentBrightness < MAXIMUM_LIGHT_LEVEL_PWM) {
      currentBrightness++;
      Serial.print("Sunrise ");
      Serial.println(currentBrightness);
      return currentBrightness;
    } else {
      return MAXIMUM_LIGHT_LEVEL_PWM;
    }
  } else if (now.hour() == determineSunsetTime()) {
    if (currentBrightness > 0) {
      currentBrightness--;
      Serial.print("Sunset ");
      Serial.println(currentBrightness);
      return currentBrightness;
    } else {
      return 0;
    }
  } else if ((now.hour() < determineSunriseTime()) or
             (now.hour() > determineSunsetTime())) {
    Serial.println("Night Time");
    currentBrightness = 0;
    return currentBrightness;
  } else if ((now.hour() > determineSunriseTime()) and
             (now.hour() < determineSunsetTime())) {
    Serial.println("Day Time");
    currentBrightness = MAXIMUM_LIGHT_LEVEL_PWM;
    return currentBrightness;
  }
}

void setLEDBrightness(int desiredBrightness) {
  ledcWrite(LED_STRIP_CHANNEL, desiredBrightness);
}