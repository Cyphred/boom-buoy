/**
* Loads the saved noise threshold from EEPROM.
*/
void loadNoiseThreshold() {
	EEPROM.get(0, noiseThreshold);
	if (!noiseThreshold)
		noiseThreshold = 300; // Default to 300 if there is no saved threshold
}

/**
* Gets the saved threshold in the EEPROM and compares it
* with the current runtime's threshold. If they are not the same,
* the current runtime's threshold is saved into EEPROM.
*/
void saveNoiseThreshold() {
	int savedThreshold;
	EEPROM.get(0,savedThreshold);
	if (savedThreshold != noiseThreshold)
		EEPROM.put(0,noiseThreshold);
}

/**
 * Reads the analog noise level being picked up by the mic and saves its value.
 */
void getNoiseLevel(long * level) {
	// Take 32 samples
	for(int i=0; i<32; i++)
		*level += analogRead(mic);
	*level >>= 5; // Shift 5 bits to right
}

