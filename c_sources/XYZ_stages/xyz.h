/*
 * XYZ.h
 * 
 * Class to serve as an extra abtraction layer for XYZ stage functionality
 * 
 * Author: Kyle Mitard
 * Created 30 Jan 2023
 */

#include "Wp2CommDllLoader.h"

/*
 * enumerated type for the current direction of the XYZ stages
 */
typedef enum {
	FORWARD,  // xstep of +1
	BACKWARD, // xstep of -1
	DOWN      // ystep of 0
} XYZDirection;


class XYZ
{
public:

	/*
	 * Constructor
	 */
	XYZ();

	/*
	 * Sets the start and end positions by manually moving with the laser, then 
	 * automatically moves to the start position
	 * 
	 * Return:
	 *  - 0 if no error or -1 otherwise
	 */
	int setStartAndEnd();

	/**
	 * Makes a step in the path 
	 * 
	 * Return:
	 *  - 0 if no error or -1 otherwise
	 */
	int step();

private:

	/*
	 * Waits for the user to type any character
	 */
	void waitForinput();

	// start coordinates
	double _startX;
	double _startY;

	// end coordinates
	double _endX;
	double _endY;
	
	// z stays the same
	char* _z;

	// current direction of movement
	XYZDirection _dir;

	// instance of DLL Loader
	Wp2CommDllLoader _comm;
};