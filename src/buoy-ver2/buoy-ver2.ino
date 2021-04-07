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

#include "Constants.h"	// Constants for command codes
#include "Packet.h"
#include "Radio.h"
#include "Hydrophone.h"
#include "Buzzer.h"

#define CE_PIN   9
#define CSN_PIN 10
const byte rxAddress[5] = { 'R','x','A','A','A' };	// Receive from this address.
const byte txAddress[5] = { 'T','x','a','a','a' };	// Transmit to this address.
Radio radio(CE_PIN, CSN_PIN, rxAddress, txAddress);
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


void setup() {
	// Check if the transceiver is NOT ready for use.
	// If not ready, goes into an indefinite loop signalling a malfunction.
	if (!radio.isInitialized())
		radioErrorLoop(); 

	settings.mode = MODE_DISCONNECTED; // Set mode to disconnected by default.
}

void loop() {
	switch (settings.mode) {
		case MODE_MONITOR:
			if (isTimeToMeasure())
				measure();
			break;
		case MODE_STREAM:
			; // TODO Add routine for stream mode.
			break;
		case MODE_DISCONNECTED:
			initialize();
			break;
	}

	if (receive())
		interpret(&incoming);

	if (isConnectionTimedOut())
		disconnect();
}

/**
* Determines if it has been to long since the station has pinged for the buoy's presence.
* If gap between current time and time of last ping is equal to or greater than the threshold,
* assume that the station has been disconnected.
*
* @return is true if connection has timed out. False if not.
*/
bool isConnectionTimedOut() {
	if ((millis() - lastPing) < settings.pingTimeout)
		return false;
	return true;
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
