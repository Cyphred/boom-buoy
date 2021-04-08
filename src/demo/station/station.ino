#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

unsigned int received;
bool newData = false;

void setup() {
	Serial.begin(9600);
	pinMode(8, OUTPUT);

	radio.begin();
	radio.setDataRate( RF24_250KBPS );
	radio.openReadingPipe(1, thisSlaveAddress);
	radio.startListening();

	if (radio.isChipConnected())
		tone(8, 2500, 1000);
	else {
		while (true) {
			tone(8, 500, 1000);
			delay(1500);
		}
	}
}

void loop() {
	if (getDataFromTransceiver()) {
		int level = getReceived();
		if (level > 300)
			Serial.println(level);
	}
}

bool getDataFromTransceiver() {
	if ( radio.available() ) {
		char data[2];
		radio.read( &data, sizeof(data) );
		newData = true;
		received = (unsigned int) (data[1]<<8) | (data[0]);
		return true;
	}
	return false;
}

unsigned int getReceived() {
	if (newData == true) {
		newData = false;
		return received;
	}
}

