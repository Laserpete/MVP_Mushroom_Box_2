#include <Arduino.h>

#include "header.h"

void setupSpeaker() { ledcAttachPin(SPEAKER_PIN, SPEAKER_CHANNEL); }

void playMusic() { ledcWriteNote(SPEAKER_CHANNEL, NOTE_C, 4); }