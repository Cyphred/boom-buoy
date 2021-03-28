#include "Buzzer.h"

#define LONG_BEEP 1500
#define SHORT_BEEP 500

Buzzer::Buzzer(int pin) {
	this->pin = pin;
}

/**
* 3 long beeps with 2 seconds in between.
* This means the transceiver is undetectable by the Arduino.
* This error requires manual inspection/diagnosis.
*/
void Buzzer::radioError() {
	tone(pin, 1000, LONG_BEEP);
	delay(LONG_BEEP + 200);
	tone(pin, 1000, LONG_BEEP);
	delay(LONG_BEEP + 200);
	tone(pin, 1000, LONG_BEEP);
	delay(LONG_BEEP + 2000);
}

/**
* 1 long beep upon successfully connecting to the station and initializing all variables.
*/
void Buzzer::initializationSuccess() {
	tone(pin, 1000, LONG_BEEP);
}
