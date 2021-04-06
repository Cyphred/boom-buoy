/**
* Methods and variables concerning the interpretation of commands received from the station.
*/

/**
* Interprets packet data by its header and executes the appropriate command.
*
* @param packet is a pointer to the packet whose data is to be interpreted.
*/
void interpret(Packet * packet) {
	switch (packet->getHeader()) {
		case QUERY_PING:
			lastPing = millis();
			send(RESP_PING_OK);
			break;

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
