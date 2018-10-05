#define BLYNK_NO_BUILTIN
#include <Arduino.h>
#include "Ticker.h"

volatile int tic, Dimmer, setDimmer;
volatile int flag1, flag2;

void tiker_interrupt();
void pulse_trig();
void analogport();


Ticker timer1(tiker_interrupt, 50, 0, MICROS_MICROS);
Ticker timer2(pulse_trig, 2000,0 , MICROS_MICROS);
Ticker timer3(analogport, 1000);

void IRAM_ATTR tiker_interrupt(){
    tic++;

    if (tic > Dimmer && flag1 == 0){
        digitalWrite(27, 1);
        //ledcWrite(1, 1);
        timer2.start();
        timer1.stop();
    }

}

void IRAM_ATTR zero_cross(){
    digitalWrite(27, 0);
    //ledcWrite(1, 175);
    tic = 0;
    timer1.start();
    //flag2++;
}

void IRAM_ATTR pulse_trig(){
    digitalWrite(27, 0);
    timer2.stop();
}

void IRAM_ATTR analogport(){
    Dimmer = analogRead(4);
    Dimmer = map(Dimmer, 0, 4028, 0, 200);
    Serial.println(String(" ") + Dimmer + " " + tic +" " + flag2);
}
void setup() {
    Serial.begin(115200);
    delay(500);
    //pinMode(0, OUTPUT);
    pinMode(4, INPUT);
    pinMode(27, OUTPUT);
    digitalWrite(27, 1);
    delay(300);
    attachInterrupt(digitalPinToInterrupt(17), zero_cross, RISING);
    timer3.start();
    while(1){
    timer1.update();
    timer2.update();
    timer3.update();
    yield();
    }
}

void loop() {
//delay(0);
}