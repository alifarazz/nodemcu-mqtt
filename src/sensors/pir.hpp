#ifndef PIR_HPP
#define PIR_HPP

#include <Arduino.h>

constexpr auto PIR_PIN = D0;

void PirSetup() { pinMode(PIR_PIN, INPUT); }

int PirRead(int &state) {
  state = digitalRead(PIR_PIN);
  Serial.println(state);

  if (state) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No Motion");
  }

  return 0;
}

// TODO: add error-checking

#endif
