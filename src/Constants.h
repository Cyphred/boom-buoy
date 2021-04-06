/**
* Constats for defining command codes in bytes.
* I put this in a higher directory than the sketch folders of the buoy and the station
* so that you can simply put a symlink in each of the sketch folders referencing this file.
* This way, any updates to the constants' values will be synchronized across both sketches.
*
* IMPORTANT NOTE:
* Remember to re-compile and upload sketches for BOTH devices when you update these values.
*/

// Command Codes
#define CONNECT 1
#define DISCONNECT 2

#define SET_VARIANCETHRESHOLD 3
#define SET_MEASUREMENTINTERVAL 4
#define SET_PINGTIMEOUT 5
#define SET_MODE 6

#define QUERY_VARIANCETHRESHOLD 7
#define QUERY_MEASUREMENTINTERVAL 8
#define QUERY_PINGTIMEOUT 9
#define QUERY_MODE 10

#define RESP_VARIANCETHRESHOLD 11
#define RESP_MEASUREMENTINTERVAL 12
#define RESP_PINGTIMEOUT 13
#define RESP_MODE 14
#define RESP_CONNECT_OK 15

// Warning Codes
#define ILLEGAL_CONNECT 100
#define ILLEGAL_HEADER 101
#define ILLEGAL_CONTENT 102