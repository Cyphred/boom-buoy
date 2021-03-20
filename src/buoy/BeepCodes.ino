int longBeepDuration = 1500;

/**
* 3 long beeps for problems with the transceiver.
*/
void radioErrorBeep() {
	do {
		tone(BUZZER, 1000, longBeepDuration);
		delay(longBeepDuration + 200);
		tone(BUZZER, 1000, longBeepDuration);
		delay(longBeepDuration + 200);
		tone(BUZZER, 1000, longBeepDuration);
		delay(longBeepDuration + 2000);
	} while (true);
}

/**
* 1 long beep upon successfully connecting to the station.
*/
void connectedBeep() {
	tone(BUZZER, 1000, longBeepDuration);
}
