#ifndef H_PACKET
#define H_PACKET

#include "Arduino.h"

class Packet {
	public:
		/**
		 * Packet data is 3 bytes in size.
		 * - The first byte is for the `header` which corresponds to
		 *   a specific byte, defined as constants. This will be used
		 *   to identify the `content` of the packet, by letting the
		 *   receiving device know what to do with the `content` part
		 *   of the packet data.
		 *
		 * - The last 2 bytes is for an unsigned integer which corresponds
		 *   to the `content` of the packet. This is used for transmitting
		 *   integer values associated with certain commands
		 *   (e.g. setting the noise threshold to a new value).
		 */
		byte data[3];
		byte getHeader();
		void storeHeader(byte value);
		unsigned int getUnsignedInt();
		void storeUnsignedInt(unsigned int num);
		void reset();
		bool isEmpty();
};

#endif
