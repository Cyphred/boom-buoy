#define RADIO_DELAY 3		// Delay between each transmission attempt.
#define RADIO_MAX_RETRIES 5	// Maximum number of retries before connection time out.

void radio_initialize() {
	radio.begin();
	if ( radio.isChipConnected() ) {
		radio.setDataRate( RF24_250KBPS );
		radio.openWritingPipe( txAddress );
		radio.openReadingPipe( 1, rxAddress );
		radio.setRetries( RADIO_DELAY, RADIO_MAX_RETRIES );
		radio.startListening();
		status.radioInitialized = true;
	}
	else
		status.radioInitialized = false;
}
