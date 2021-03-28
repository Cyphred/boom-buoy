#include "Packet.h"
#include "Arduino.h"

/**
 * Gets the byte portion of the packet.
 *
 * @return the byte portion of the packet.
 */
byte Packet::getByte() {
	return data[0];
}

/**
* Puts a byte into the outbox.
*
* @param data is the byte to be put into the command address in the outbox.
*/
void Packet::storeByte(byte value) {
	data[0] = value;
}

/**
* Gets the unsigned integer from the packet.
* This combines the last 2 bytes in the packet into an unsigned int.
*
* @return is the unsigned integer resulting from the combination of the
* last 2 bytes of incomingPacket.
*/
unsigned int Packet::getUnsignedInt() {
	return (unsigned int) (data[2]<<8) | (data[1]);
}

/**
* Splits an unsigned integer into two bytes and stores them in the packet.
*
* @param num is the unsigned integer to be stored in the packet.
*/
void Packet::storeUnsignedInt(unsigned int num) {
	data[1] = (byte) (num & 0xFF);
	data[2] = (byte) ((num >> 8) & 0xFF);
}

/**
 * Resets all the bytes in the packet.
 */
void Packet::reset() {
	for (byte i = 0; i < 3; i++)
		data[i] = 0;
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
