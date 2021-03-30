#ifndef H_NOISEDATA
#define H_NOISEDATA

#include "Arduino.h"

class NoiseData {
	private:
		NoiseData * parent;	 // Parent instance to stash data to once current instance expires.
		unsigned long startTime; // Time when instantiated or reset.
		unsigned long lifetime;  // Expected lifetime before stashing data to another NoiseData instance.
	public:
		NoiseData();
		NoiseData(NoiseData * parent, unsigned long lifetime);
		long lastEntryTime;	// Time when last entry was added.
		int lastEntryValue;	// Value of last entry
		int entriesCount;	// Total number of entries added.
		unsigned long totalValues; // Total of all raw entry data.
		int average;		// Average of all entries' raw data.

		void addEntry(int entry);
		void reset();
		bool isEmpty();
		bool isExpired();
		void stashData();
};

#endif
