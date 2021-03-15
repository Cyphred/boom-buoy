/**
* 3 long beeps for problems with the transceiver.
*/
void radioErrorBeep() {
	do {
		tone(buzzer, 1000, 1000);
		delay(1200);
		tone(buzzer, 1000, 1000);
		delay(1200);
		tone(buzzer, 1000, 1000);
		delay(3000);
	} while (true);
}

/**
* 1 long beep upon successfully connecting to the station.
*/
void connectedBeep() {
	tone(buzzer, 1000, 1000);
}
