#include <Arduino.h>
#include <FastLED.h>

#include "header.h"

CRGB leds[NUM_LEDS];

CRGBPalette16 currentPallette;
TBlendType currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemRGBPalette16 myRedWhiteBluePalette_p PROGMEM;

void setupWS2812LEDs() {
  FastLED.addLeds<LED_TYPE, WS2812_PIN, COLOUR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  currentPallette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void whatToDisplayOnLEDs(SensorData SensorData, bool humidifierIsOn) {
  if (humidifierIsOn == 1) {
    humidifyLightshowLEDs();
  }
}

void humidifyLightshowLEDs() {
  ChangePalettPeriodically();

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;  // motion speed

  FillLEDsFromPaletteColours(startIndex);
  FastLED.show();
}

void FillLEDsFromPaletteColours(uint8_t colourIndex) {
  uint8_t brightness = 255;
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPallette, colourIndex, brightness,
                               currentBlending);
    colourIndex += 3;
  }
}

void ChangePalettePeriodically() {}