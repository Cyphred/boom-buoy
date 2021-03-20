// Connection Commands =======================================================================
/**
* Waits for connection and initialization data to be completed.
* If a single variable fails to arrive, entire process fails and needs to start over.
*/
void waitForInitialization() {
	do {
		waitForConnectionRequest();
		if (!waitForSetNoisethreshold(1000))
			continue; // if timed out
		if (!waitForSetMeasurementInterval(1000))
			continue; // if timed out
		if (!waitForSetPingInterval(1000))
			continue; // if timed out
		if (!waitForSetMode(1000))
			continue; // if timed out
		else
			initializationSuccessBeep();
			break; // if successfully set all variables.
	} while (true);
}

/**
* Indefinitely waits for a connection request from the station.
* This will warn the station of illegal commands sent in.
*/
void waitForConnectionRequest() {
	do {
		fetchIncomingPacket();
		if ( newData ) {
			byte command = getIncomingByte();
			if ( command == CMD_CONNECT ) {
				resetIncomingPacket();
				newData = false;
				break;
			}
			else {
				resetIncomingPacket();
				warnStationCommandIsIllegal();
			}
		}
	} while (true);
}

/**
* Gives an audible disconnect warning and resets variables.
*/
void disconnect() {
	disconnectWarning();
	resetVariables();
}

// Wait For Commands ========================================================================
// Mostly used for initialization by waiting for the station to send specific command-value
// pairs for essential operational variables.

/**
* Waits for a command-value pair to arrive within a specified time.
* This will warn the station of illegal commands sent in.
*
* @param command is the expected command to receive.
* @param variable is where the unsigned integer in the packet will be stored.
* @param timeout is the time in ms to wait for the command.
* @return is true if the command has been received within the specified time. Otherwise, false.
*/
bool waitForCommandValuePair(byte expected_command, unsigned int * variable, long timeout) {
	long initiated = millis(); // Keep track of the time this method was called.
	do {
		fetchIncomingPacket();
		if ( newData ) {
			byte command = getIncomingByte();
			if ( command == expected_command ) {
				*variable = getIncomingUInt();
				resetIncomingPacket();
				newData = false;
				return true;
			}
			else {
				resetIncomingPacket();
				warnStationCommandIsIllegal();
				return false;
			}
		}
	} while ((millis() - initiated) < timeout);
	return false;
}

/**
* Waits for the noise threshold to be set by the station within a specified time.
*
* @param timeout is the time to wait for the command.
* @return is true if the command has been received within the specified time.
*/
bool waitForSetNoisethreshold(long timeout) {
	return waitForCommandValuePair(CMD_SETNOISETHRESHOLD, &noiseThreshold, timeout);
}

/**
* Waits for the noise measurement interval to be set by the station within a specified time.
*
* @param timeout is the time to wait for the command.
* @return is true if the command has been received within the specified time.
*/
bool waitForSetMeasurementInterval(long timeout)  {
	return waitForCommandValuePair(CMD_SETMEASUREMENTINTERVAL, &measurementInterval, timeout);
}

/**
* Waits for the ping interval to be set by the station within a specified time.
*
* @param timeout is the time to wait for the command.
* @return is true if the command has been received within the specified time.
*/
bool waitForSetPingInterval(long timeout) {
	return waitForCommandValuePair(CMD_SETPINGINTERVAL, &pingInterval, timeout);
}

/**
* Waits for the mode to be set by the station within a specified time.
*
* @param timeout is the time to wait for the command.
* @return is true if the command has been received within the specified time.
*/
bool waitForSetMode()(long timeout) {
	return waitForCommandValuePair(CMD_SETMODE, &mode, timeout);
}

// Send Commands =============================================================================
/**
* Sends the current noise threshold to the device.
*/
void sendNoiseThreshold() {
	putByteIntoOutgoingPacket(CMD_SENDNOISETHRESHOLD);
	putUIntIntoOutgoingPacket(noiseThreshold);
	sendOutgoingPacket();
}

/**
* Sends the current noise measurement interval to the device.
*/
void sendMeasurementInterval()
	putByteIntoOutgoingPacket(CMD_SENDMEASUREMENTINTERVAL);
	putUIntIntoOutgoingPacket(measurementInterval);
	sendOutgoingPacket();
}

/**
* Sends the current noise measurement interval to the device.
*/
void sendPingInterval() {
	putByteIntoOutgoingPacket(CMD_SENDPINGINTERVAL);
	putUIntIntoOutgoingPacket(pingInterval);
	sendOutgoingPacket();
}

/**
* Sends the current noise measurement interval to the device.
*/
void sendMaxNoiseLevel() {
	putByteIntoOutgoingPacket(CMD_SENDMAXNOISELEVEL);
	putUIntIntoOutgoingPacket(maxNoiseLevel);
	sendOutgoingPacket();
}

/**
* Sends the current noise measurement interval to the device.
*/
void sendMode () {
	putByteIntoOutgoingPacket(CMD_SENDMODE);
	putUIntIntoOutgoingPacket(mode);
	sendOutgoingPacket();
}


// Set Commands =============================================================================
/**
* Resets variables to starting state.
* This will mainly be used when disconnecting.
*/
void resetVariables() {
	setNoiseThreshold(0);
	setMeasurementInterval(0);
	setPingInterval(0);
	setMode(MODE_MONITOR);

	resetIncomingPacket();
	resetOutgoingPacket();
	maxNoiseLevel = 0;
	lastPing = 0;
	lastNoiseReading = 0;
	newData = false;
}

/**
* Sets the interval between each ping before timing out and going into a disconnected state.
* A ping is the station and the buoy's way of telling that they are still connected. 
*
* @param duration is the time to wait for each ping.
*/
void setPingInterval(long duration) {
	pingInterval = duration;
}

/**
* Sends a warning to the station that the last command sent is valid, but currently illegal.
*/
void warnStationCommandIsIllegal() {
	resetOutgoingPacket();
	putByteIntoOutgoingPacket(WARN_ILLEGALCOMMAND);
	sendOutgoingPacket();
}
