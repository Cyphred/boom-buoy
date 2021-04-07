/**
* Methods and variables for interfacing with the console application.
*/
void interpretConsoleCommand(byte command) {
	switch (command) {
		case (byte) CON_CONNECT:
			consoleConnect();
			break;
		case (byte) CON_DISCONNECT:
			break;
		case (byte) CON_SET_VARIANCETHRESHOLD:
			break;
		case (byte) CON_SET_MEASUREMENTINTERVAL:
			break;
		case (byte) CON_SET_PINGTIMEOUT:
			break;
		case (byte) CON_SET_MODE:
			break;
		case (byte) CON_GET_VARIANCETHRESHOLD:
			consoleGetVariancethreshold();
			break;
		case (byte) CON_GET_MEASUREMENTINTERVAL:
			consoleGetMeasurementInterval();
			break;
		case (byte) CON_GET_PINGTIMEOUT:
			consoleGetPingTimeout();
			break;
		case (byte) CON_GET_MODE:
			consoleGetMode();
			break;
	}
}

/**
* Handles request for connection by a console application.
*/
void consoleConnect() {
	if (connectedToConsole) {
		buzzer.genericError();
		Serial.write(CON_REJECT);
	}
	else {
		connectedToConsole = true;
		Serial.write(CON_ACCEPT);
		buzzer.genericOK();
	}
}

void consoleGetVariancethreshold() {
	Serial.print(settings.varianceThreshold);
}

void consoleGetMeasurementInterval() {
	Serial.print(settings.measurementInterval);
}

void consoleGetPingTimeout() {
	Serial.print(settings.pingTimeout);
}

/**
* Query for state of connection.
*/
void consoleGetMode() {
	Serial.print(settings.mode);
}
