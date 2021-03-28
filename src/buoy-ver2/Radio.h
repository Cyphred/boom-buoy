#ifndef H_TRANSCEIVER
#define H_TRANSCEIVER

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Packet.h"

#define DELAY 3		// Delay between each transmission attempt.
#define MAX_RETRIES 5	// Maximum number of retries before connection time out.

class Radio {
	private:
		RF24 rf;
		byte txAddress[5];
		byte rxAddress[5];
		bool initialized;

	public:
		Radio(byte ce, byte csn, byte * rx, byte * tx);
		bool receive(Packet * packet);
		bool transmit(Packet * packet);
		bool isInitialized();
};

#endif

