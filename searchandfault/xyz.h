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
	LEFT,  // xstep of +1
	RIGHT, // xstep of -1
	UP,    // ystep of +1
	DOWN,  // ystep of -1
	STOP   // stopped
} XYZDirection;


class XYZ
{
public:

	/*
	 * Constructor
	 */
	XYZ();


	/*
	 * Sets the reference point for the image and writes it to result/refpoint.txt
	 * 
	 * Return:
	 *   0 if no error or -1 otherwise
	 */
	int setRefPoint();


	/*
	 * Sets the start and end positions by manually moving with the laser, then 
	 * automatically moves to the start position
	 * 
	 * Return:
	 *   0 if no error or -1 otherwise
	 */
	int setStartAndEnd();


	/*
	 * Makes a step in the path 
	 * 
	 * Return:
	 *   0 if no error or -1 otherwise
	 */
	int step();


	/*
	 * gets the command to call the python script based on the current position
	 * 
	 * Params:
	 *   cmdBuf = pointer to string buffer containing the command
	 * 
	 * Return:
	 *   0 if no error or -1 otherwise
	 */
	int getPythonCmd(char* cmdBuf);


	/*
	 * returns true if at the end of the search 
	 * 
	 * Return:
	 *   1 if at the end or 0 otherwise
	 */
	bool isDone();

private:

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

	// direction to take when the end is reached
	XYZDirection _verticalStepDir;

	// instance of DLL Loader
	Wp2CommDllLoader _comm;
};