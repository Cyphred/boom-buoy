#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

void setup() {
	pinMode(8, OUTPUT);
	radio.begin();
	radio.setDataRate( RF24_250KBPS );
	radio.setRetries(3,5); // delay, count
	radio.openWritingPipe(slaveAddress);

	if (radio.isChipConnected())
		tone(8, 2500, 500);
	else {
		while (true) {
			tone(8, 500, 1000);
			delay(1500);
		}
	}
	
	pinMode(A0, INPUT);
}

unsigned long lastReading;

void loop() {
	if (isTimeForReading()) {
		lastReading = millis();
		int level = measure();
		send(level);
	}
}

bool isTimeForReading() {
	if (millis() - lastReading >= 10)
		return true;
	return false;
}

void send(unsigned int data) {
	byte dataToSend[2];
	dataToSend[0] = (byte) (data & 0xFF);
	dataToSend[1] = (byte) ((data >> 8) & 0xFF);
	radio.write( &dataToSend, sizeof(dataToSend) );
	// Always use sizeof() as it gives the size as the number of bytes.
	// For example if dataToSend was an int sizeof() would correctly return 2
}

int measure() {
	long level = 0;
	for ( byte i = 0 ; i < 32 ; i++ )
		level += analogRead( A0 );
	level >>= 5; // Shift 5 bits to the right.

	return (int) level;
}
