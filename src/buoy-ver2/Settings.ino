/**
* For dealing with the getting and setting of operational settings/parameters.
*/

/**
* Handles connection requests.
*/
void connect() {
	// If the buoy receives a connection request while in a
	// non-disconnected state, tell the station that it
	// has sent an illegal connection request. At this point,
	// the station must wait for an existing connection to
	// terminate, whether terminated by the actively controlling
	// station, or by timing out from the existing connection.
	if (settings.mode != MODE_DISCONNECTED) {
		send(ILLEGAL_CONNECT);
	}

	// Tells the station the connection is approved.
	// This will make the station send the initialization variables.
	send(RESP_CONNECT_OK); 
}

/**
* Sets the device to a disconnected state.
*/
void disconnect() {
	resetSettings();
	buzzer.disconnected();
}

/**
* Sets the operation mode for the device
*
* @param code is the integer corresponding to the mode to be set.
*/
void setMode(int code) {
	switch (code) {
		case MODE_DISCONNECTED:
		case MODE_STREAM:
		case MODE_MONITOR:
			settings.mode = code;
			break;
		default:
			send(ILLEGAL_CONTENT, SET_MODE);
			break;
	}
}

/**
* Sets the threshold for level variance between two noise level readings.
*
* @param threshold is the percentage that is the maximum tolerated variance.
*/
void setVarianceThreshold(int threshold) {
	settings.varianceThreshold = threshold;
}

/**
* Sets the interval between each reading of noise level.
*
* @param interval is the time in ms between each reading of noise level.
*/
void setMeasurementInterval(unsigned int interval) {
	settings.measurementInterval = interval;
}

/**
* Sets the expected time for each probing ping.
* This will be used for regularly checking if the station is still responding.
*
* @param timeout is the maximum time in ms to wait for a probing ping from the station.
*/
void setPingTimeout(unsigned int timeout) {
	settings.pingTimeout = timeout;
}

/**
* Resets all operational variables.
*/
void resetSettings() {
	settings.measurementInterval = 0;
	settings.varianceThreshold = 0;
	settings.pingTimeout = 0;
	settings.mode = MODE_DISCONNECTED;
	lastPing = 0;
}
