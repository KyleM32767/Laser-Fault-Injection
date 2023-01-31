/*
 * pewpewpew.c
 * 
 * Uses AlphaNov's PDM v5 programming tools to automatically run the laser for a few seconds
 * 
 * Author: Kyle Mitard
 * Created 26 Jan 2023
 */

#include <stdio.h>
#include <windows.h>
#include "pdmv5.h"
#include "pewpewpew.h"

// Serial port for laser 
#define LASER_PORT "COM4"

// address of laser
#define ADDR 1

// laser settings
#define PULSE_WIDTH  200000 // ps
#define PEAK_CURRENT 25     // percent of max (4A)
#define FREQUENCY    100000 // Hz
#define RUN_TIME     3000   // ms

// the serial port for the laser
struct sp_port* p;


/*
 * sets up the laser
 * 
 * Return:
 *  - 0 if success, -1 otherwise
 */
int laser_init() {

	// open serial port
	char strport[] = LASER_PORT;
	if (OpenCommunication_PDMv5(strport, &p) != SP_OK) {
		printf("error opening port\n");
		return -1;
	}

	// set parameters
	if (SetPulseWidth_PDMv5(p, ADDR, PULSE_WIDTH) != 0) {
		printf("error setting current\n");
		return -1;
	}
	if (SetCurrent_PDMv5(p, ADDR, 25) != 0) {
		printf("error setting current\n");
		return -1;
	}
	if (SetFrequency_PDMv5(p, ADDR, FREQUENCY) != 0) {
		printf("error setting frequency\n");
		return -1;
	}
}


/*
 * Fires the laser for a few seconds
 * 
 * Return:
 *  - 0 if success, -1 otherwise 
 */
int pewpewpew() {

	// turn on the laser
	if (SetLaserStatus_PDMv5(p, ADDR, 1) != 0) {
		printf("error setting laser status\n");
		return -1;
	}
	if (ApplyRequest_PDMv5(p, ADDR) != 0) {
		printf("error turning on laser\n");
		return -1;
	}

	// wait a bit
	Sleep(RUN_TIME);

	// turn off the laser
	if (SetLaserStatus_PDMv5(p, ADDR, 0) != 0) {
		printf("error setting laser status\n");
		return -1;
	}
	if (ApplyRequest_PDMv5(p, ADDR) != 0) {
		printf("error turning off laser\n");
		return -1;
	}
}