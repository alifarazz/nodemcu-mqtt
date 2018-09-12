#ifndef PIR_HPP
#define PIR_HPP

constexpr auto Mottion_Pin = D0 ;

void PirSetup(){
    pinMode(Mottion_Pin,INPUT);
}
void PirRead(int &state){
    state  = digitalRead(Mottion_Pin);
    Serial.println(state);
    
    if (state){
        Serial.println("Motion detected!");
    }
    else{
        Serial.println("No Motion");
    }
}

#endif
