//---------------------------------------------------------------------------
//                              Wp2CommDllLoader.h
//---------------------------------------------------------------------------
//  Copyright (C): ITK Dr. Kassen GmbH, 2015
//---------------------------------------------------------------------------
/**
\mainpage The Wp2CommDemo Example documentation

This is a example project to show how you can include the `Wp2Comm.dll` into your project.
It contains the `Wp2CommDllLoader.h` header file and `Wp2CommDllLoader.cpp`. These are
the most important files, which should be reused in other projects you create for using
the `Wp2Comm.dll`. In this documentation only `Wp2CommDllLoader.h` is described, because
the `.cpp` file contains the definitions of all class functions of the header file.
At the same time each exported function of the `Wp2Comm.dll` is included in these files
for using the dll functions with the equal call.
So you have to use these two files. It is your decision how you implement your application. It could be
a project with a graphical user interface or a console application. For using
the `Wp2Comm.dll`the Visual C++ libraries `msvcp120.dll` (C run-time library functions)
and `msvcr120.dll` (C++ run-time functions) should be available.
These two dll's are also redistributed by this project. There is also a executable `Wp2CommDemo.exe`
with a GUI example, which uses these two files to call the `Wp2Comm.dll` functions.

*/
#include <Windows.h>

#if defined _WIN64
#define IS64Bit   1
#else
#define IS64Bit   0
#endif


#ifndef __WP2COMMDLLLoader__
#define __WP2COMMDLLLoader__

/*! \def WMU_ASYNCMSG
\Message posted in asynchronous mode to signal that the controller replied and the data can be processed.
*/
#define		WMU_ASYNCMSG		WM_USER+10

#define STATE_OK 0
#define NOT_ENOUGH_MEMORY 2
#define NOT_CONNECTED 3
#define INVALID_PORT 4
#define INVALID_COMMAND 5
#define INVALID_CONTROLLER 6
#define INVALID_AXES 7
#define INVALID_AXIS 8
#define INVALID_BAUDRATE 9
#define WAITING_FOR_REPLY 10
#define INVALID_POSDATA 11
#define INVALID_DATA 12
#define INVALID_REPLY 13
#define INVALID_POINTER 14
#define NO_REPLY_FROM_CONTROLLER 15
#define INVALID_IDENTIFY 16
#define INVALID_INTERPRETER 17
#define ERROR_SENDING_BREAK_CHAR 18
#define WAIT_TIMEOUT 19
#define WAIT_FAILED 20
#define BREAK_DETECTED 21
#define VALIDATE_NOT_READY 22
#define FUNCTION_NOT_AVAILABLE 23
#define EVERR 24


typedef DWORD(*PInitController)(DWORD ControllerMode, DWORD Axes, DWORD ComPort, DWORD Baudrate, HWND UserWin, UINT AsyncMsg, DWORD Mode);
typedef DWORD(*POpenController)();
typedef DWORD(*PCloseController)();
typedef DWORD(*PExecuteCommand)(LPSTR Command, DWORD LinesExpected, LPSTR Reply);
typedef DWORD(*PGetReply)(LPSTR Reply);
typedef DWORD(*PRangeMeasure)();
typedef DWORD(*PAbortCommand)();
typedef DWORD(*PCalibrate)();
typedef DWORD(*PGetAcceleration)(LPSTR Accel);
typedef DWORD(*PSetAcceleration)(LPSTR Accel);
typedef DWORD(*PGetDllVersion)(double *Version);
typedef DWORD(*PGetVelocity)(LPSTR Vel);
typedef DWORD(*PSetVelocity)(LPSTR Vel);
typedef DWORD(*PIdentify)(LPSTR Id);
typedef DWORD(*PIsClearBufferEmpty)(BOOL *IsEmpty);
typedef DWORD(*PGetStatus)(LPDWORD Status);
typedef DWORD(*PGetError)(LPDWORD Error);
typedef DWORD(*PGetLimits)(LPSTR A1Min, LPSTR A1Max, LPSTR A2Min, LPSTR A2Max, LPSTR A3Min, LPSTR A3Max, LPSTR A4Min, LPSTR A4Max);
typedef DWORD(*PGetParamsOnStack)(LPDWORD Value);
typedef DWORD(*PClearParameterStack)();
typedef DWORD(*PGetPos)(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);
typedef DWORD(*PMoveAbsolute)(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);
typedef DWORD(*PMoveRelative)(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);
typedef DWORD(*PMoveAbsoluteAutoReply)(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);
typedef DWORD(*PMoveRelativeAutoReply)(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);
typedef DWORD(*PResetComm)(void);
typedef DWORD(*PJoystickEnable)();
typedef DWORD(*PJoystickDisable)();
typedef DWORD(*PGetJoystickVelocity)(LPSTR JoyVel);
typedef DWORD(*PSetJoystickVelocity)(LPSTR JoyVel);
typedef DWORD(*PGetAxisMode)(LPDWORD Axis1Mode, LPDWORD Axis2Mode, LPDWORD Axis3Mode, LPDWORD Axis4Mode);
typedef DWORD(*PSetAxisMode)(LPSTR Axis1Mode, LPSTR Axis2Mode, LPSTR Axis3Mode, LPSTR Axis4Mode);
typedef DWORD(*PSetOrigin)(void);
typedef DWORD(*PPreprocessReply)(BYTE Active);
typedef DWORD(*PSetClearBufferEmpty)(BOOL ClearBuffer);
typedef DWORD(*PSetDecimalSeparator)(BYTE DecimalSep);
typedef DWORD(*PSetSleepWhileWaitingWithoutTimeout)(DWORD milliseconds);


class Wp2CommDllLoader
{
	int			m_DLLResultat = 0;		// DLL-Zugriff ok
	bool		isDllLoad = false;
	HINSTANCE	hITKVenus;				// Handle auf DLL

	PInitController m_InitController;
	POpenController m_OpenController;
	PCloseController m_CloseController;
	PExecuteCommand m_ExecuteCommand;
	PGetReply m_GetReply;
	PRangeMeasure m_RangeMeasure;
	PAbortCommand m_AbortCommand;
	PCalibrate m_Calibrate;
	PGetAcceleration m_GetAcceleration;
	PSetAcceleration m_SetAcceleration;
	PGetDllVersion m_GetDllVersion;
	PGetVelocity m_GetVelocity;
	PSetVelocity m_SetVelocity;
	PIdentify m_Identify;
	PIsClearBufferEmpty m_IsClearBufferEmpty;
	PGetStatus m_GetStatus;
	PGetError m_GetError;
	PGetLimits m_GetLimits;
	PGetParamsOnStack m_GetParamsOnStack;
	PClearParameterStack m_ClearParameterStack;
	PGetPos m_GetPos;
	PMoveAbsolute m_MoveAbsolute;
	PMoveRelative m_MoveRelative;
	PMoveAbsoluteAutoReply m_MoveAbsoluteAutoReply;
	PMoveRelativeAutoReply m_MoveRelativeAutoReply;
	PResetComm m_ResetComm;
	PJoystickEnable m_JoystickEnable;
	PJoystickDisable m_JoystickDisable;
	PGetJoystickVelocity m_GetJoystickVelocity;
	PSetJoystickVelocity m_SetJoystickVelocity;
	PGetAxisMode m_GetAxisMode;
	PSetAxisMode m_SetAxisMode;
	PSetOrigin m_SetOrigin;
	PPreprocessReply m_PreprocessReply;
	PSetClearBufferEmpty m_SetClearBufferEmpty;
	PSetDecimalSeparator m_SetDecimalSeparator;
	PSetSleepWhileWaitingWithoutTimeout m_SetSleepWhileWaitingWithoutTimeout;

public:
	//! The default constructor.
	/*!
	The default constructor initializes all functions and tries to load the <b>Venus3.dll</b>. If the loading
	is successfully completed, it retrieves the addresses of all exported functions from the specified dynamic-link library.
	*/
	Wp2CommDllLoader();
	~Wp2CommDllLoader();

	//! The isDllLoaded function to check if the <b>Wp2Comm.dll</b> is successfuly loaded.
	/*!
	This function returns true if the  <b>Wp2Comm.dll</b> could be loaded, false if loading process failed.
	*/
	boolean isDllLoaded();

	/**  Sets the main parameters, Wp2Comm.dll uses to communicate with the controller. InitController must be called first.
	*
	* @param ControllerMode Type of the controller, for Corvus = 64 (for the time being, only Corvus is supported) 
	* @param Axes Number of axes ( usually 3 or 4), for Corvus 1-3 axes are supported
	* @param ComPort The port number
	* @param Baudrate The baudrate (300...115200)
	* @param UserWin Handle of the window to post AsyncMsg to. Can be 0 if no asynchronous mode is used (default).
	* @param AsyncMsg Message posted in asynchronous mode to signal that the controller replied and the data can be processed. Can be 0 if no asynchronous mode is used otherwise a WM_USER value.
	* @param Mode Used to set the mode, the DLL uses to process Venus-commands internally, default value for synchronous mode is 1050884 (or 2308), for asynchronous mode 1051140 (or 2564).
	*
	*
	* @return
	*   Returns the state of the InitController command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD InitController(DWORD ControllerMode, DWORD Axes, DWORD ComPort, DWORD Baudrate, HWND UserWin, UINT AsyncMsg, DWORD Mode);

	/**  Opens the COM-port and connects to the controller. Make sure to have calles InitController() before executing OpenController().
	*
	* @return
	*   Returns the state of the OpenController command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD OpenController();

	/**  Closes the port, clears buffers, includes ResetComm() and if need be it stops all running threads for the asynchronous mode.
	*
	* @return
	*   Returns the state of the CloseController command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD CloseController();

	/**  Executes a venus command.
	*
	* @param Command The command itself
	* @param LinesExpected Number of lines, the controller will return processing the command (a line is terminated by CR\LF)
	* @param Reply Data returned by the controller
	*
	*
	* @return
	*   Returns the state of the ExecuteCommand command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD ExecuteCommand(LPSTR Command, DWORD LinesExpected, LPSTR Reply);

	/**  Retrieves data sent by the controller; used in asynchronous mode.
	*
	* @param Reply Buffer to receive the data
	*
	*
	* @return
	*   Returns the state of the GetReply command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetReply(LPSTR Reply);

	/**  By default Wp2Comm.dll preprocesses the data returned by the controller, eliminates leading and trailing spaces,
	* CR/LF and replaces the '.' by the decimalseperator as set in Windows (default) or by SetDecimalSeperator().
	*
	* @param Active 0 = Don't preprocess the data, <> 0 = Preprocess data (default)
	*
	* @return
	*   Returns the state of the PreprocessReply command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD PreprocessReply(BYTE Active);

	/**  
	*	
	*
	* @param ClearBuffer -> decides whether the buffer should be read empty after ExecuteCommand
	*
	* @return
	*    Returns the state of the SetClearBufferEmpty command. 0 if the command is successfully executed,
	*	 otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetClearBufferEmpty(BOOL ClearBuffer);

	/**  By default Wp2Comm.dll preprocesses the data returned by the controller,
	* replaces the '.' by the decimalseperator as set in Windows. Set DecimalSeparator() allows to change this behaviour.
	*
	* @param DecimalSep 0 = Use decimal separator of windows (default), 0xFF = Leave decimal separartor unchanged, Every other value = Use this byte as decimal separator
	*
	* @return
	*   Returns the state of the SetDecimalSeparator command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetDecimalSeparator(BYTE DecimalSep);

	/**  This function sets a the sleeping time for internally used function Sleep() which is used in a function that is polling.( e.g. MoveAbsoluteAutoReply)
	*
	* @param milliseconds Sleep time of wp2comm.dll polling routine in milliseconds 0 = no sleep() is performed
	*
	* @return
	*   Returns the state of the SetSleepWhileWaitingWithoutTimeout command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetSleepWhileWaitingWithoutTimeout(DWORD milliseconds);

	/**  Sends a Break ([Ctrl] + [C]) to the controller, aborting the command (e.g.terminating move operation).
	*
	*
	* @return
	*   Returns the state of the AbortCommand command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: [Ctrl] + [C]
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD AbortCommand();

	/**  Calibrates the controller; see RangeMeasure().
	*
	*
	* @return
	*   Returns the state of the Calibrate command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: calibrate/cal
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD Calibrate();

	/**  Clears the controller stack.
	*
	* @return
	*   Returns the state of the ClearParameterStack command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: clear
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD ClearParameterStack();

	/**  Gets the acceleration of all axes.
	*
	* @param Accel acceleration in current unit
	*
	* @return
	*   Returns the state of the GetAcceleration command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: getaccel/ga
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetAcceleration(LPSTR Accel);

	/**  Gets the mode of the axes
	*
	* @param Axis1Mode value defining the mode of axis 1, can be NULL if the axis doesn't exist.
	* @param Axis2Mode value defining the mode of axis 2, can be NULL if the axis doesn't exist.
	* @param Axis3Mode value defining the mode of axis 3, can be NULL if the axis doesn't exist.
	* @param Axis4Mode value defining the mode of axis 4, can be NULL if the axis doesn't exist.
	*
	* @return
	*   Returns the state of the GetAxisMode command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: getaxis
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetAxisMode(LPDWORD Axis1Mode, LPDWORD Axis2Mode, LPDWORD Axis3Mode, LPDWORD Axis4Mode);

	/**  Returns the DLL version.
	*
	* @param Version 
	*
	* @return
	*   Returns the state of the GetDllVersion command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetDllVersion(double *Version);

	/**  Gets the error code of the controller.
	*
	* @param Error Error code
	*
	* @return
	*   Returns the state of the GetError command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: geterror/ge
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetError(LPDWORD Error);


	/**  Gets the joystick velocity
	*
	* @param JoyVel joystick velocity
	*
	* @return
	*   Returns the state of the GetJoystickVelocity command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: getjoyspeed
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetJoystickVelocity(LPSTR JoyVel);

	/**  Gets the limit coordinates of all axes.
	*
	* @param A1Min Lower limit value of axis 1
	* @param A1Max Upper limit value of axis 1
	* @param A2Min Lower limit value of axis 2
	* @param A2Max Upper limit value of axis 2
	* @param A3Min Lower limit value of axis 3
	* @param A3Max Upper limit value of axis 3
	* @param A4Min Lower limit value of axis 4
	* @param A4Max Upper limit value of axis 4
	*
	* @return
	*   Returns the state of the GetLimits command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: getlimit
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetLimits(LPSTR A1Min, LPSTR A1Max, LPSTR A2Min, LPSTR A2Max, LPSTR A3Min, LPSTR A3Max, LPSTR A4Min, LPSTR A4Max);

	/**  Gets the number of parameters on the stack of the controller.
	*
	* @param Value Number of parameters on the stack
	*
	* @return
	*   Returns the state of the GetParamsOnStack command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: gsp
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetParamsOnStack(LPDWORD Value);

	/**  Gets the current position (coordinate) of all active axes.
	*
	* @param Axis1Pos Current position of axis 1 in current unit. Can be NULL if the axis does not exist.
	* @param Axis2Pos Current position of axis 2 in current unit. Can be NULL if the axis does not exist.
	* @param Axis3Pos Current position of axis 3 in current unit. Can be NULL if the axis does not exist.
	* @param Axis4Pos Current position of axis 4 in current unit. Can be NULL if the axis does not exist.
	*
	* @return
	*   Returns the state of the GetPos command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: pos/p
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetPos(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);

	/**  Gets the controller status.
	*
	* @param Status Status of the controller
	*
	* @return
	*   Returns the state of the GetStatus command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: status/st
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetStatus(LPDWORD Status);

	/**  Gets the velocity of all axes.
	*
	* @param Vel Velocity in current unit
	*
	* @return
	*   Returns the state of the GetVelocity command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: getvel/gv
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD GetVelocity(LPSTR Vel);

	/**  Gets the identify string of the controller.
	*
	* @param Id identify string
	*
	* @return
	*   Returns the state of the Identify command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: identify
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD Identify(LPSTR Id);

	/**  Returns whether clearing buffer after calling functionExecuteCommand is activated.
	*
	* @param isEmpty 
	*
	* @return
	*   Returns the state of the IsClearBufferEmpty command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD IsClearBufferEmpty(BOOL *isEmpty);

	/**  Turns joystick off
	*
	* @return
	*   Returns the state of the JoystickDisable command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: 0 joystick/0 nj
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD JoystickDisable();

	/**  Turns joystick on
	*
	* @return
	*   Returns the state of the JoystickEnable command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: 1 joystick/1 nj
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD JoystickEnable();

	/**  Moves the axes to the desired absolute coordinates.
	*
	* @param Axis1Pos Absolute position for axis 1 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis2Pos Absolute position for axis 2 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis3Pos Absolute position for axis 3 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis4Pos Absolute position for axis 4 in current unit to move to. Can be NULL if the axis does not exist.
	*
	* @return
	*   Returns the state of the MoveAbsolute command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: move/m
	*
	* @remarks While a move operation is performed it is possible to determine the position with GetPos() and the status with GetStatus()
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD MoveAbsolute(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);

	/**  Moves the axes to the desired absolute coordinates; after reaching the target the function returns.
	*
	* @param Axis1Pos Absolute position for axis 1 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis2Pos Absolute position for axis 2 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis3Pos Absolute position for axis 3 in current unit to move to. Can be NULL if the axis does not exist.
	* @param Axis4Pos Absolute position for axis 4 in current unit to move to. Can be NULL if the axis does not exist.
	*
	* @return
	*   Returns the state of the MoveAbsoluteAutoReply command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: move/m, status/st
	*
	* @remarks The AutoReply-function returns only, when a desired target is reached. So, GetPos() and GetStatus() cannot be used externally, because this is done even in the function.
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD MoveAbsoluteAutoReply(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);

	/**  Moves the axes relative starting from the current position.
	*
	* @param Axis1Pos Relative position for axis 1 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis2Pos Relative position for axis 2 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis3Pos Relative position for axis 3 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis4Pos Relative position for axis 4 in current unit to move. Can be NULL if the axis does not exist.
	*
	* @return
	*   Returns the state of the MoveRelative command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: rmove/rm
	*
	* @remarks While a move operation is performed it is possible to determine the position with GetPos() and the status with GetStatus()
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD MoveRelative(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);

	/**  Moves the axes relative starting from the current position; after reaching the target the function returns.
	*
	* @param Axis1Pos Relative position for axis 1 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis2Pos Relative position for axis 2 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis3Pos Relative position for axis 3 in current unit to move. Can be NULL if the axis does not exist.
	* @param Axis4Pos Relative position for axis 4 in current unit to move. Can be NULL if the axis does not exist.
	*
	* @return
	*   Returns the state of the MoveRelativeAutoReply command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: rmove/rm, status/st
	*
	* @remarks The AutoReply-function returns only, when a desired target is reached. So, GetPos() and GetStatus() cannot be used externally, because this is done even in the function.
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD MoveRelativeAutoReply(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos);

	/**  Measures the stage to determine the limits.
	*
	*
	* @return
	*   Returns the state of the RangeMeasure command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: rangemeasure/rm
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD RangeMeasure();

	/**  Should be called in case of communication errors. Clears COM-buffers, program buffers, resets errors
	*
	* @return
	*   Returns the state of the ResetComm command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD ResetComm(void);

	/**  Sets the acceleration of all axes.
	*
	* @param Accel acceleration in current unit
	*
	* @return
	*   Returns the state of the SetAcceleration command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: setaccel/sa
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetAcceleration(LPSTR Accel);

	/**  Sets the mode of the axes
	*
	* @param Axis1Mode value defining the mode of axis 1, can be NULL if the axis doesn't exist.
	* @param Axis2Mode value defining the mode of axis 2, can be NULL if the axis doesn't exist.
	* @param Axis3Mode value defining the mode of axis 3, can be NULL if the axis doesn't exist.
	* @param Axis4Mode value defining the mode of axis 4, can be NULL if the axis doesn't exist.
	*
	* @return
	*   Returns the state of the SetAxisMode command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: setaxis
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetAxisMode(LPSTR Axis1Mode, LPSTR Axis2Mode, LPSTR Axis3Mode, LPSTR Axis4Mode);

	/**  Sets the joystick velocity
	*
	* @param JoyVel joystick velocity
	*
	* @return
	*   Returns the state of the SetJoystickVelocity command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: joyspeed/js
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetJoystickVelocity(LPSTR JoyVel);

	/**  Sets the current coordinate as the point of origin (as zero).
	*
	* @return
	*   Returns the state of the SetOrigin command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: setpos
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetOrigin(void);

	/**  Sets the velocity of all axes.
	*
	* @param Vel Velocity in current unit
	*
	* @return
	*   Returns the state of the SetVelocity command. 0 if the command is successfully executed,
	*	otherwise a value greater than zero. (see error codes)
	*
	* @see Venus command: setvel/sv
	*
	* @internal
	*
	* @bug
	*
	**/
	DWORD SetVelocity(LPSTR Vel);

};


#endif