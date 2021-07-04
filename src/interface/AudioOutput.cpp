#include "AudioOutput.hpp"

const uint8_t BUZZER_PIN = A0;

AudioOutput::AudioOutput() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
}

void AudioOutput::reset() {
  digitalWrite(BUZZER_PIN, HIGH);
}

void AudioOutput::buzz(int length, uint8_t count, int pause) {
  for (uint8_t i = 0; i < count; i++) {
    if (i > 0) {
      delay(pause);
    }
    digitalWrite(BUZZER_PIN, LOW);
    delay(length);
    digitalWrite(BUZZER_PIN, HIGH);
  }
}
