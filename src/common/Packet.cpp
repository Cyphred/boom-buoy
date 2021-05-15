#include "Packet.h"
#include "Arduino.h"

/**
 * Gets the header portion of the packet data.
 *
 * @return the header portion of the packet data.
 */
byte Packet::getHeader() {
	return data[0];
}

/**
* Sets a byte as the header of the packet data.
*
* @param data is the byte to be stored as the header of the packet data.
*/
void Packet::setHeader(byte value) {
	data[0] = value;
}

/**
* Gets the content from the packet data.
* This combines 2 bytes in the packet into an unsigned int.
*
* @return is the unsigned integer resulting from the combination of the
* 2 bytes in the content region of the packet.
*/
unsigned int Packet::getContent() {
	return (unsigned int) (data[2]<<8) | (data[1]);
}

/**
* Splits an unsigned integer into two bytes and stores them as the content in the packet data.
*
* @param num is the unsigned integer to be stored as the content in the packet data.
*/
void Packet::setContent(unsigned int num) {
	data[1] = (byte) (num & 0xFF);
	data[2] = (byte) ((num >> 8) & 0xFF);
}

/**
 * Gets the timestamp from the packet data.
 * This combines 4 bytes in the packet into an unsigned long.
 *
 * @return is the unsigned long resulting from the combination of the
 * 4 bytes in the timestamp region of the packet.
 */
unsigned long Packet::getTimestamp() {
	return (unsigned int) (data[6]<<24) | (data[5]<<16) | (data[4]<<8) | (data[3]);
}

/**
* Splits an unsigned long into four bytes and stores them in the
* timestamp region of the packet data.
*
* @param num is the unsigned long to be stored as the timestamp.
*/
void Packet::setTimestamp(unsigned long timeStamp) {
	data[3] = (byte) (timeStamp & 0xFF);
	data[4] = (byte) ((timeStamp >> 8) & 0xFF);
	data[5] = (byte) ((timeStamp >> 16) & 0xFF);
	data[6] = (byte) ((timeStamp >> 24) & 0xFF);
}

/**
 * Resets all the bytes in the packet.
 */
void Packet::reset() {
	for (int x = 0; x < 7; x++ )
		data[x] = 0;
}

/**
 * Checks if there is data in the packet.
 *
 * @return is true if there is data in the packet. False if it is empty.
 */
bool Packet::isEmpty() {
	for (byte i = 0; i < 3; i++) {
		if (data[i] != 0)
			return false;
	}
	return true;
}
