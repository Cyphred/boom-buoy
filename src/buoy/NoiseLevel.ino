/**
* Sets the noise threshold.
*/
void setNoiseThreshold(unsigned int value) {
	noiseThreshold = value;
}
/**
* Sets the noise measurement interval.
*/
void setMeasurementInterval(int value) {
	measurementInterval = value;
}

/**
 * Reads the analog noise level being picked up by the mic and saves its value.
 */
long measureNoiseLevel() {
	long level;
	// Take 32 samples
	for(int i=0; i<32; i++)
		level += analogRead(mic);
	level >>= 5; // Shift 5 bits to right
	return level;
}

/**
* Determines if it is time to do another noise level reading.
*/
bool isTimeToMeasureNoise() {
	// If difference of current time and the time of the last reading
	// reaches or exceeds the defined interval.
	if ((millis() - lastNoiseReading) >= noiseMeasurementInterval)
		return true;
	return false;
}
