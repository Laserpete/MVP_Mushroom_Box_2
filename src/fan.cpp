#include <Arduino.h>

#include "header.h"

const int MAX_DUTY_CYCLE = (int)(pow(2, FAN_PWM_RESOLUTION) - 1);

int dutyCycle;

void setupFan() {
  ledcSetup(FAN_PWM_CHANNEL, FAN_PWM_FREQUENCY, FAN_PWM_RESOLUTION);
  ledcAttachPin(FAN_PIN, FAN_PWM_CHANNEL);
  Serial.print("PWM max duty cycle = ");
  Serial.println(MAX_DUTY_CYCLE);
  setFanSpeed(FAN_IDLE_DUTY_CYCLE);
}
void setFanSpeed(int PWMVal) {
  ledcWrite(FAN_PWM_CHANNEL, PWMVal);
  Serial.print("Current Fan duty cycle = ");
  Serial.println(PWMVal);
}
