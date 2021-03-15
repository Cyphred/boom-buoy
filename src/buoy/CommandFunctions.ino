/**
* Interprets the new data.
*/
void interpretNewData() {
	if (expectedType == 0)
		interpretCommand(&incomingByte); // If next expected data is a command byte
	else
		processReceivedInt(); // If the received data is expected to be an integer value.
}

/**
* Interpret a received command byte
*/
void interpretCommand(byte * command) {
	switch (*command) {
		case 33:
			// Expect next received transmission is an integer value containing the new temporary threshold.
			expectedType = 33;
			break;
		case 34:
			sendTempNoiseThreshold();
			break;
		case 35:
			sendSavedNoiseThreshold();
			break;
		case 36:
			saveNoiseThreshold();
			break;
		case 37:
			monitorMode();
			break;
		case 38:
			streamMode();
			break;
	}
}

void processReceivedInt() {
	switch (expectedType) {
		case 33:
			// Set current runtime's noise threshold
			noiseThreshold = incomingInt;
			break;
	}
}
	
/**
* Sends the current runtime's noise threshold to the station.
*/
void sendTempNoiseThreshold() {
	outgoingInt = noiseThreshold;
	sendInt();
}

/**
* Retrieve and send the saved noise threshold in the EEPROM.
*/
void sendSavedNoiseThreshold() {
	EEPROM.get(0,outgoingInt);
	sendInt();
}

/**
* Sets the buoy to monitor mode - this is the default monitoring mode.
*/
void monitorMode() {
	if (mode != 0) {

	}
}

/**
* Sets the buoy to stream mode - this will continously stream data to the station.
*/
void streamMode() {}
