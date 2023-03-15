/*
 * searchandfault.cpp
 * 
 * Controls the XYZ stages and laser to attempt to induce faults in an FPGA,
 * reprogramming and reporting a fault if needed
 * 
 * Author: Kyle Mitard
 * Created 30 Jan 2023
 */

#include "xyz.h"
#include "pewpewpew.h"
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * Main processing
 */
int main() {

	// XYZ stages instance
	XYZ_init();

	// set reference point manually
	if (XYZ_setRefPoint() != 0) {
		cout << "failed to set ref point\n" << flush;
		return -1;
	}

	// set start and end manually
	if (XYZ_setStartAndEnd() != 0) {
		cout << "failed to set start and end\n" << flush;
		return -1;
	}

	// setup laser
	if (laser_init() != 0) {
		cout << "failed to setup laser\n" << flush;
		return -1;
	}

	// wait a bit
	Sleep(1000);

	// step through until done
	while (!XYZ_isDone()) {
		
		// fire the laser
		if (pewpewpew() != 0) {
			cout << "Error firing laser\n" << flush;
			return -1;
		}

		// command used to invoke the python script
		char pythonCmd[50] = "";
		if (XYZ_getPythonCmd(pythonCmd) != 0) {
			cout << "error invoking python script\n";
			return -1;
		}

		// test the xor gate
		system(pythonCmd);
		delete pythonCmd;

		// insert a gap between teste
		cout << "\n\n" << flush;

		// take a step
		if (XYZ_step() != 0) {
			cout << "Error taking step\n" << flush;
			return -1;
		}

		// wait a bit
		Sleep(700);
	}

	return 0;
}