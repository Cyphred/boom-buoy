#ifndef H_PACKET
#define H_PACKET

#include "Arduino.h"

class Packet {
	public:
		/**
		 * Packet data is 7 bytes in size.
		 * - The first byte is for the `header` which corresponds to
		 *   a specific byte, defined as constants. This will be used
		 *   to identify the `content` of the packet, by letting the
		 *   receiving device know what to do with the `content` part
		 *   of the packet data.
		 *
		 * - The next 2 bytes is for an unsigned integer which corresponds
		 *   to the `content` of the packet. This is used for transmitting
		 *   integer values associated with certain commands
		 *   (e.g. setting the noise threshold to a new value).
		 *
		 * - The last 4 bytes is for an unsigned long which will be used
		 *   for timestamps.
		 */
		byte data[7];
		byte getHeader();
		void setHeader(byte value);
		unsigned int getContent();
		void setContent(unsigned int num);
		unsigned long getTimestamp();
		void setTimestamp(unsigned long timeStamp);
		void reset();
		bool isEmpty();
};

#endif
