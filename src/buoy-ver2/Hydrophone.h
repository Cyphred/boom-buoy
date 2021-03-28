#ifndef H_HYDROPHONE
#define H_HYDROPHONE

#include "Arduino.h"

class Hydrophone {
	private:
		byte pin;
		unsigned int noiseThreshold;
		unsigned int measurementInterval;
		long lastMeasurement;
	
	public:
		Hydrophone(int pin);
		bool isReady();
		void setNoiseThreshold(unsigned int value);
		unsigned int getNoiseThreshold();
		void setMeasurementInterval(unsigned int value);
		unsigned int getMeasurementInterval();
		long measure();
		bool isTimeToMeasure();
};

#endif
