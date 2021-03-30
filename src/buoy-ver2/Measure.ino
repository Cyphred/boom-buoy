/**
* Methods and variables concerning the measurement/monitoring of sound levels.
*/

Hydrophone hydrophone(A0, 32);	// Initialize on A0 with 32 samples per reading.
unsigned long lastMeasureTime;
int lastLevel;

/**
* Routine for monitor mode.
*/
void measure() {
	lastMeasureTime = millis(); // Remember current time
	int currentLevel = hydrophone.measure();
	int variance = getVariance(lastLevel, currentLevel);
	if ( variance >= settings.varianceThreshold )
		warnStation();
}

/**
* Determines if it is time to measure the current sound level.
*
* @return is true if it is time to measure the current sound level. False if not.
*/
bool isTimeToMeasure() {
	if ((millis() - lastMeasureTime) >= settings.measurementInterval)
		return true;
	return false;
}

/**
* Gets the percentage of variance between two noise levels.
*
* @param oldValue is the previous noise level reading.
* @param newValue is the new noise level reading.
* @return is the percentage of variance between the two readings.
*/
int getVariance(int oldValue, int newValue) {
	return ((float) (newValue - newValue) / (float) newValue) * 100;
}
