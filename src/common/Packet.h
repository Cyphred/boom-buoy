#ifndef H_PACKET
#define H_PACKET

#include "Arduino.h"

class Packet {
	public:
		/**
		 * Packet data is 2 bytes in size.
		 * - The 2 bytes are for an unsigned integer which corresponds
		 *   to the `content` of the packet. This is used for transmitting
		 *   integer values associated with certain commands
		 *   (e.g. setting the noise threshold to a new value).
		 */
		byte data[2];
		unsigned int getContent();
		void setContent(unsigned int num);
		void reset();
		bool isEmpty();
};

#endif
