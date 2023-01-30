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

int main() {

	// XYZ stages instance
	XYZ xyz;

	// set start and end manually
	xyz.setStartAndEnd();
	Sleep(5000);

	// step through until done
	while (!xyz.isDone()) {
		xyz.step();
		Sleep(100);
	}

	return 0;
}