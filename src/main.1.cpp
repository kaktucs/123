#include <Arduino.h>
#include "Ticker.h"

volatile int tic, Dimmer, setDimmer;
volatile int flag1, flag2;

void tiker_interrupt();
void pulse_trig();
void analogport();


Ticker timer1(tiker_interrupt, 50, 0, MICROS_MICROS);
Ticker timer2(pulse_trig, 220,0 , MICROS_MICROS);
Ticker timer3(analogport, 1000);

void tiker_interrupt(){
    tic++;

    if (tic > Dimmer){
        digitalWrite(27, 1);
        timer2.start();
        timer1.stop();
        //гавно ёбаное

    }

}

void zero_cross(){
    digitalWrite(27, 0);
    tic = 0;
    timer1.start();
}

void pulse_trig(){
    digitalWrite(27, 0);
    timer2.stop();
}

void analogport(){
    Dimmer = analogRead(4);
    Dimmer = map(Dimmer, 0, 4028, 0, 200);
    Serial.println(String(" ") + Dimmer + " " + tic +" " + flag2);
}
void setup() {
    Serial.begin(115200);
    delay(500);
    pinMode(4, INPUT); //analog potentiometer pin
    pinMode(27, OUTPUT);
    digitalWrite(27, 1);// pin 27 triac gate pin 
    delay(300);
    attachInterrupt(17, zero_cross, RISING); //pin 17 zerocross 
    timer3.start();
}

void loop() {
    timer1.update();
    timer2.update();
    timer3.update();
}