#ifndef MQ9_HPP
#define MQ9_HPP

#include <Arduino.h>

constexpr auto MQ9_PIN = 10;

void Mq9Setup() { pinMode(MQ9_PIN, INPUT); }

int Mq9Read(int &state) {
  state = digitalRead(MQ9_PIN);
  Serial.println(state);

  if (state) {
    Serial.println("Gas detected!");
  } else {
    Serial.println("No Gas");
  }

  return 0;
}

// TODO: add error-checking

#endif
