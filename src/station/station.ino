/**
* Sketch for the prototype of the dynamite fishing detection station.
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
*   unique node address. See variable nodeAddr[] below.
*/

#include "Packet.h"
#include "Buzzer.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
const byte address[5] = {'R','x','a','a','a'}; // Receive from this address
RF24 radio(CE_PIN, CSN_PIN);
Buzzer buzzer(8); // Initialize on D8.

Packet incoming;

struct Status {
	bool radioInitialized;
} status;

void setup() {
	Serial.begin(115200);
	Serial.print("Initializing radio...");	
	// Check if transceiver is connected.
	if (radio_initialize()) {
		status.radioInitialized = true;
		Serial.println("OK");
	}
	else {
		Serial.println("ERROR");
		radio_errorLoop();
	}
}

void loop() {
	if (radio.available()) {
		radio.read(incoming.data, sizeof(incoming.data)); // Read data from rf buffer and store it into packet's array.
		Serial.println(incoming.getContent());
	}
}

