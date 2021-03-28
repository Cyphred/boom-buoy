#ifndef H_TRANSCEIVER
#define H_TRANSCEIVER

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Packet.h"

class Radio {
	private:
		RF24 rf;
		const byte txAddress[5];
		const byte rxAddress[5];
		Packet receivedData;
		Packet transmitData;
	public:
		bool initializeRadio();
		bool receive(Packet * packet);
		bool transmit(Packet * packet);
};

#endif

