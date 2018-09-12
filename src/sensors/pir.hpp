#ifndef PIR_HPP
#define PIR_HPP

#include <Arduino.h>

constexpr auto Motion_Pin = D0 ;

void PirSetup(){
    pinMode(Motion_Pin,INPUT);
}
void PirRead(int &state){
    state = digitalRead(Motion_Pin);
    Serial.println(state);

    if (state){
        Serial.println("Motion detected!");
    }
    else{
        Serial.println("No Motion");
    }
}

#endif
