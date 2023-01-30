/*
 * searchandfault.cpp
 * 
 * Controls the XYZ stages and laser to attempt to induce faults in an FPGA,
 * reprogramming and reporting a fault if needed
 * 
 * Author: Kyle Mitard
 * Created 30 Jan 2023
 */

#include "XYZ_stages/xyz.h"
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
	Sleep(5000);

	// step through until done
	while (!xyz.isDone()) {
		
		try {
			xyz.step();
		} catch (exception e) {
			cout << e.what() << endl;
		}
		Sleep(1000);
	}

	return 0;
}