#define RADIO_DELAY 3		// Delay between each transmission attempt.
#define RADIO_MAX_RETRIES 5	// Maximum number of retries before connection time out.

/**
* Attempt initializing the radio transceiver.
*
* @return true if successful.
*/
bool radio_initialize() {
	radio.begin();
	if (radio.isChipConnected()) {
		radio.setDataRate(RF24_250KBPS);
		radio.openWritingPipe(txAddress);
		radio.openReadingPipe(1, rxAddress);
		radio.setRetries(RADIO_DELAY, RADIO_MAX_RETRIES);
		radio.startListening();
		return true;
	}
	else
		return false;
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
	radio.read(&packet->data, sizeof(packet->data)); // Read data from rf buffer and store it into packet's array.
}

/**
 * Transmits data to the TX address.
 *
 * @param *packet is the pointer to the packet where the received data will be written to.
 * @return true if an acknowledgement has been received.
 */
bool radio_transmit(Packet * packet) {
	radio.stopListening();
	bool acknowledged = radio.write(&packet->data, sizeof(packet->data));
	radio.startListening();
	if (acknowledged);
		return true;
	return false;
}
