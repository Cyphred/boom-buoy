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
		case (byte) CON_SET_MEASUREMENTINTERVAL:
			consoleSetMeasurementInterval();
			break;
		case (byte) CON_SET_PINGTIMEOUT:
			consoleSetPingTimeout();
			break;
		case (byte) CON_GET_MEASUREMENTINTERVAL:
			consoleGetMeasurementInterval();
			break;
		case (byte) CON_GET_PINGTIMEOUT:
			consoleGetPingTimeout();
			break;
	}
}

/**
* Waits for a stream of characters and builds it into an integer.
*
* @param is the variable where the built integer is stored.
* @return is true if the stream has successfully built an integer.
*/
bool waitForIntegerStream(unsigned int * target, unsigned long timeout) {
	String stream = "";
	bool timedOut = true;
	unsigned long start = millis();
	do {
		char data = Serial.read();
		if (data == 2) {
			timedOut = false;
			break;
		}
		else if (data >= 48 && data <= 57) {
			stream += data;
		}
	} while ((millis() - start) < timeout);
	
	if (timedOut)
		return false;

	*target = stream.toInt();
	return true;
}

/**
* Handles communication algorithm with console for receiving integer values.
*
* @return is the integer received from the console.
*/
unsigned int receiveNewValue() {
	Serial.write(CON_ACCEPT);
	unsigned int result;
	if (waitForIntegerStream(&result, 1000))
		Serial.write(CON_ACCEPT);
	else
		Serial.write(CON_REJECT);
	
	return result;
}

/**
* Handles request for connection by a console application.
*/
void consoleConnect() {
	if (status.isConnectedToConsole) {
		buzzer.genericError();
		Serial.write(CON_REJECT);
	}
	else {
		status.isConnectedToConsole = true;
		Serial.write(CON_ACCEPT);
		buzzer.genericOK();
	}
}

/**
* Set the measurement interval setting using a value sent by the console.
*/
void consoleSetMeasurementInterval() {
	unsigned int newValue = receiveNewValue();
	if (newValue)
		settings.measurementInterval = newValue;
}

/**
* Set the ping timeout setting using a value sent by the console.
*/
void consoleSetPingTimeout() {
	unsigned int newValue = receiveNewValue();
	if (newValue)
		settings.pingTimeout = newValue;
}

/**
* Prints the current measurement interval setting.
*/
void consoleGetMeasurementInterval() {
	Serial.print(settings.measurementInterval);
}

/**
* Prints the current ping timeout setting.
*/
void consoleGetPingTimeout() {
	Serial.print(settings.pingTimeout);
}

/**
* Prints a data point's contents to serial.
* This is for the console to be able to receive and log data points coming in from the buoy.
*
* @param packet is the packet whose contents will be dumped as a data point.
*/
void sendDataPointToConsole(Packet * packet) {
	Serial.print(packet->getTimestamp());
	Serial.print(",");
	Serial.println(packet->getContent());
}
