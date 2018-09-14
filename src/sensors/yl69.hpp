#ifndef YL69_HPP
#define YL69_HPP

#include <Arduino.h>

constexpr auto YL69_PIN = A0;
constexpr auto YL69_THRESHOLDVALUE = 800;

void Yl69Setup() {}
int Yl69Read(int &state) {
  int readData = digitalRead(YL69_PIN);

  if (readData < YL69_THRESHOLDVALUE) {
    state = 0;
    Serial.println("- Doesn't need watering");
  } else {
    state = 1;
    Serial.println(" - Time to water your plant");
  }

  return 0;
}

// TODO: add error-checking

#endif
