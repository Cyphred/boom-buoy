#include "Hydrophone.h"

/**
 * Creates an instance of the hydrophone.
 * Must be called in the setup() function.
 *
 * @param pin is the analog pin on the arduino where the hydrophone is connected.
 */
Hydrophone::Hydrophone(int pin) {
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

/**
 * Checks if all hydrophone variables have been initialized.
 *
 * @return is true if all necessary variables have valid values. Returns false if not.
 */
bool Hydrophone::isReady() {
	if ( ! noiseThreshold )
		return false;
	if ( ! measurementInterval )
		return false;
	return true;
}

void Hydrophone::setNoiseThreshold(unsigned int value) {
	noiseThreshold = value;
}

unsigned int Hydrophone::getNoiseThreshold() {
	return noiseThreshold;
}

void Hydrophone::setMeasurementInterval(unsigned int value) {
	measurementInterval = value;
}

unsigned int Hydrophone::getMeasurementInterval() {
	return measurementInterval;
}

/**
 * Measures the noise level being picked up by the hydrophone.
 *
 * @return the value of the measured noise level.
 */
long Hydrophone::measure() {
	long level;
	for ( byte i = 0 ; i < 32 ; i++ )
		level += analogRead( pin );
	level >>= 5; // Shift 5 bits to the right.
	return level;
}

/**
 * Determines if it is time to make another measurement based on the time of the
 * last measurement, and the measurement interval.
 *
 * @return is true if the gap between the current time and the last measurement
 * time is equal to or larger than the measurement interval.
 */
bool Hydrophone::isTimeToMeasure() {
	if ( ( millis() - lastMeasurement ) > measurementInterval )
		return true;
	return false;
}
