/**
* Waits for station to set required parameters for operation.
*
* @return is true if all paramters have been received. False if not.
*/
bool waitForInitialization() {
	// List of expected headers. Make sure the station sends them in this order.
	byte headers[4] = { SET_VARIANCETHRESHOLD, SET_MEASUREMENTINTERVAL, SET_PINGTIMEOUT, SET_MODE };

	// Iterate through each header.
	for ( byte i = 0; i < 4; i++ ) {
		if (waitForHeader(headers[i], 1000))
			interpret(&incoming);
		else
			return false;
	}
	return true;
}

/**
* Waits for a packet with a specified header to be received.
*
* @param timeout is the time in ms to wait before timing out.
* @return is true if the data matches and received within the allowed time.
*/
bool waitForHeader(byte header, unsigned long timeout) {
	unsigned long timeStart = millis();
	do {
		if (!radio.isDataAvailable()) continue;
		radio.storeReceivedDataIn(&incoming);
		if (incoming.getHeader() == header)
			return true;
		else {
			outgoing.setHeader(ILLEGAL_HEADER);
			outgoing.setContent(0);
			radio.transmit(&outgoing);
			return false;
		}
	} while ( (millis() - timeStart) < timeout );
	return false; // When timed out
}

/**
* Checks if all operational variables have valid values.
*
* @return true if all operational variables have valid values.
*/
bool isSetupComplete() {
	if (!settings.measurementInterval)
		return false;
	if (!settings.varianceThreshold)
		return false;
	if (!settings.pingTimeout)
		return false;
	if (!settings.mode)
		return false;
	return true;
}
