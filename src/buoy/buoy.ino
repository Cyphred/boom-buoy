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
#include <EEPROM.h>

#define BUZZER 8

// Transceiver Variables =====================================================================
#define CE_PIN   9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte nodeAddr[5] = {'R','x','A','A','A'};
const byte stationAddr[5] = {'T','x','a','a','a'};
bool newData;
// Incoming data
byte incomingByte;
int incomingInt;
// Outgoing data
byte outgoingByte;
int outgoingInt;
/**
* Expected data type of the next transmission from station.
* 0 - single byte that translates to a command.
* 1 - integer that is sent after a command. Can be used to set thresholds.
*/
byte expectedType = 0;
bool connected;

// Hydrophone variables
const int mic = A0;
int noiseThreshold;
int maxNoiseLevel = 0; // Highest noise level encountered

// Buzzer variables
const int buzzer = 8;

// Time variables
unsigned long lastPing = 0; // Time last communicated with station
unsigned long lastNoiseReading = 0;
byte noiseMeasurementInterval = 10;

/**
* The operation mode of the buoy.
* 0 - Monitor mode, this is the default.
* 1 - Stream mode, this will stream live noise levels to the station.
*/
byte mode;

void setup() {
	Serial.begin(9600);
	pinMode(buzzer,OUTPUT);
	switchToMonitorMode(); // Monitor mode by default
	loadNoiseThreshold();
	initializeRadio();
	waitForConnection();
}

void loop() {
	getData();
	if (newData) {
		interpretNewData();
		newData = false;
	}

	if ((millis() - lastNoiseReading) >= noiseMeasurementInterval) {
		long noiseLevel = 0;
		getNoiseLevel(&noiseLevel);
		if (noiseLevel >= noiseThreshold)
			warnStation();

		// Record noise level if it is higher than the current record.
		if (noiseLevel > maxNoiseLevel)
			maxNoiseLevel = noiseLevel;

		lastNoiseReading = millis();
	}
}
