/**
* Initialize buoy variables after establishing a connection with the station.
* This is a blocking method that will not proceed until initialization is complete.
*/
void initialize() {
	while (settings.mode == MODE_DISCONNECTED) {
		waitForConnectionRequest();
		if (waitForInitialVariables(1000))
			buzzer.initSuccess(); // If all variables are received on time.
		else
			resetSettings(); // If one of the variables failed to arrive on time.
	}
	lastPing = millis();
}

/**
* Indefinitely waits for a connection request.
*/
void waitForConnectionRequest() {
	while (true) {
		if (!receive())
			continue;
		if (incoming.getHeader() == CONNECT)
			break;
	}
	// Tell station that the buoy is ready to receive the initial variables.
	send(RESP_CONNECT_OK); 
}

/**
* Waits for station to set required parameters for operation.
*
* @param timeout is the time to wait for each parameter to arrive.
* @return is true if all paramters have been received. False if not.
*/
bool waitForInitialVariables(unsigned long timeout) {
	// List of expected headers. Make sure the station sends them in this order.
	byte headers[4] = { SET_VARIANCETHRESHOLD, SET_MEASUREMENTINTERVAL, SET_PINGTIMEOUT, SET_MODE };

	// Iterate through each header.
	for ( byte i = 0; i < 4; i++ ) {
		if (_waitForHeader(headers[i], &timeout))
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
bool _waitForHeader(byte header, unsigned long * timeout) {
	unsigned long timeStart = millis();
	do {
		if (!receive()) 
			continue;

		if (incoming.getHeader() == header)
			return true;
		else {
			send(ILLEGAL_HEADER, header);
			return false;
		}
	} while ( (millis() - timeStart) < *timeout );

	// Tell station that the window for sending initial variables is up.
	send(TIMEOUT_INIT, header); 
	return false;
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
