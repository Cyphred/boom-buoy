/**
* Initializes the transceiver.
*/
void initializeRadio() {
	radio.begin();
	if (radio.isChipConnected()) {
		radio.setDataRate( RF24_250KBPS );
		radio.openWritingPipe(stationAddr);
		radio.openReadingPipe(1, nodeAddr);
		radio.setRetries(3,5); // delay, count
		radio.startListening();
	}
	else {
		radioErrorBeep();
	}
}

void waitForConnection() {
	do {
		expectedType = 0;
		getData();
		// 70 is an arbitrary number that must be matched by the station
		if (newData == 1 && incomingByte == 70) {
			lastPing = millis();
			connected = true;
			break;
		}
	} while (true);
}

/**
* Gets the data from the receive buffer.
*/
void getData() {
	if (radio.available()) {
		if (expectedType == 0) {
			radio.read( &incomingByte, sizeof(incomingByte) );
			newData = 1;
		}
		else {
			radio.read( &incomingInt, sizeof(incomingInt) );
			newData = 2;
		}

		lastPing = millis();
	}
}

void sendByte() {
	radio.stopListening();
	bool rslt;
	rslt = radio.write( &outgoingByte, sizeof(outgoingByte) );
	radio.startListening();
	if (rslt) {
		// Acknowledge received
	}
	else {
		// Tx failed
	}
}

void sendInt() {
	radio.stopListening();
	bool rslt;
	rslt = radio.write( &outgoingInt, sizeof(outgoingInt) );
	radio.startListening();
	if (rslt) {
		// Acknowledge received
	}
	else {
		// Tx failed
	}
}

/**
 * Transmit a warning signal to the station.
 */
void warnStation() {
	tone(buzzer, 500, 100);
}
