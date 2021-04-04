/**
* Constats for defining command codes in bytes.
* I put this in a higher directory than the sketch folders of the buoy and the station
* so that you can simply put a symlink in each of the sketch folders referencing this file.
* This way, any updates to the constants' values will be synchronized across both sketches.
*
* IMPORTANT NOTE:
* Remember to re-compile and upload sketches for BOTH devices when you update these values.
*/

// Command Codes from Station to Node
#define CMD_CONNECT 1			// Connection request
#define CMD_DISCONNECT 2		// Disconnection request
#define CMD_SETNOISETHRESHOLD 3		// Set the noise threshold
#define CMD_SENDNOISETHRESHOLD 4	// Query noise threshold
#define CMD_SETMEASUREMENTINTERVAL 5	// Set the measurement interval
#define CMD_SENDMEASUREMENTINTERVAL 6	// Query measurement interval
#define CMD_SETPINGINTERVAL 7		// Set ping interval
#define CMD_SENDPINGINTERVAL 8		// Send the timeout for communication to the station.
#define CMD_SENDMAXNOISELEVEL 9		// Send the maximum noise level to the station.
#define CMD_SETMODE 10			// Set the current mode.
#define CMD_SENDMODE 11			// Send the current mode to the station.

// Warning Codes
#define WARN_CONNECT_REFUSE 100		// Warn
#define WARN_EXCEEDEDTHRESHOLD 100	// Warn station that threshold has been exceeded.
#define WARN_ILLEGALCOMMAND 101		// Warn station that it is trying to send an illegal command.
