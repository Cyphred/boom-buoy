/**
* Interprets packet data by its header and executes the appropriate command.
*
* @param packet is a pointer to the packet whose data is to be interpreted.
*/
void interpret(Packet * packet) {
	switch (packet->getHeader()) {
		case CONNECT:
			connect();
			break;
		case DISCONNECT:
			disconnect();
			break;
		case SET_VARIANCETHRESHOLD:
			setVarianceThreshold(packet->getContent());
			break;
		case SET_MEASUREMENTINTERVAL:
			setMeasurementInterval(packet->getContent());
			break;
		case SET_PINGTIMEOUT:
			setPingTimeout(packet->getContent());
			break;
		case SET_MODE:
			setMode(packet->getContent());
			break;
		case QUERY_VARIANCETHRESHOLD:
			send(RESP_VARIANCETHRESHOLD, settings.varianceThreshold);
			break;
		case QUERY_MEASUREMENTINTERVAL:
			send(RESP_MEASUREMENTINTERVAL, settings.measurementInterval);
			break;
		case QUERY_PINGTIMEOUT:
			send(RESP_PINGTIMEOUT, settings.pingTimeout);
			break;
		case QUERY_MODE:
			send(RESP_MODE, settings.mode);
			break;
		default:
			send(ILLEGAL_HEADER);
			break;
	}
}

void disconnect() {
	settings.mode = MODE_DISCONNECTED;
	buzzer.disconnected();
}

/**
* Warns the station of an illegal command and its details.
*
* @param warningID is the type of warning. See `Constants.ino` for a list of warning types.
* @param details is the details of the warning. This is the code of the offending command.
*/
void warn(int warningID, int details) {
	outgoing.setHeader(warningID);
	outgoing.setContent(details);
	radio.transmit(&outgoing);
}
