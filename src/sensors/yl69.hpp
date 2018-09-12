#ifndef YL69_HPP
#define YL69_HPP

#include <Arduino.h>

constexpr auto yl69_Pin = A0;
constexpr auto thresholdValue = 800; 

void yl69Setup(){

}
void yl69Read(int & state){
    int ReadData = digitalRead(yl69_Pin);
    if (ReadData < thresholdValue){
        state = 0 ;
        Serial.println("- Doesn't need watering");
    }
    else{
        state = 1 ;
        Serial.println(" - Time to water your plant");
    }
}
#endif