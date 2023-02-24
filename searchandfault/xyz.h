/*
 * XYZ.h
 * 
 * Header file for a class to serve as an extra abtraction layer for XYZ stage functionality
 * 
 * Author: Kyle Mitard
 * Created 30 Jan 2023
 */

#ifndef XYZ_H
#define XYZ_H

/*
 * Constructor
 */
void XYZ_init();


/*
 * Sets the reference point for the image and writes it to result/refpoint.txt
 * 
 * Return:
 *   0 if no error or -1 otherwise
 */
int XYZ_setRefPoint();


/*
 * Sets the start and end positions by manually moving with the laser, then 
 * automatically moves to the start position
 * 
 * Return:
 *   0 if no error or -1 otherwise
 */
int XYZ_setStartAndEnd();


/*
 * Makes a step in the path 
 * 
 * Return:
 *   0 if no error or -1 otherwise
 */
int XYZ_step();


/*
 * gets the command to call the python script based on the current position
 * 
 * Params:
 *   cmdBuf = pointer to string buffer containing the command
 * 
 * Return:
 *   0 if no error or -1 otherwise
 */
int XYZ_getPythonCmd(char* cmdBuf);


/*
 * returns true if at the end of the search 
 * 
 * Return:
 *   1 if at the end or 0 otherwise
 */
bool XYZ_isDone();

#endif