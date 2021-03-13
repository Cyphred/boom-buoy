/*
* Written by Jeremy Andrews I. Zantua
* jeremyzantua@gmail.com
* 13 March 2021
*
* This sketch uses the TMRh20 version of the nRF24 library.
* Library: https://github.com/nRF24/RF24/
* Guide: https://forum.arduino.cc/index.php?topic=421081
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int mic = A0; // Pin for hydrophone

void setup() {
}

void loop() {
    long soundLevel = 0;
    for(int i=0; i<32; i++) {
        soundLevel += analogRead(pinAdc);
    }
    soundLevel >>= 5;
}
