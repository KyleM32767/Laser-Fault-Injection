/*
 * xyz.cpp
 * 
 * ss
 * 
 * Author: Kyle Mitard
 * Created 27 Jan 2023
 */

#include "xyz.h"
#include <iostream>
#include <fstream>

using namespace std;

// serial port for XYZ stage
#define XYZ_PORT (DWORD) 9

// these are things that won't be changed
#define CORVUS_CONTROLLER (DWORD) 64
#define N_AXES            (DWORD) 3
#define BAUD_RATE         (DWORD) 57600
#define MODE_SYNCHRONOUS  (DWORD) 1050884


double _startX;
double _startY;
double _startZ;

char PLUS_ONE[] = "0.002";
char MINUS_ONE[] = "-0.002";
char ZERO[] = "0";

// a low stage velocity to prevent vibrations from messing with things
char VELOCITY[]  = "0.05";


void XYZ::waitForinput() {
	char in = '\0';
	while (in == '\0') {
		cin >> in;
	}
}


XYZ::XYZ() {
	// attempt to initialize
	if (_comm.InitController(CORVUS_CONTROLLER, N_AXES, XYZ_PORT,
	                        BAUD_RATE, 0, 0, MODE_SYNCHRONOUS) != STATE_OK) {
		cout << "failed to initialize controller\n" << flush;
	}

	// attempt to open controller
	if (_comm.OpenController() != STATE_OK) {
		cout << "failed to open controller\n" << flush;
	}

	// set a low velocity
	if (_comm.SetVelocity(VELOCITY) != 0) {
		cout << "failed to set velocity\n" << flush;
	}
}


/*
 * Sets the reference point for the image and writes it to result/refpoint.txt
 * 
 * Return:
 *  - 0 if no error or -1 otherwise
 */
int XYZ::setRefPoint() {

	// enable joystick
	if (_comm.JoystickEnable() != STATE_OK) {
		cout << "failed to enable Joystick\n" << flush;
		return -1;
	}

	// stream for reference point file 
	ofstream refPoint;
	refPoint.open("result/refpoint.txt");

	// instructions
	char* inBuf = new char[30];
	cout << "First, a reference point must be set by following these steps..." << endl 
		 << "\t1) Open LUCIE and take a picture of the area, and save it to result/map.png" << endl
		 << "\t3) Using the joystick, aim the laser such that it is on top of a point that is easy to locate on the image" << endl
		 << "\t3) Open MS paint and find the pixel location of where you aimed on the image you took in step 1" << endl
		 << "\t4) Type the coordinates below" << endl
		 << "after you are done typing the Y-coordinate, the position of the stages will be taken and written" << endl;
	
	// write image coordinates to reference file
	cout << "x = " << flush;
	cin >> inBuf;
	refPoint << inBuf << endl;
	cout << "y = " << flush;
	cin >> inBuf;
	refPoint << inBuf << endl;
	
	// get IRL position and write to reference file
	char* x1 = new char[20];
	char* y1 = new char[20];
	char* z1 = new char[20];
	char* a1 = new char[20];
	if (_comm.GetPos(x1, y1, z1, a1) != STATE_OK) {
		cout << "failed to get position\n" << flush;
		return -1;
	}
	refPoint << x1 << endl << y1 << endl;

	// delete things
	delete x1;
	delete y1;
	delete z1;
	delete a1;
	delete inBuf;

	return 0;
}


int XYZ::setStartAndEnd() {

	// enable joystick
	if (_comm.JoystickEnable() != STATE_OK) {
		cout << "failed to enable Joystick\n" << flush;
		return -1;
	}

	// at this point, move to the start position manually
	cout << "press any key then enter when at start position\n" << flush;
	waitForinput();

	// attempt to get start position
	char* x1 = new char[20];
	char* y1 = new char[20];
	char* a1 = new char[20];
	if (_comm.GetPos(x1, y1, _z, a1) != STATE_OK) {
		cout << "failed to get position\n" << flush;
		return -1;
	}
	cout << "START: (" << x1 << ", " << y1 << ", " << _z << ")\n" << flush;
	_startX = stod(x1);
	_startY = stod(y1);

	// at this point, move to the end position manually
	cout << "press any key then enter when at end position\n" << flush;
	waitForinput();

	// attempt to get start position
	char* x2 = new char[20];
	char* y2 = new char[20];
	char* z2 = new char[20];
	char* a2 = new char[20];
	if (_comm.GetPos(x2, y2, z2, a2) != STATE_OK) {
		cout << "failed to get position\n" << flush;
		return -1;
	}
	cout << "END:   (" << x2 << ", " << y2 << ", " << z2 << ")\n" << flush;
	_endX = stod(x2);
	_endY = stod(y2);

	// attempt to move back to start position
	if (_comm.MoveAbsolute(x1,y1,_z,NULL) != STATE_OK) {
		cout << "failed to move\n" << flush;
		return -1;
	}

	// set initial direction
	if (_startX > _endX)
		_dir = RIGHT;
	else
		_dir = LEFT;
	

	// set y step direction
	if (_startY > _endY)
		_verticalStepDir = DOWN;
	else
		_verticalStepDir = UP;

	// enable joystick
	if (_comm.JoystickEnable() != STATE_OK) {
		cout << "failed to disable Joystick\n";
		return -1;
	}

	// draw on map image
	char cmdBuf[50] = "";
	strcat(cmdBuf, "python drawBounds.py ");
	strcat(cmdBuf, x1);
	strcat(cmdBuf, " ");
	strcat(cmdBuf, y1);
	strcat(cmdBuf, " ");
	strcat(cmdBuf, x2);
	strcat(cmdBuf, " ");
	strcat(cmdBuf, y2);
	system(cmdBuf);

	return 0;
}


int XYZ::step() {

	int error;

	cout << "moved ";

	// move depending on direction
	switch (_dir) {
		case LEFT:
			error = _comm.MoveRelative(PLUS_ONE, ZERO, ZERO, NULL);
			cout << "left to  ";
			break;
		case RIGHT:
			error = _comm.MoveRelative(MINUS_ONE, ZERO, ZERO, NULL);
			cout << "right to ";
			break;
		case UP:
			error = _comm.MoveRelative(ZERO, PLUS_ONE, ZERO, NULL);
			cout << "up to    ";
			break;
		case DOWN:
			error = _comm.MoveRelative(ZERO, MINUS_ONE, ZERO, NULL);
			cout << "down to  ";
			break;
	}

	// return if there was an error
	if (error != STATE_OK) {
		cout << "error moving\n" << flush;
		return -1;
	}

	// get new position
	char* newX = new char[20];
	char* newY = new char[20];
	char* newZ = new char[20];
	char* newA = new char[20];
	_comm.GetPos(newX, newY, newZ, newA);
	cout << "(" << newX << ", " << newY << ", " << newZ << ")\n" << flush;

	// return if there was an error
	if (error != STATE_OK) {
		cout << "error getting position\n" << flush;
		return -1;
	}

	// go to a vertical step at the end of a row 
	if ((_dir == LEFT  && stod(newX) >= _startX && stod(newX) >= _endX)
	 || (_dir == RIGHT && stod(newX) <= _startX && stod(newX) <= _endX))
		_dir = _verticalStepDir;
	
	
	else if (_dir == _verticalStepDir) {
		
		// stop if the end is hit in the y direction
		if ((_dir == UP   && stod(newY) && stod(newY) >= _endY)
		 || (_dir == DOWN && stod(newY) && stod(newY) <= _endY))
			_dir = STOP;
		
		// after a vertical step, go back to horizontal
		else if (stod(newX) >= _startX && stod(newX) >= _endX)
			_dir = RIGHT;
		else
			_dir = LEFT;

	}

	// enable joystick
	if (_comm.JoystickEnable() != STATE_OK) {
		cout << "failed to disable Joystick\n";
		return -1;
	}
	
	// delete stuff
	delete newX;
	delete newY;
	delete newZ;
	delete newA;

	return 0;
}

int XYZ::getPythonCmd(char* cmdBuf) {
	
	// get new position
	char* newX = new char[20];
	char* newY = new char[20];
	char* newZ = new char[20];
	char* newA = new char[20];
	if (_comm.GetPos(newX, newY, newZ, newA) != STATE_OK) {
		cout << "error getting position\n" << flush;
		return -1;
	}
	
	strcat(cmdBuf, "python testandprogram.py COM15 ");
	strcat(cmdBuf, newX);
	strcat(cmdBuf, " ");
	strcat(cmdBuf, newY);
	
	delete newX;
	delete newY;
	delete newZ;
	delete newA;

	return 0;
}

bool XYZ::isDone() {
	
	if (_dir == STOP) 
		_comm.JoystickEnable();
	
	return _dir == STOP;
}

