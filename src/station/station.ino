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

#include "Constants.h" // Constants for command codes
#include "ConsoleConstants.h" // Constants for console commands
#include "Packet.h"
#include "Radio.h"
#include "Buzzer.h"

#define CE_PIN   9
#define CSN_PIN 10
const byte rxAddress[5] = {'T','x','a','a','a'}; // Receive from this address
const byte txAddress[5] = {'R','x','A','A','A'}; // Transmit to this address
// Radio radio(CE_PIN, CSN_PIN, rxAddress, txAddress);
Packet incoming;
Packet outgoing;
Buzzer buzzer(8); // Initialize on D8.
unsigned long lastPing;
struct Settings {
	unsigned int measurementInterval;	// Time in ms between each noise level measurement.
	int varianceThreshold;			// The percentage of tolerable variance 
	unsigned int pingTimeout;		// Time in ms before declaring TX as unresponsive.
	byte mode;				// Operational mode
} settings;

bool connectedToConsole;

void setup() {
	Serial.begin(9600);

	// Check if the transceiver is NOT ready for use.
	// If not ready, goes into an indefinite loop signalling a malfunction.
	// if (!radio.isInitialized())
	//	radioErrorLoop(); 
}

void loop() {
	if (Serial.available()) {
		interpretConsoleCommand(Serial.read());
	}
}

/**
* Infinite loop for indicating an error with initializing the transceiver.
*/
void radioErrorLoop() {
	while (true) {
		buzzer.radioError();
		delay(2000);
	}
}
