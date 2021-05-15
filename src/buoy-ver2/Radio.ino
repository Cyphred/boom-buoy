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
		radio.setRetries(RADIO_DELAY, RADIO_MAX_RETRIES);
		radio.openWritingPipe(stationAddress);
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
* Sends a packet to the station.
*/
bool radio_send(Packet * packet) {
	return radio.write(&packet->data, sizeof(&packet->data));
}
