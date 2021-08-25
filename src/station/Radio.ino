/**
* Attempt initializing the radio transceiver.
*
* @return true if successful.
*/
bool radio_initialize() {
	radio.begin();
	if (radio.isChipConnected()) {
		radio.setDataRate(RF24_250KBPS);
		radio.openReadingPipe(1, address);
		radio.startListening();
		return true;
	}
	else {
		return false;
	}
}

/**
* Indefinitely loop to signal an error with the transceiver.
*/
void radio_errorLoop() {
	while (true) {
		buzzer.genericError();
		delay(1000);
	}
}

/**
* Fetches the data from the receive buffer of the transceiver and stores it.
*
* @param *packet is the pointer to the packet where the received data will be written to.
*/
void radio_storeReceivedDataIn(Packet * packet) {
	// Read data from rf buffer and store it into packet's array.
	radio.read(&packet->data, sizeof(packet->data)); 
}
