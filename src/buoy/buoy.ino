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

// Tansceiver variables
#define CE_PIN   9
#define CSN_PIN 10
const byte receiveAddress[5] = {'R','x','A','A','A'};
//RF24 radio(CE_PIN, CSN_PIN);

// Hydrophone variables
const int mic = A0;
int noiseThreshold;

void setup() {
	Serial.begin(115200);
	Serial.println("Buoy Initialized");
	pinMode(13, OUTPUT);
}

void loop() {
	long soundLevel = 0;
	readSoundLevel(&soundLevel);
	if (soundLevel > noiseThreshold)
		warnStation();
	delay(10);
}

/**
* Reads the analog sound level being picked up by the mic and saves its value.
*/
void readSoundLevel(long * level) {
	for(int i=0; i<32; i++)
		*level += analogRead(mic);
	*level >>= 5;
}

/**
* Transmit a warning signal to the station.
*/
void warnStation() {

}
