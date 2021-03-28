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

// Data structures
#include "Packet.h"
#include "Radio.h"
#include "Hydrophone.h"
#include "Buzzer.h"

#define CE_PIN   9
#define CSN_PIN 10
const byte rxAddress[5] = { 'R','x','A','A','A' };	// Receive from this address
const byte txAddress[5] = { 'T','x','a','a','a' };	// Transmit to this address
Radio radio(CE_PIN, CSN_PIN, rxAddress, txAddress);
Hydrophone hydrophone(A0, 32);	// Initialize on A0 with 32 samples
Buzzer buzzer(8);		// Initialize on D8

// Time Variables ============================================================================
unsigned long lastPing;			// Time last pinged by the station.
unsigned int pingInterval;		// Interval between each ping.

// Operational Variables =====================================================================
// The operation mode of the buoy.
// 0 - Monitor mode, this is the default.
// 1 - Stream mode, this will stream live noise levels to the station.
#define MODE_DISCONNECTED 0
#define MODE_MONITOR 1
#define MODE_STREAM 2
byte mode;

void setup() {
}

void loop() {
}
