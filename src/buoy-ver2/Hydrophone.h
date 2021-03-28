#ifndef H_HYDROPHONE
#define H_HYDROPHONE

#include "Arduino.h"

class Hydrophone {
	private:
		byte pin;
		byte samples;
	
	public:
		Hydrophone(int pin, int samples);
		long measure();
};

#endif
