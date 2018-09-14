#ifndef DHT_HPP
#define DHT_HPP

#include <Arduino.h>

// #include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

constexpr auto DHT_PIN = D1;
constexpr auto DHT_TYPE = DHT22;

DHT_Unified dht(DHT_PIN, DHT_TYPE);

uint32_t DHT_delayMS;

void DhtSetup() {
  sensor_t sensor;

  dht.begin();

  dht.temperature().getSensor(&sensor);
  DHT_delayMS = sensor.min_delay / 1000;
  dht.humidity().getSensor(&sensor);
  DHT_delayMS = max((int32_t)DHT_delayMS, sensor.min_delay / 1000);
}

int DhtRead(float &temp, float &humid) {
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
