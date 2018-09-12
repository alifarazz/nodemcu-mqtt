#ifndef MQ9_HPP
#define MQ9_HPP

#include <Arduino.h>

constexpr auto MQ_Pin = 10 ;


void Mq9Setup(){
    pinMode(MQ_Pin,INPUT);
}
void Mq9Read(int & state){
    state = !digitalRead(MQ_Pin);
    Serial.println(state);

    if (~state){
        Serial.println("Gas detected!");
    }
    else{
        Serial.println("No Gas");
    }
}

#endif