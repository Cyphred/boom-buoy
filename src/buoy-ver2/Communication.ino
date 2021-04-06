/**
* Methods and variables for handling communication between buoy and station.
*/

/**
* Generic command for sending data ot the station.
*
* @param header is the header byte.
* @param content is the unsigned integer content.
*/
void send(byte header, unsigned int content) {
	outgoing.setHeader(header);
	outgoing.setContent(content);
	radio.transmit(&outgoing);
}

/**
* Generic command for sending data ot the station.
*
* @param header is the header byte.
*/
void send(byte header) {
	outgoing.setHeader(header);
	outgoing.setContent(0);
	radio.transmit(&outgoing);
}
