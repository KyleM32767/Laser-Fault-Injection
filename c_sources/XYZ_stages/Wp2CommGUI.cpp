//---------------------------------------------------------------------------
//                              Wp2CommGUI.cpp
//---------------------------------------------------------------------------
//  Copyright (C): ITK Dr. Kassen GmbH, 2015
//---------------------------------------------------------------------------
#include "Wp2CommGUI.h"
#include <iostream>
#using <System.dll>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO::Ports;
using namespace System::ComponentModel;


[STAThread]
void main(array<String^>^ args) {


	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Wp2CommDemo::Wp2CommGUI form;
	Application::Run(%form);
}

