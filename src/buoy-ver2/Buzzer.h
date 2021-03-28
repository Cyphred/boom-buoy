#ifndef H_BUZZER
#define H_BUZZER

#include "Arduino.h"

class Buzzer {
	private:
		int pin;
	public:
		Buzzer(int pin);
};

#endif
