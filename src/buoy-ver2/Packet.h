#ifndef H_PACKET
#define H_PACKET

#include "Arduino.h"

class Packet {
	public:
		/**
		 * Packets are 3 bytes in size.
		 * The first byte is for the "command byte" which corresponds to
		 * a specific command. The last 2 bytes are for unsigned integer
		 * values that are relevant to the command byte, particularly for
		 * sending data back to the station.
		 */
		byte data[3];
		byte getByte();
		void storeByte(byte value);
		unsigned int getUnsignedInt();
		void storeUnsignedInt(unsigned int num);
		void reset();
};

#endif

