#include "Hydrophone.h"

/**
 * Creates an instance of the hydrophone.
 * Must be called in the setup() function.
 *
 * @param pin is the analog pin on the arduino where the hydrophone is connected.
 * @param samples is the number of samples to average per reading.
 */
Hydrophone::Hydrophone(int pin, int samples) {
	this->pin = pin;
	this->samples = samples;
	pinMode(pin, OUTPUT);
}

/**
 * Measures the noise level being picked up by the hydrophone.
 *
 * @return the value of the measured noise level.
 */
long Hydrophone::measure() {
	long level;
	for ( byte i = 0 ; i < samples ; i++ )
		level += analogRead( pin );
	level >>= 5; // Shift 5 bits to the right.

	return level;
}
