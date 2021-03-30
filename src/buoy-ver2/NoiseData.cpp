#include "NoiseData.h"

NoiseData::NoiseData() {
	;
}

NoiseData::NoiseData(NoiseData * parent, unsigned long lifetime) {
		this->parent = parent;
		this->lifetime = lifetime;
		startTime = millis(); // Store time of instantiation.
}

void NoiseData::addEntry(int entry) {
	lastEntryTime = millis(); // Record the time current entry is added.
	totalValues += entry;	
	entriesCount++;
	average = totalValues / entriesCount; // Save the new average.
}

/**
 * Resets all data and counters.
 */
void NoiseData::reset() {
	lastEntryTime = entriesCount = totalValues = average = 0;
	startTime = millis();
}

/**
 * Determines if there are no entries yet.
 */
bool NoiseData::isEmpty() {
	if (!entriesCount)
		return true;
	return false;
}

/**
 * Determines if the data is expired.
 * This means the data needs to be stashed into a longer-term
 * data set.
 *
 * @return is true if the data has exceeded expected lifetime. False if the data is still valid.
 */
bool NoiseData::isExpired() {
	if ((millis() - startTime) >= lifetime)
		return true;
	return false;
}

/**
 * Stashes the `average` data into a parent `NoiseData` instance.
 */
void NoiseData::stashData() {
	parent->addEntry(average);
	reset();
}
