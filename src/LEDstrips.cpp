#include <Arduino.h>

#include "header.h"

bool sunHasRisen, sunHasSet, dayTime = false;

void setupLEDstrips() {
  ledcSetup(LED_STRIP_CHANNEL, 1000, 8);
  ledcAttachPin(LED_STRIP_PIN, LED_STRIP_CHANNEL);
  ledcAttachPin(UV_STRIP_PIN, LED_STRIP_CHANNEL);
  Serial.println("LED strips setup");
}

bool timeControlLEDstrips(DateTime now) {
  int timeControl = now.hour() + HOURS_OFFSET;

  if (timeControl == SUNRISE_TIME) {
    sunrise();
  }
  if (timeControl == SUNSET_TIME) {
    sunset();
  }
  if ((timeControl >= SUNRISE_TIME) && (timeControl <= SUNSET_TIME)) {
    return dayTime = true;
  } else if ((timeControl >= SUNSET_TIME) || (timeControl <= SUNRISE_TIME)) {
    return dayTime = false;
  }
}

void sunrise() {
  sunHasSet = false;
  int sunLevel = 0;

  if (sunHasRisen == false) {
    Serial.println("Sunrise");
    sunHasRisen = true;
    void displaySunriseOnLCD();

    do {
      sunLevel++;
      ledcWrite(LED_STRIP_CHANNEL, sunLevel);
      Serial.println(sunLevel);
      delay(SUN_ITERATION_TIME);
      displaySunriseOnLCD();
      if (sunLevel == 255) {
        Serial.println("Sunrise finished");
        sunHasRisen = true;
      }

    } while (sunLevel <= 255);
  }
}

void sunset() {
  sunHasRisen = false;
  int sunLevel = 255;

  if (sunHasSet == false) {
    Serial.println("Sunset");
    sunHasSet = true;

    do {
      sunLevel--;
      ledcWrite(LED_STRIP_CHANNEL, sunLevel);
      Serial.println(sunLevel);
      delay(SUN_ITERATION_TIME);
      displaySunsetOnLCD();
      if (sunLevel == 0) {
        Serial.println("Sunset finished");
        sunHasSet = true;
      }

    } while (sunLevel >= 1);
  }
}

void dayNight(bool dayTime) {
  if (dayTime == true) {
    ledcWrite(LED_STRIP_CHANNEL, MAX_LIGHT_LEVEL);
    Serial.println("It is now day time");
  }
  if (dayTime == false) {
    ledcWrite(LED_STRIP_CHANNEL, 0);
    Serial.println("It is now night time");
  }
}