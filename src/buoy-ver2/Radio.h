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
		byte txAddress[5];
		byte rxAddress[5];
		Packet receivedData;
		Packet transmitData;
	public:
		Radio(byte ce, byte csn, byte * rx, byte * tx);
		bool initializeRadio();
		bool receive(Packet * packet);
		bool transmit(Packet * packet);
};

#endif

