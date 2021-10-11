/**
* Methods and variables concerning the measurement/monitoring of sound levels.
*/

/**
* Measures the current sound level.
*/
void measure() {
	status.lastMeasureTime = millis();
	long sum = 0;
	for(int i=0; i<32; i++) {
		sum += analogRead(hydrophone);
	}
	sum >>= 5;
	status.lastLevel = sum;
}

/**
* Determines if it is time to measure the current sound level.
*
* @return is true if it is time to measure the current sound level. False if not.
*/
bool isTimeToMeasure() {
	if ((millis() - status.lastMeasureTime) >= settings.measurementInterval)
		return true;
	return false;
}
