/**
* Sketch for the prototype of the dynamite fishing detection buoy.
* =================================================================
* Written by Jeremy Andrews I. Zantua
* jeremyzantua@gmail.com
* 13 March 2021
* =================================================================
* IMPORTANT NOTES
* - This sketch uses the TMRh20 version of the nRF24 library.
*   Library: https://github.com/nRF24/RF24/
*   Guide: https://forum.arduino.cc/index.php?topic=421081
*
* - This sketch has been used and tested only on a chinese clone of
*   the Arduino Nano. It is the version running a CH340G chip.
*
* - This sketch was written with the intention of testing on only one node and one station.
*   If you want to add more nodes, you will have to individually set up each node with a
*   unique node address. See variable rxAddress[] below.
*/

#include "Packet.h"
#include "Buzzer.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RF_CE_PIN   9
#define RF_CSN_PIN 10
const byte stationAddress[5] = { 'R','x','a','a','a' };	// Transmit to this address.
RF24 radio(RF_CE_PIN, RF_CSN_PIN);
Buzzer buzzer(7); // Initialize on D8.
int hydrophone = A0;

Packet outgoing;

struct Status {
	bool radioInitialized;
	int lastLevel;
	unsigned long lastMeasureTime;
} status;

struct Settings {
	unsigned long measurementInterval = 10;
} settings;

void setup() {
	pinMode(hydrophone, INPUT);
	if (radio_initialize()) {
		status.radioInitialized = true;
		buzzer.genericOK();
	}
	else {
		radio_errorLoop();
	}
}

void loop() {
	if (isTimeToMeasure()) {
		measure();
		outgoing.setContent(status.lastLevel);
		radio_send(&outgoing);
	}
}
