//---------------------------------------------------------------------------
//                              Wp2CommDllLoader.cpp
//---------------------------------------------------------------------------
//  Copyright (C): ITK Dr. Kassen GmbH, 2015
//---------------------------------------------------------------------------
#include <Windows.h>
#include "Wp2CommDllLoader.h"
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;


Wp2CommDllLoader::Wp2CommDllLoader(){

	m_DLLResultat = 0;	// defaultly OK

	// Initialization of Pointer to all functions
	m_InitController = NULL;
	m_OpenController = NULL;
	m_CloseController = NULL;
	m_ExecuteCommand = NULL;
	m_GetReply = NULL;
	m_RangeMeasure = NULL;
	m_AbortCommand = NULL;
	m_Calibrate = NULL;
	m_GetAcceleration = NULL;
	m_SetAcceleration = NULL;
	m_GetVelocity = NULL;
	m_SetVelocity = NULL;
	m_Identify = NULL;
	m_IsClearBufferEmpty = NULL;
	m_GetStatus = NULL;
	m_GetError = NULL;
	m_GetParamsOnStack = NULL;
	m_ClearParameterStack = NULL;
	m_GetPos = NULL;
	m_MoveAbsolute = NULL;
	m_MoveRelative = NULL;
	m_MoveAbsoluteAutoReply = NULL;
	m_MoveRelativeAutoReply = NULL;
	m_ResetComm = NULL;
	m_JoystickEnable = NULL;
	m_JoystickDisable = NULL;
	m_GetJoystickVelocity = NULL;
	m_SetJoystickVelocity = NULL;
	m_GetAxisMode = NULL;
	m_SetAxisMode = NULL;
	m_SetOrigin = NULL;
	m_PreprocessReply = NULL;
	m_SetClearBufferEmpty = NULL;
	m_SetDecimalSeparator = NULL;
	m_SetSleepWhileWaitingWithoutTimeout = NULL;

	if (IS64Bit == 0){
		hITKVenus = ::LoadLibrary(_T("Wp2Comm.dll"));
		cout << "Wp2Comm.dll";
	}
	else{
		hITKVenus = ::LoadLibrary(_T("Wp2Comm_64.dll"));
		cout << "Wp2Comm_64.dll";
	}
	
	if (hITKVenus == 0)
	{
		m_DLLResultat = -1; // DLL couldn't be loaded
		cout << " Dll couldn't be loaded..." << endl;
	}
	else
	{
		cout << " Dll successfuly loaded..." << endl << endl;

		cout << "DLL functions loading State: (0 = OK, -2 = error function not load)" << endl;

		m_InitController = (PInitController)GetProcAddress(hITKVenus, "InitController");
		if (!m_InitController) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "InitController " << m_DLLResultat << endl;

		m_OpenController = (POpenController)GetProcAddress(hITKVenus, "OpenController");
		if (!m_OpenController) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "OpenController " << m_DLLResultat << endl;

		m_CloseController = (PCloseController)GetProcAddress(hITKVenus, "CloseController");
		if (!m_CloseController) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "CloseController " << m_DLLResultat << endl;

		m_ExecuteCommand = (PExecuteCommand)GetProcAddress(hITKVenus, "ExecuteCommand");
		if (!m_ExecuteCommand) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "ExecuteCommand " << m_DLLResultat << endl;

		m_GetReply = (PGetReply)GetProcAddress(hITKVenus, "GetReply");
		if (!m_GetReply) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetReply " << m_DLLResultat << endl;

		m_RangeMeasure = (PRangeMeasure)GetProcAddress(hITKVenus, "RangeMeasure");
		if (!m_RangeMeasure) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "RangeMeasure " << m_DLLResultat << endl;

		m_AbortCommand = (PAbortCommand)GetProcAddress(hITKVenus, "AbortCommand");
		if (!m_AbortCommand) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "AbortCommand " << m_DLLResultat << endl;

		m_Calibrate = (PAbortCommand)GetProcAddress(hITKVenus, "Calibrate");
		if (!m_Calibrate) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "Calibrate " << m_DLLResultat << endl;

		m_GetAcceleration = (PGetAcceleration)GetProcAddress(hITKVenus, "GetAcceleration");
		if (!m_GetAcceleration) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetAcceleration " << m_DLLResultat << endl;

		m_SetAcceleration = (PSetAcceleration)GetProcAddress(hITKVenus, "SetAcceleration");
		if (!m_SetAcceleration) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetAcceleration " << m_DLLResultat << endl;

		m_GetDllVersion = (PGetDllVersion)GetProcAddress(hITKVenus, "GetDllVersion");
		if (!m_GetDllVersion) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetDllVersion " << m_DLLResultat << endl;

		m_GetVelocity = (PGetVelocity)GetProcAddress(hITKVenus, "GetVelocity");
		if (!m_GetVelocity) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetVelocity " << m_DLLResultat << endl;

		m_SetVelocity = (PSetVelocity)GetProcAddress(hITKVenus, "SetVelocity");
		if (!m_SetVelocity) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetVelocity " << m_DLLResultat << endl;

		m_IsClearBufferEmpty = (PIsClearBufferEmpty)GetProcAddress(hITKVenus, "IsClearBufferEmpty");
		if (!m_IsClearBufferEmpty) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "IsClearBufferEmpty " << m_DLLResultat << endl;

		m_Identify = (PIdentify)GetProcAddress(hITKVenus, "Identify");
		if (!m_Identify) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "Identify " << m_DLLResultat << endl;

		m_GetStatus = (PGetStatus)GetProcAddress(hITKVenus, "GetStatus");
		if (!m_GetStatus) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetStatus " << m_DLLResultat << endl;

		m_GetError = (PGetError)GetProcAddress(hITKVenus, "GetError");
		if (!m_GetError) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetError " << m_DLLResultat << endl;

		m_GetLimits = (PGetLimits)GetProcAddress(hITKVenus, "GetLimits");
		if (!m_GetLimits) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetLimits " << m_DLLResultat << endl;

		m_GetParamsOnStack = (PGetParamsOnStack)GetProcAddress(hITKVenus, "GetParamsOnStack");
		if (!m_GetParamsOnStack) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetParamsOnStack " << m_DLLResultat << endl;

		m_ClearParameterStack = (PClearParameterStack)GetProcAddress(hITKVenus, "ClearParameterStack");
		if (!m_ClearParameterStack) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "ClearParameterStack " << m_DLLResultat << endl;

		m_GetPos = (PGetPos)GetProcAddress(hITKVenus, "GetPos");
		if (!m_GetPos) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetPos " << m_DLLResultat << endl;

		m_MoveAbsolute = (PMoveAbsolute)GetProcAddress(hITKVenus, "MoveAbsolute");
		if (!m_MoveAbsolute) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "MoveAbsolute " << m_DLLResultat << endl;

		m_MoveRelative = (PMoveRelative)GetProcAddress(hITKVenus, "MoveRelative");
		if (!m_MoveRelative) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "MoveRelative " << m_DLLResultat << endl;

		m_MoveAbsoluteAutoReply = (PMoveAbsoluteAutoReply)GetProcAddress(hITKVenus, "MoveAbsoluteAutoReply");
		if (!m_MoveAbsoluteAutoReply) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "MoveAbsoluteAutoReply " << m_DLLResultat << endl;

		m_MoveRelativeAutoReply = (PMoveRelativeAutoReply)GetProcAddress(hITKVenus, "MoveRelativeAutoReply");
		if (!m_MoveRelativeAutoReply) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "MoveRelativeAutoReply " << m_DLLResultat << endl;

		m_ResetComm = (PResetComm)GetProcAddress(hITKVenus, "ResetComm");
		if (!m_ResetComm) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "ResetComm " << m_DLLResultat << endl;

		m_JoystickEnable = (PJoystickEnable)GetProcAddress(hITKVenus, "JoystickEnable");
		if (!m_JoystickEnable) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "JoystickEnable " << m_DLLResultat << endl;

		m_JoystickDisable = (PJoystickDisable)GetProcAddress(hITKVenus, "JoystickDisable");
		if (!m_JoystickDisable) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "JoystickDisable " << m_DLLResultat << endl;

		m_GetJoystickVelocity = (PGetJoystickVelocity)GetProcAddress(hITKVenus, "GetJoystickVelocity");
		if (!m_GetJoystickVelocity) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetJoystickVelocity " << m_DLLResultat << endl;

		m_SetJoystickVelocity = (PSetJoystickVelocity)GetProcAddress(hITKVenus, "SetJoystickVelocity");
		if (!m_SetJoystickVelocity) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetJoystickVelocity " << m_DLLResultat << endl;

		m_GetAxisMode = (PGetAxisMode)GetProcAddress(hITKVenus, "GetAxisMode");
		if (!m_GetAxisMode) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "GetAxisMode " << m_DLLResultat << endl;

		m_SetAxisMode = (PSetAxisMode)GetProcAddress(hITKVenus, "SetAxisMode");
		if (!m_SetAxisMode) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetAxisMode " << m_DLLResultat << endl;

		m_SetOrigin = (PSetOrigin)GetProcAddress(hITKVenus, "SetOrigin");
		if (!m_SetOrigin) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetOrigin " << m_DLLResultat << endl;

		m_PreprocessReply = (PPreprocessReply)GetProcAddress(hITKVenus, "PreprocessReply");
		if (!m_PreprocessReply) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "PreprocessReply " << m_DLLResultat << endl;

		m_SetClearBufferEmpty = (PSetClearBufferEmpty)GetProcAddress(hITKVenus, "SetClearBufferEmpty");
		if (!m_SetClearBufferEmpty) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetClearBufferEmpty " << m_DLLResultat << endl;

		m_SetDecimalSeparator = (PSetDecimalSeparator)GetProcAddress(hITKVenus, "SetDecimalSeparator");
		if (!m_SetDecimalSeparator) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetDecimalSeparator " << m_DLLResultat << endl;

		m_SetSleepWhileWaitingWithoutTimeout = (PSetSleepWhileWaitingWithoutTimeout)GetProcAddress(hITKVenus, "SetSleepWhileWaitingWithoutTimeout");
		if (!m_SetSleepWhileWaitingWithoutTimeout) m_DLLResultat = -2; else m_DLLResultat = 0;
		cout << "SetSleepWhileWaitingWithoutTimeout " << m_DLLResultat << endl;
	}
}

boolean Wp2CommDllLoader::isDllLoaded(){
	return isDllLoad;
}

// Destructor
Wp2CommDllLoader::~Wp2CommDllLoader()
{
	if (hITKVenus != 0)
	{
		FreeLibrary(hITKVenus);
	}
}

/**********************************************************************************************/
// *** Functions of the DLL *******************************************************************/
/**********************************************************************************************/
DWORD Wp2CommDllLoader::InitController(DWORD ControllerMode, DWORD Axes, DWORD ComPort, DWORD Baudrate, HWND UserWin, UINT AsyncMsg, DWORD Mode)
{
	if (m_InitController)
	{
		return m_InitController(ControllerMode, Axes, ComPort, Baudrate, UserWin, AsyncMsg, Mode);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::OpenController()
{
	if (m_OpenController)
	{
		return m_OpenController();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::CloseController()
{
	if (m_CloseController)
	{
		return m_CloseController();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::ExecuteCommand(LPSTR Command, DWORD LinesExpected, LPSTR Reply){
	if (m_ExecuteCommand)
	{
		return m_ExecuteCommand(Command, LinesExpected, Reply);
	}
	else
		return -1;

}
DWORD Wp2CommDllLoader::GetReply(LPSTR Reply){
	if (m_GetReply)
	{
		return m_GetReply(Reply);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::RangeMeasure(){
	if (m_RangeMeasure)
	{
		return m_RangeMeasure();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::AbortCommand(){
	if (m_AbortCommand)
	{
		return m_AbortCommand();
	}
	else
		return -1;
}


DWORD Wp2CommDllLoader::Calibrate(){
	if (m_Calibrate)
	{
		return m_Calibrate();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetAcceleration(LPSTR Accel){
	if (m_GetAcceleration)
	{
		return m_GetAcceleration(Accel);
	}
	else
		return -1;
}


DWORD Wp2CommDllLoader::SetAcceleration(LPSTR Accel){
	if (m_SetAcceleration)
	{
		return m_SetAcceleration(Accel);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetVelocity(LPSTR Vel){
	if (m_GetVelocity)
	{
		return m_GetVelocity(Vel);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetVelocity(LPSTR Vel){
	if (m_SetVelocity)
	{
		return m_SetVelocity(Vel);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::Identify(LPSTR Id){
	if (m_Identify)
	{
		return m_Identify(Id);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::IsClearBufferEmpty(BOOL *IsEmpty){
	if (m_IsClearBufferEmpty)
	{
		return m_IsClearBufferEmpty(IsEmpty);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetStatus(LPDWORD Status){
	if (m_GetStatus)
	{
		return m_GetStatus(Status);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetDllVersion(double *Version){
	if (m_GetDllVersion)
	{
		return m_GetDllVersion(Version);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetError(LPDWORD Error){
	if (m_GetError)
	{
		return m_GetError(Error);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetLimits(LPSTR A1Min, LPSTR A1Max, LPSTR A2Min, LPSTR A2Max, LPSTR A3Min, LPSTR A3Max, LPSTR A4Min, LPSTR A4Max){
	if (m_GetLimits)
	{
		return m_GetLimits(A1Min, A1Max, A2Min, A2Max, A3Min, A3Max, A4Min, A4Max);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetParamsOnStack(LPDWORD Value){
	if (m_GetParamsOnStack)
	{
		return m_GetParamsOnStack(Value);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::ClearParameterStack(){
	if (m_ClearParameterStack)
	{
		return m_ClearParameterStack();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetPos(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos){
	if (m_GetPos)
	{
		return m_GetPos(Axis1Pos, Axis2Pos, Axis3Pos, Axis4Pos);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::MoveAbsolute(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos){
	if (m_MoveAbsolute)
	{
		return m_MoveAbsolute(Axis1Pos, Axis2Pos, Axis3Pos, Axis4Pos);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::MoveRelative(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos){
	if (m_MoveRelative)
	{
		return m_MoveRelative(Axis1Pos, Axis2Pos, Axis3Pos, Axis4Pos);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::MoveAbsoluteAutoReply(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos){
	if (m_MoveAbsoluteAutoReply)
	{
		return m_MoveAbsoluteAutoReply(Axis1Pos, Axis2Pos, Axis3Pos, Axis4Pos);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::MoveRelativeAutoReply(LPSTR Axis1Pos, LPSTR Axis2Pos, LPSTR Axis3Pos, LPSTR Axis4Pos){
	if (m_MoveRelativeAutoReply)
	{
		return m_MoveRelativeAutoReply(Axis1Pos, Axis2Pos, Axis3Pos, Axis4Pos);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::ResetComm(){
	if (m_ResetComm)
	{
		return m_ResetComm();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::JoystickEnable(){
	if (m_JoystickEnable){
		return m_JoystickEnable();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::JoystickDisable(){
	if (m_JoystickDisable){
		return m_JoystickDisable();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetJoystickVelocity(LPSTR JoyVel){
	if (m_GetJoystickVelocity){
		return m_GetJoystickVelocity(JoyVel);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetJoystickVelocity(LPSTR JoyVel){
	if (m_SetJoystickVelocity){
		return m_SetJoystickVelocity(JoyVel);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::GetAxisMode(LPDWORD Axis1Mode, LPDWORD Axis2Mode, LPDWORD Axis3Mode, LPDWORD Axis4Mode){
	if (m_GetAxisMode){
		return m_GetAxisMode(Axis1Mode, Axis2Mode, Axis3Mode, Axis4Mode);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetAxisMode(LPSTR Axis1Mode, LPSTR Axis2Mode, LPSTR Axis3Mode, LPSTR Axis4Mode){
	if (m_SetAxisMode){
		return m_SetAxisMode(Axis1Mode, Axis2Mode, Axis3Mode, Axis4Mode);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetOrigin(){
	if (m_SetOrigin){
		return m_SetOrigin();
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::PreprocessReply(BYTE Active){
	if (m_PreprocessReply){
		return m_PreprocessReply(Active);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetClearBufferEmpty(BOOL ClearBuffer){
	if (m_SetClearBufferEmpty){
		return m_SetClearBufferEmpty(ClearBuffer);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetDecimalSeparator(BYTE DecimalSep){
	if (m_SetDecimalSeparator){
		return m_SetDecimalSeparator(DecimalSep);
	}
	else
		return -1;
}

DWORD Wp2CommDllLoader::SetSleepWhileWaitingWithoutTimeout(DWORD milliseconds){
	if (m_SetSleepWhileWaitingWithoutTimeout){
		return m_SetSleepWhileWaitingWithoutTimeout(milliseconds);
	}
	else
		return -1;
}

