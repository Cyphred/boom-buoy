#include "Radio.h"

/**
 * Constructs a Radio object.
 *
 * @param ce is the pin where CE from the tranceiver is connected.
 * @param csn is the pin where CSN from the tranceiver is connected.
 * @param rxAddress is the array of bytes containing the receive address for incoming data.
 * @param txAddress is the array of bytes containing the transmit address for outgoing data.
 */
Radio::Radio(byte ce, byte csn, byte * rx, byte * tx) : rf(ce, csn) {
	// Addresses should always be 5 bytes in length.
	for (byte i = 0; i < 5 ; i++ ) {
		rxAddress[i] = rx[i];
		txAddress[i] = tx[i];
	}

	rf.begin();
	if ( rf.isChipConnected() ) {
		rf.setDataRate( RF24_250KBPS );
		rf.openWritingPipe( txAddress );
		rf.openReadingPipe( 1, rxAddress );
		rf.setRetries( DELAY, MAX_RETRIES );
		rf.startListening();
		initialized = true;
	}
	else {
		initialized = false;
	}
}

/**
* Fetches the data from the receive buffer of the transceiver and stores it.
*
* @param *packet is the pointer to the packet where the received data will be written to.
*/
void Radio::receive(Packet * packet) {
	rf.read( &packet->data, sizeof( packet->data ) ); // Read data from rf buffer and store it into packet's array.
}

/**
 * Transmits data to the TX address.
 *
 * @param *packet is the pointer to the packet where the received data will be written to.
 * @return true if an acknowledgement has been received.
 */
bool Radio::transmit(Packet * packet) {
	rf.stopListening();
	bool acknowledged = rf.write( &packet->data, sizeof( packet->data ) );
	rf.startListening();
	if ( acknowledged );
		return true;
	return false;
}

/**
 * Tests if the transceiver has been properly initialized.
 *
 * @return is true if the transceiver is properly initialized.
 */
bool Radio::isInitialized() {
	return initialized;
}

/**
 * Checks if there is available data in the transceiver's receive buffer.
 *
 * @return is true if there is data in the receive buffer.
 */
bool Radio::available() {
	return rf.available();
}
