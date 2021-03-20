int longBeepDuration = 1500;

/**
* 3 long beeps with 2 seconds in between.
* This means the transceiver is undetectable by the Arduino.
* This error requires manual inspection/diagnosis.
*/
void radioInitErrorLoop() {
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
* 1 long beep upon successfully connecting to the station and initializing all variables.
*/
void initializationSuccessBeep() {
	tone(BUZZER, 1000, longBeepDuration);
}
