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
			break;
		case (byte) CON_GET_MEASUREMENTINTERVAL:
			break;
		case (byte) CON_GET_PINGTIMEOUT:
			consolePingTimeoutQuery();
			break;
		case (byte) CON_GET_MODE:
			consoleModeQuery();
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

void consolePingTimeoutQuery() {
	Serial.print(settings.pingTimeout);
}

/**
* Query for state of connection.
*/
void consoleModeQuery() {
	Serial.print(settings.mode);
}
