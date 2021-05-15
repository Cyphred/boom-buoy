#include "Radio.h"

/**
 * Constructs a Radio object.
 *
 * @param ce is the pin where CE from the tranceiver is connected.
 * @param csn is the pin where CSN from the tranceiver is connected.
 * @param rxAddress is the array of bytes containing the receive address for incoming data.
 * @param txAddress is the array of bytes containing the transmit address for outgoing data.
 */
Radio::Radio(int ce, int csn, byte * rx, byte * tx) {
	RF24 m_radio(ce, csn);
	// Addresses should always be 5 bytes in length.
	for (byte i = 0; i < 5 ; i++ ) {
		rxAddress[i] = rx[i];
		txAddress[i] = tx[i];
	}

	m_radio.begin();
	if ( m_radio.isChipConnected() ) {
		m_radio.setDataRate( RF24_250KBPS );
		m_radio.openWritingPipe( txAddress );
		m_radio.openReadingPipe( 1, rxAddress );
		m_radio.setRetries( DELAY, MAX_RETRIES );
		m_radio.startListening();
		initialized = true;
		Serial.println("Radio initialized");
	}
	else {
		initialized = false;
		Serial.println("Radio NOT initialized");
	}
}

/**
* Fetches the data from the receive buffer of the transceiver and stores it.
*
* @param *packet is the pointer to the packet where the received data will be written to.
*/
void Radio::storeReceivedDataIn(Packet * packet) {
	m_radio.read( &packet->data, sizeof( packet->data ) ); // Read data from rf buffer and store it into packet's array.
}

/**
 * Transmits data to the TX address.
 *
 * @param *packet is the pointer to the packet where the received data will be written to.
 * @return true if an acknowledgement has been received.
 */
bool Radio::transmit(Packet * packet) {
	m_radio.stopListening();
	bool acknowledged = m_radio.write( &packet->data, sizeof( packet->data ) );
	m_radio.startListening();
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
bool Radio::isDataAvailable() {
	return m_radio.available();
}
