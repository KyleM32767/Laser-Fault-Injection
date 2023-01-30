/*
 * xyz.cpp
 * 
 * ss
 * 
 * Author: Kyle Mitard
 * Created 27 Jan 2023
 */

#include <iostream>
#include <fstream>
#include "Wp2CommDllLoader.h"

using namespace std;

// serial port for XYZ stage
#define XYZ_PORT (DWORD) 9

// these are things that won't be changed
#define CORVUS_CONTROLLER (DWORD) 64
#define N_AXES            (DWORD) 3
#define BAUD_RATE         (DWORD) 57600
#define MODE_SYNCHRONOUS  (DWORD) 1050884


/*
 * Waits for the user to type any character
 */
void waitForinput() {
	char in = '\0';
	while (in == '\0') {
		cin >> in;
	}
}


/* 
 * Main Processing
 */
int main() {
	
	// instance of DLL loader
	Wp2CommDllLoader comm;

	// attempt to initialize
	if (comm.InitController(CORVUS_CONTROLLER, N_AXES, XYZ_PORT,
	                        BAUD_RATE, 0, 0, MODE_SYNCHRONOUS) != STATE_OK) {
		cout << "failed to initialize controller\n";
		return -1;
	}

	// attempt to open controller
	if (comm.OpenController() != STATE_OK) {
		cout << "failed to open controller\n";
		return -1;
	}

	// at this point, move to the start position manually
	cout << "press any key then enter when at start position\n";
	waitForinput();

	// attempt to get start position
	char* x1 = new char[20];
	char* y1 = new char[20];
	char* z1 = new char[20];
	char* a1 = new char[20];
	if (comm.GetPos(x1, y1, z1, a1) != STATE_OK) {
		cout << "failed to get position\n";
		return -1;
	}
	cout << "START: (" << x1 << ", " << y1 << ", " << z1 << ")\n";


	// at this point, move to the end position manually
	cout << "press any key then enter when at end position\n";
	waitForinput();

	// attempt to get start position
	char* x2 = new char[20];
	char* y2 = new char[20];
	char* z2 = new char[20];
	char* a2 = new char[20];
	if (comm.GetPos(x2, y2, z2, a2) != STATE_OK) {
		cout << "failed to get position\n";
		return -1;
	}
	cout << "END:   (" << x2 << ", " << y2 << ", " << z2 << ")\n";


	return 0;
}