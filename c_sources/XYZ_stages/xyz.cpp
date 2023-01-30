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
		cout << "failed to initialize controller\n";
	}

	// attempt to open controller
	if (_comm.OpenController() != STATE_OK) {
		cout << "failed to open controller\n";
	}
}


int XYZ::setStartAndEnd() {

	// at this point, move to the start position manually
	cout << "press any key then enter when at start position\n";
	waitForinput();

	// attempt to get start position
	char* x1 = new char[20];
	char* y1 = new char[20];
	char* a1 = new char[20];
	if (_comm.GetPos(x1, y1, _z, a1) != STATE_OK) {
		cout << "failed to get position\n";
		return -1;
	}
	cout << "START: (" << x1 << ", " << y1 << ", " << _z << ")\n";
	_startX = stod(x1);
	_startY = stod(y1);

	// at this point, move to the end position manually
	cout << "press any key then enter when at end position\n";
	waitForinput();

	// attempt to get start position
	char* x2 = new char[20];
	char* y2 = new char[20];
	char* z2 = new char[20];
	char* a2 = new char[20];
	if (_comm.GetPos(x2, y2, z2, a2) != STATE_OK) {
		cout << "failed to get position\n";
		return -1;
	}
	cout << "END:   (" << x2 << ", " << y2 << ", " << z2 << ")\n";
	_endX = stod(x2);
	_endY = stod(y2);

	// attempt to move back to start position
	if (_comm.MoveAbsolute(x1,y1,_z,NULL) != STATE_OK) {
		cout << "failed to move\n";
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

	return 0;
}


int XYZ::step() {

	int error;

	// move depending on direction
	switch (_dir) {
		case LEFT:
			error = _comm.MoveRelative("1", "0", "0", NULL);
			break;
		case RIGHT:
			error = _comm.MoveRelative("-1", "0", "0", NULL);
			break;
		case UP:
			error = _comm.MoveRelative("0", "1", "0", NULL);
			break;
		case DOWN:
			error = _comm.MoveRelative("0", "-1", "0", NULL);
			break;
	}

	// return if there was an error
	if (error != STATE_OK)
		return -1;

	// get new position
	char* newX;
	char* newY;
	char* newZ;
	char* newA;
	_comm.GetPos(newX, newY, newZ, newA);

	// return if there was an error
	if (error != STATE_OK)
		return -1;

	// change row if the end is hit on the x direction
	if ((_dir == LEFT  && stod(newX) >= _startX && stod(newX) >= _endX)
	 || (_dir == RIGHT && stod(newX) <= _startX && stod(newX) <= _endX))
		_dir = _verticalStepDir;

	// stop if the end is hit in the y direction
	else if ((_dir == UP   && stod(newY) >= _startY && stod(newY) >= _endY)
		  || (_dir == DOWN && stod(newY) <= _startY && stod(newY) <= _endY))
		_dir = STOP;
	
	return 0;
}


bool XYZ::isDone() {
	return _dir == STOP;
}