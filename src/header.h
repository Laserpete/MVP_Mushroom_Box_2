#include <RTClib.h>

#define LED_STRIP_PIN 2
#define UV_STRIP_PIN 4
#define LED_STRIP_CHANNEL 0

#define HUMIDIFIER_PIN 15

#define FAN_PIN 13

#define WS8212_PIN 27

#define SPEAKER_PIN 25
#define SPEAKER_CHANNEL 1

#define MAX_LIGHT_LEVEL 255

#define HUMIDITY_SETTING 90

#define HOURS_OFFSET 0

#define DISPLAY_SWITCH_TIME 10

#define MAXIMUM_LIGHT_LEVEL_PWM 255
#define HOURS_OF_LIGHT 12
#define DAYTIME_OFFSET 0

typedef struct _SensorData {
  float temperature;
  int temperatureAsInt;
  float humidity;
  int humidityAsInt;
} SensorData;

void setupPins();

void setupHTU21D();
void htu21dSensorHeater(SensorData);
SensorData getSensorData();

void setupLCD();
void whatToDisplayOnLCD(SensorData, DateTime, bool);
void displaySensorDataOnLCD(SensorData);
void displayTimeOnLCD(DateTime);
void displayStatusOnLCD();
void displaySunriseOnLCD();
void displaySunsetOnLCD();
void displayHumidifierStatusOnLCD(SensorData);

void setupHumidifier();
bool controlHumidifier(SensorData);

void setupLEDstrips();
int determineSunriseTime();
int determineSunsetTime();
int getSunBrightness(DateTime);
void setLEDBrightness(int);

void setupClock();
DateTime getCurrentTimeFromRTC();
void serialPrintCurrentTime(DateTime now);

void setupSpeaker();
void playMusic();

void setupWS8212LEDs();