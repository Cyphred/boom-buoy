#include "Radio.h"

#define CE_PIN   9
#define CSN_PIN 10

RF24 rf( CE_PIN, CSN_PIN );
const byte rxAddress[5] = { 'R','x','A','A','A' };	// Receive from this address
const byte txAddress[5] = { 'T','x','a','a','a' };	// Transmit to this address

/**
 * Initializes the transceiver.
 *
 * @return is true if the transceiver has been properly initialized.
 */
bool Radio::initializeRadio() {
	rf.begin();
	if ( rf.isChipConnected() ) {
		rf.setDataRate( RF24_250KBPS );
		rf.openWritingPipe( txAddress );
		rf.openReadingPipe( 1, rxAddress );
		rf.setRetries( 3, 5 ); // delay between each retry, number of retries
		rf.startListening();
		return true;
	}
	return false;
}

/**
* Fetches the data from the receive buffer of the transceiver and stores it.
*
* @param packet is the pointer to the packet where the received data will be written to.
* @return is true if data has been fetched and stored into a packet. False data is unavailable.
*/
bool Radio::receive(Packet * packet) {
	if ( rf.available() ) {
		rf.read( &packet->data, sizeof( packet->data ) ); // Read data from rf buffer and store it into packet's array.
		return true;
	}
	return false;
}

/**
 * Transmits data to the TX address.
 *
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
