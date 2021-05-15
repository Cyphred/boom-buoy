#include "Packet.h"
#include "Arduino.h"

/**
* Gets the content from the packet data.
* This combines 2 bytes in the packet into an unsigned int.
*
* @return is the unsigned integer resulting from the combination of the
* 2 bytes in the content region of the packet.
*/
unsigned int Packet::getContent() {
	return (unsigned int) (data[1]<<8) | (data[0]);
}

/**
* Splits an unsigned integer into two bytes and stores them as the content in the packet data.
*
* @param num is the unsigned integer to be stored as the content in the packet data.
*/
void Packet::setContent(unsigned int num) {
	data[0] = (byte) (num & 0xFF);
	data[1] = (byte) ((num >> 8) & 0xFF);
}

/**
 * Resets all the bytes in the packet.
 */
void Packet::reset() {
	for (int x = 0; x < 2; x++ )
		data[x] = 0;
}

/**
 * Checks if there is data in the packet.
 *
 * @return is true if there is data in the packet. False if it is empty.
 */
bool Packet::isEmpty() {
	for (byte i = 0; i < 2; i++) {
		if (data[i] != 0)
			return false;
	}
	return true;
}
