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
using namespace std;

int main() {

	// XYZ stages instance
	XYZ xyz;

	// set start and end manually
	if (xyz.setStartAndEnd() != 0) {
		cout << "failed to set start and end\n";
		return -1;
	}

	// set start and end manually
	if (laser_init() != 0) {
		cout << "failed to setup laser\n";
		return -1;
	}


	// wait a bit
	Sleep(5000);

	// step through until done
	while (!xyz.isDone()) {
		
		// fire the laser
		if (pewpewpew() != 0) {
			cout << "Error firing laser\n";
			return -1;
		}

		cout << flush;

		// test the xor gate
		system("python testandprogram.py COM15");

		// take a step
		if (xyz.step() != 0) {
			cout << "Error taking step\n";
			return -1;
		}

		// wait a bit
		Sleep(1000);
	}

	return 0;
}