#ifndef DHT_HPP
#define DHT_HPP

#include <Arduino.h>

// #include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

constexpr auto DHTPIN = D1;
constexpr auto DHTTYPE = DHT22;

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t DHT_delayMS;

void dhtSetup() {
  sensor_t sensor;

  dht.begin();

  dht.temperature().getSensor(&sensor);
  DHT_delayMS = sensor.min_delay / 1000;
  dht.humidity().getSensor(&sensor);
  DHT_delayMS = max((int32_t)DHT_delayMS, sensor.min_delay / 1000);
}

int dhtRead(float &temp, float &humid) {
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  temp = event.temperature;
  dht.humidity().getEvent(&event);
  humid = event.relative_humidity;
  return isnan(humid) || isnan(temp);
}

// TODO: implement dhtGetAttr
//       use namespace ?

#endif
