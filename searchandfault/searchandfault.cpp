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

int main() {

	// XYZ stages instance
	XYZ xyz;

	// set reference point manually
	if (xyz.setRefPoint() != 0) {
		cout << "failed to set ref point\n" << flush;
		return -1;
	}

	// set start and end manually
	if (xyz.setStartAndEnd() != 0) {
		cout << "failed to set start and end\n" << flush;
		return -1;
	}

	// set start and end manually
	if (laser_init() != 0) {
		cout << "failed to setup laser\n" << flush;
		return -1;
	}


	// wait a bit
	Sleep(5000);

	// command used to invoke the python script
	char pythonCmd[50];

	// step through until done
	while (!xyz.isDone()) {
		
		// fire the laser
		if (pewpewpew() != 0) {
			cout << "Error firing laser\n" << flush;
			return -1;
		}

		xyz.getPythonCmd(pythonCmd);

		// test the xor gate
		system(pythonCmd);

		// insert a newline
		cout << "\n\n" << flush;

		// take a step
		if (xyz.step() != 0) {
			cout << "Error taking step\n" << flush;
			return -1;
		}

		// wait a bit
		Sleep(1000);
	}

	return 0;
}