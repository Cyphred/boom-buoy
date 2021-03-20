/**
* Fetches the data from the receive buffer of the transceiver ad stores it.
*/
void fetchIncomingPacket() {
	if ( radio.available() ) {
		radio.read( &incomingPacket, sizeof(incomingPacket) );
		newData = true;
	}
}

/**
* Sends the contents of outgoingPacket to the station.
*
* @return true if acknowledgement has been received.
*/
bool sendOutgoingPacket() {
	radio.stopListening();
	bool rslt;
	rslt = radio.write( &outgoingPacket, sizeof(outgoingPacket) );
	radio.startListening();
	if ( rslt )
		return true;
	return false;
}

/**
* Resets the values of incomingPacket.
*/
void resetIncomingPacket() {
	for (int i = 0; i < 3; i++)
		incomingPacket[i] = 0;
}

/**
* Resets the values of outgoingPacket.
*/
void resetOutgoingPacket() {
	for (int i = 0; i < 3; i++)
		outgoingPacket[i] = 0;
}

/**
* Splits an unsigned integer into two bytes and stores them in the outgoing packet.
* The 2 bytes of an unsigned integer are placed in addresses 1 and 2
*
* @param num is the unsigned integer to be loaded into the outbox
*/
void putUIntIntoOutgoingPacket(unsigned int num) {
	outbox[1] = (byte) (num & 0xFF);
	outbox[2] = (byte) ((num >> 8) & 0xFF);
}

/**
* Puts a byte into the outbox.
*
* @param data is the byte to be put into the command address in the outbox.
*/
void putByteIntoOutgoingPacket(byte data) {
	outbox[0] = data;
}

/**
* Gets the unsigned integer from the incoming packet.
* This combines the last 2 bytes in incomingPacket into an unsigned int.
* @return is the unsigned integer resulting from the combination of the last 2 bytes of incomingPacket.
*/
unsigned int getIncomingUInt() {
	return (unsigned int) (incomingPacket[2]<<8) | (incomingPacket[1]);
}

/**
* Gets the command byte from the incoming packet.
*/
byte getIncomingByte() {
	return incomingPacket[0];
}

/**
* Initializes the transceiver.
*
* @return is true if the transceiver is detected. Otherwise, false.
*/
bool initializeRadio() {
	radio.begin();
	if ( radio.isChipConnected() ) {
		radio.setDataRate( RF24_250KBPS );
		radio.openWritingPipe(stationAddr);
		radio.openReadingPipe(1, nodeAddr);
		radio.setRetries(3,5); // delay, count
		radio.startListening();
		return true;
	}
	return false;
}

/**
* Determines if the connection has timed out.
*/
bool isConnectionTimedOut() {
	if ( ( millis() - lastPing ) > pingInterval )
		return true;
	return false;
}

/**
 * Transmit a warning signal to the station.
 *
 * @param level is the address of the noise level value that exceeded the threshold.
 * @return true if the station has acknowledged the sent warning.
 */
bool warnStation(unsigned int * level) {
	putByteIntoOutbox(CMD_WARN);
	putUIntIntoOutbox(*level);
	sendOutgoingPacket();
	resetOutgoingPacket();
}

