#ifndef H_HYDROPHONE
#define H_HYDROPHONE

#include "Arduino.h"

class Hydrophone {
	private:
		byte pin;	// SIG pin of hydrophone
		byte samples;	// Number of samples to be averaged per reading.
	
	public:
		Hydrophone(int pin, int samples);
		int measure();
};

#endif
