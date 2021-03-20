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
*   unique node address. See variable nodeAddr[] below.
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BUZZER 8

// Transceiver Variables =====================================================================
#define CE_PIN   9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);

// Addresses of this node and the station.
const byte nodeAddr[5] = {'R','x','A','A','A'};
const byte stationAddr[5] = {'T','x','a','a','a'};

// Hydrophone Variables ======================================================================
const int mic = A0;		// Analog pin of the hydrophone.
unsigned int noiseThreshold;	// Maximum noise threshold to be considered normal.
unsigned int maxNoiseLevel;	// Highest noise level encountered
unsigned long readings;		// Keeps track of the number of readings taken.

// Time Variables ============================================================================
unsigned long lastPing;			// Time last pinged by the station.
unsigned long lastNoiseReading;		// Time of last noise reading.
unsigned int measurementInterval;	// Interval between each noise measurement.
unsigned int pingInterval;		// Interval between each ping.

// Operational Variables =====================================================================
// The operation mode of the buoy.
// 0 - Monitor mode, this is the default.
// 1 - Stream mode, this will stream live noise levels to the station.
#define MODE_DISCONNECTED 0
#define MODE_MONITOR 1
#define MODE_STREAM 2
byte mode;

// Communication Variables ===================================================================
bool newData; // true when there is new, unprocessed data.

// Packets can hold either a byte, an unsigned integer, or both at the same time.
// Address 0 is for the byte, which will be used for bytes equivalent to commands.
// Address 1 is for the unsigned integer, which will be used for passing integer data.
byte incomingPacket[3];
byte outgoingPacket[3];

void setup() {
	pinMode(BUZZER, OUTPUT);
	if (!initializeRadio())
		radioInitErrorLoop();
	waitForInitialization();
}

void loop() {
	if (isConnectionTimedOut()) {
		disconnect();
		waitForInitialization();
		return;
	}

	if (mode == MODE_MONITOR)
		monitorModeRoutine();
	else 
		streamModeRoutine();
}

/**
* Routine for monitor mode.
*/
void monitorModeRoutine() {
	fetchInbox();
	if (newByte || newUInt)
		interpretNewData();

	if (isTimeToMeasureNoise()) {
		long noiseLevel = measureNoiseLevel();
		if (noiseLevel >= noiseThreshold)
			warnStation();

		// Save noise level if it is higher than the last recorded maximum.
		if (noiseLevel > maxNoiseLevel)
			maxNoiseLevel = noiseLevel;

		lastNoiseReading = millis(); // Record the time this reading was taken.
	}
}
