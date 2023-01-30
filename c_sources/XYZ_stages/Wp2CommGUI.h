//---------------------------------------------------------------------------
//                              Wp2CommGUI.h
//---------------------------------------------------------------------------
//  Copyright (C): ITK Dr. Kassen GmbH, 2015
//---------------------------------------------------------------------------
#include "Wp2CommDllLoader.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>

using namespace std;
using msclr::interop::marshal_as;

using namespace std;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO::Ports;
using namespace System::ComponentModel;

#pragma once

bool isnumeric(string st) {
	int len = st.length(), asciiCode, decimal_count = -1, neg_count = -1;
	for (int i = 0; i < len; i++) {
		asciiCode = int(st[i]);
		switch (asciiCode) {
		case 44: // Allow commas. 
			// This will allow them anywhere, so ",,," would return true.
			// Write code here to require commas be every 3 decimal places.
			break;
		case 45: // Allow a negative sign.
			neg_count++;
			if (neg_count || i != 0) {
				return false;
			}
			break;
		case 46: // Allow a decimal point.
			decimal_count++;
			if (decimal_count) {
				return false;
			}
			break;
		default:
			if (asciiCode < 48 || asciiCode > 57) {
				return false;
			}
			break;
		}
	}
	return true;
}

array<String^>^ listComports(){
	array<String^>^ serialPorts = nullptr;
	try
	{
		// Get a list of serial port names.
		serialPorts = SerialPort::GetPortNames();
	}
	catch (Win32Exception^ ex)
	{
		Console::WriteLine(ex->Message);
	}

	Console::WriteLine("The following serial ports were found:");

	// Display each port name to the console.
	for each(String^ port in serialPorts)
	{
		Console::WriteLine(port);
	}
	return serialPorts;
}

namespace Wp2CommDemo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	Wp2CommDllLoader wp2Comm;

	/// <summary>
	/// Zusammenfassung für Wp2CommGUI
	/// </summary>
	public ref class Wp2CommGUI : public System::Windows::Forms::Form
	{
	public:
		Wp2CommGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Wp2CommGUI()
		{
			if (components)
			{
				delete components;
			}
		}
		virtual void WndProc(Message% m) override
		{

			// Listen for operating system messages.
			switch (m.Msg)
			{
			case WMU_ASYNCMSG:

				string y = "";
				char *Reply = &y[0];
				int ret = wp2Comm.GetReply(Reply);
				if (ret == 0){
					string answerstr = Reply;
					String ^ answerStr = marshal_as<String ^>(answerstr);
					textAsyncAnswer->Text = answerStr;
				}
				break;
			}
			Form::WndProc(m);
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::GroupBox^  groupBox9;
	private: System::Windows::Forms::Button^  buttonSetVelocity;

	private: System::Windows::Forms::Button^  buttonGetVelocity;

	private: System::Windows::Forms::TextBox^  textVelocity;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textAcceleration;
	private: System::Windows::Forms::Button^  buttonSetAcceleration;


	private: System::Windows::Forms::Button^  buttonGetAcceleration;

	private: System::Windows::Forms::GroupBox^  groupBox12;
	private: System::Windows::Forms::Button^  buttonClearStack;
	private: System::Windows::Forms::Button^  buttonGetParamsOnStack;
	private: System::Windows::Forms::TextBox^  textParameter;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Button^  buttonGetError;
	private: System::Windows::Forms::Button^  buttonGetStatus;
	private: System::Windows::Forms::Button^  buttonIdentify;
	private: System::Windows::Forms::TextBox^  textError;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textState;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textIdentify;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::GroupBox^  groupBox25;
	private: System::Windows::Forms::Button^  buttonExecute;
	private: System::Windows::Forms::TextBox^  textLines;
	private: System::Windows::Forms::Label^  label60;
	private: System::Windows::Forms::TextBox^  textAnswer;
	private: System::Windows::Forms::Label^  label59;
	private: System::Windows::Forms::TextBox^  textCommand;
	private: System::Windows::Forms::Label^  label58;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkPreprocess;
	private: System::Windows::Forms::Button^  buttonResetComm;
	private: System::Windows::Forms::TextBox^  textAsyncAnswer;
	private: System::Windows::Forms::Label^  label57;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::RadioButton^  radioAsynchron;
	private: System::Windows::Forms::RadioButton^  radioSynchron;
	private: System::Windows::Forms::ComboBox^  comboPort;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboAxes;
	private: System::Windows::Forms::TextBox^  textLastCommand;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboMode;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBaudrate;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  buttonInit;
	private: System::Windows::Forms::Button^  buttonOpenController;
	private: System::Windows::Forms::Button^  buttonCloseController;



	private: System::Windows::Forms::Button^  buttonSetOrigin;
	private: System::Windows::Forms::Button^  buttonAbortCommand;

	private: System::Windows::Forms::GroupBox^  groupBox27;
	private: System::Windows::Forms::Button^  buttonXSetAxisMode;

	private: System::Windows::Forms::Button^  buttonXGetAxisMode;
	private: System::Windows::Forms::ComboBox^  comboZAxisMode;
	private: System::Windows::Forms::ComboBox^  comboYAxisMode;
	private: System::Windows::Forms::ComboBox^  comboXAxisMode;
	private: System::Windows::Forms::Label^  label67;
	private: System::Windows::Forms::Label^  label66;
	private: System::Windows::Forms::Label^  label65;
	private: System::Windows::Forms::GroupBox^  groupBox26;
	private: System::Windows::Forms::Button^  buttonSetJoyVel;
	private: System::Windows::Forms::Button^  buttonGetJoyVel;
	private: System::Windows::Forms::TextBox^  textJoystickVelocity;
	private: System::Windows::Forms::Label^  label61;
	private: System::Windows::Forms::CheckBox^  checkJoystickEnabled;
	private: System::Windows::Forms::GroupBox^  groupBox24;
	private: System::Windows::Forms::CheckBox^  checkMoveRelAutoReply;
	private: System::Windows::Forms::Button^  buttonMoveRel;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Label^  label53;
	private: System::Windows::Forms::Label^  label54;
	private: System::Windows::Forms::Label^  label55;
	private: System::Windows::Forms::Label^  label56;
	private: System::Windows::Forms::TextBox^  textZMoveRel;
	private: System::Windows::Forms::TextBox^  textYMoveRel;
	private: System::Windows::Forms::TextBox^  textXMoveRel;
	private: System::Windows::Forms::GroupBox^  groupBox23;
	private: System::Windows::Forms::Label^  labelMoveAbsState;
	private: System::Windows::Forms::CheckBox^  checkMoveAbsAutoReply;
	private: System::Windows::Forms::Button^  buttonGetPosition;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textZMove;
	private: System::Windows::Forms::TextBox^  textYMove;
	private: System::Windows::Forms::TextBox^  textXMove;
	private: System::Windows::Forms::GroupBox^  groupBox10;
private: System::Windows::Forms::Button^  buttonRangeMeasure;
private: System::Windows::Forms::Button^  buttonCalibrate;


	private: System::Windows::Forms::GroupBox^  groupBox22;
	private: System::Windows::Forms::Button^  buttonGetPos;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textZPos;
	private: System::Windows::Forms::TextBox^  textYPos;
	private: System::Windows::Forms::TextBox^  textXPos;
	private: System::Windows::Forms::GroupBox^  groupBox21;
	private: System::Windows::Forms::Label^  label64;
	private: System::Windows::Forms::Label^  label63;
	private: System::Windows::Forms::Label^  label62;
	private: System::Windows::Forms::Button^  buttonGetLimits;
	private: System::Windows::Forms::TextBox^  textZUpperLimit;
	private: System::Windows::Forms::TextBox^  textZLowerLimit;
	private: System::Windows::Forms::TextBox^  textYUpperLimit;
	private: System::Windows::Forms::TextBox^  textYLowerLimit;
	private: System::Windows::Forms::TextBox^  textXUpperLimit;
	private: System::Windows::Forms::TextBox^  textXLowerLimit;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->buttonSetOrigin = (gcnew System::Windows::Forms::Button());
			this->buttonAbortCommand = (gcnew System::Windows::Forms::Button());
			this->groupBox27 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonXSetAxisMode = (gcnew System::Windows::Forms::Button());
			this->buttonXGetAxisMode = (gcnew System::Windows::Forms::Button());
			this->comboZAxisMode = (gcnew System::Windows::Forms::ComboBox());
			this->comboYAxisMode = (gcnew System::Windows::Forms::ComboBox());
			this->comboXAxisMode = (gcnew System::Windows::Forms::ComboBox());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->groupBox26 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonSetJoyVel = (gcnew System::Windows::Forms::Button());
			this->buttonGetJoyVel = (gcnew System::Windows::Forms::Button());
			this->textJoystickVelocity = (gcnew System::Windows::Forms::TextBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->checkJoystickEnabled = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox24 = (gcnew System::Windows::Forms::GroupBox());
			this->checkMoveRelAutoReply = (gcnew System::Windows::Forms::CheckBox());
			this->buttonMoveRel = (gcnew System::Windows::Forms::Button());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->textZMoveRel = (gcnew System::Windows::Forms::TextBox());
			this->textYMoveRel = (gcnew System::Windows::Forms::TextBox());
			this->textXMoveRel = (gcnew System::Windows::Forms::TextBox());
			this->groupBox23 = (gcnew System::Windows::Forms::GroupBox());
			this->labelMoveAbsState = (gcnew System::Windows::Forms::Label());
			this->checkMoveAbsAutoReply = (gcnew System::Windows::Forms::CheckBox());
			this->buttonGetPosition = (gcnew System::Windows::Forms::Button());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textZMove = (gcnew System::Windows::Forms::TextBox());
			this->textYMove = (gcnew System::Windows::Forms::TextBox());
			this->textXMove = (gcnew System::Windows::Forms::TextBox());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonRangeMeasure = (gcnew System::Windows::Forms::Button());
			this->buttonCalibrate = (gcnew System::Windows::Forms::Button());
			this->groupBox22 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonGetPos = (gcnew System::Windows::Forms::Button());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textZPos = (gcnew System::Windows::Forms::TextBox());
			this->textYPos = (gcnew System::Windows::Forms::TextBox());
			this->textXPos = (gcnew System::Windows::Forms::TextBox());
			this->groupBox21 = (gcnew System::Windows::Forms::GroupBox());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->buttonGetLimits = (gcnew System::Windows::Forms::Button());
			this->textZUpperLimit = (gcnew System::Windows::Forms::TextBox());
			this->textZLowerLimit = (gcnew System::Windows::Forms::TextBox());
			this->textYUpperLimit = (gcnew System::Windows::Forms::TextBox());
			this->textYLowerLimit = (gcnew System::Windows::Forms::TextBox());
			this->textXUpperLimit = (gcnew System::Windows::Forms::TextBox());
			this->textXLowerLimit = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonSetVelocity = (gcnew System::Windows::Forms::Button());
			this->buttonGetVelocity = (gcnew System::Windows::Forms::Button());
			this->textVelocity = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textAcceleration = (gcnew System::Windows::Forms::TextBox());
			this->buttonSetAcceleration = (gcnew System::Windows::Forms::Button());
			this->buttonGetAcceleration = (gcnew System::Windows::Forms::Button());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonClearStack = (gcnew System::Windows::Forms::Button());
			this->buttonGetParamsOnStack = (gcnew System::Windows::Forms::Button());
			this->textParameter = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->buttonGetError = (gcnew System::Windows::Forms::Button());
			this->buttonGetStatus = (gcnew System::Windows::Forms::Button());
			this->buttonIdentify = (gcnew System::Windows::Forms::Button());
			this->textError = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textState = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textIdentify = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox25 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonExecute = (gcnew System::Windows::Forms::Button());
			this->textLines = (gcnew System::Windows::Forms::TextBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->textAnswer = (gcnew System::Windows::Forms::TextBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->textCommand = (gcnew System::Windows::Forms::TextBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkPreprocess = (gcnew System::Windows::Forms::CheckBox());
			this->buttonResetComm = (gcnew System::Windows::Forms::Button());
			this->textAsyncAnswer = (gcnew System::Windows::Forms::TextBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->radioAsynchron = (gcnew System::Windows::Forms::RadioButton());
			this->radioSynchron = (gcnew System::Windows::Forms::RadioButton());
			this->comboPort = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboAxes = (gcnew System::Windows::Forms::ComboBox());
			this->textLastCommand = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboMode = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBaudrate = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonInit = (gcnew System::Windows::Forms::Button());
			this->buttonOpenController = (gcnew System::Windows::Forms::Button());
			this->buttonCloseController = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox27->SuspendLayout();
			this->groupBox26->SuspendLayout();
			this->groupBox24->SuspendLayout();
			this->groupBox23->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox22->SuspendLayout();
			this->groupBox21->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox12->SuspendLayout();
			this->groupBox25->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(923, 508);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->buttonSetOrigin);
			this->tabPage1->Controls->Add(this->buttonAbortCommand);
			this->tabPage1->Controls->Add(this->groupBox27);
			this->tabPage1->Controls->Add(this->groupBox26);
			this->tabPage1->Controls->Add(this->groupBox24);
			this->tabPage1->Controls->Add(this->groupBox23);
			this->tabPage1->Controls->Add(this->groupBox10);
			this->tabPage1->Controls->Add(this->groupBox22);
			this->tabPage1->Controls->Add(this->groupBox21);
			this->tabPage1->Controls->Add(this->groupBox9);
			this->tabPage1->Controls->Add(this->groupBox12);
			this->tabPage1->Controls->Add(this->groupBox25);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(915, 482);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Connection";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// buttonSetOrigin
			// 
			this->buttonSetOrigin->Location = System::Drawing::Point(805, 37);
			this->buttonSetOrigin->Name = L"buttonSetOrigin";
			this->buttonSetOrigin->Size = System::Drawing::Size(100, 23);
			this->buttonSetOrigin->TabIndex = 31;
			this->buttonSetOrigin->Text = L"Set Origin";
			this->buttonSetOrigin->UseVisualStyleBackColor = true;
			this->buttonSetOrigin->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonSetOrigin_Click);
			// 
			// buttonAbortCommand
			// 
			this->buttonAbortCommand->ForeColor = System::Drawing::Color::Red;
			this->buttonAbortCommand->Location = System::Drawing::Point(805, 12);
			this->buttonAbortCommand->Name = L"buttonAbortCommand";
			this->buttonAbortCommand->Size = System::Drawing::Size(100, 23);
			this->buttonAbortCommand->TabIndex = 30;
			this->buttonAbortCommand->Text = L"Abort Command";
			this->buttonAbortCommand->UseVisualStyleBackColor = true;
			this->buttonAbortCommand->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonAbortCommand_Click);
			// 
			// groupBox27
			// 
			this->groupBox27->Controls->Add(this->buttonXSetAxisMode);
			this->groupBox27->Controls->Add(this->buttonXGetAxisMode);
			this->groupBox27->Controls->Add(this->comboZAxisMode);
			this->groupBox27->Controls->Add(this->comboYAxisMode);
			this->groupBox27->Controls->Add(this->comboXAxisMode);
			this->groupBox27->Controls->Add(this->label67);
			this->groupBox27->Controls->Add(this->label66);
			this->groupBox27->Controls->Add(this->label65);
			this->groupBox27->Location = System::Drawing::Point(435, 242);
			this->groupBox27->Name = L"groupBox27";
			this->groupBox27->Size = System::Drawing::Size(307, 52);
			this->groupBox27->TabIndex = 29;
			this->groupBox27->TabStop = false;
			this->groupBox27->Text = L"Axis Mode";
			// 
			// buttonXSetAxisMode
			// 
			this->buttonXSetAxisMode->Location = System::Drawing::Point(261, 15);
			this->buttonXSetAxisMode->Name = L"buttonXSetAxisMode";
			this->buttonXSetAxisMode->Size = System::Drawing::Size(34, 23);
			this->buttonXSetAxisMode->TabIndex = 37;
			this->buttonXSetAxisMode->Text = L"Set";
			this->buttonXSetAxisMode->UseVisualStyleBackColor = true;
			this->buttonXSetAxisMode->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonXSetAxisMode_Click);
			// 
			// buttonXGetAxisMode
			// 
			this->buttonXGetAxisMode->Location = System::Drawing::Point(223, 15);
			this->buttonXGetAxisMode->Name = L"buttonXGetAxisMode";
			this->buttonXGetAxisMode->Size = System::Drawing::Size(34, 23);
			this->buttonXGetAxisMode->TabIndex = 34;
			this->buttonXGetAxisMode->Text = L"Get";
			this->buttonXGetAxisMode->UseVisualStyleBackColor = true;
			this->buttonXGetAxisMode->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonXGetAxisMode_Click);
			// 
			// comboZAxisMode
			// 
			this->comboZAxisMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboZAxisMode->FormattingEnabled = true;
			this->comboZAxisMode->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0", L"1", L"2", L"3", L"4" });
			this->comboZAxisMode->Location = System::Drawing::Point(166, 17);
			this->comboZAxisMode->Name = L"comboZAxisMode";
			this->comboZAxisMode->Size = System::Drawing::Size(42, 21);
			this->comboZAxisMode->TabIndex = 32;
			// 
			// comboYAxisMode
			// 
			this->comboYAxisMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboYAxisMode->FormattingEnabled = true;
			this->comboYAxisMode->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0", L"1", L"2", L"3", L"4" });
			this->comboYAxisMode->Location = System::Drawing::Point(101, 17);
			this->comboYAxisMode->Name = L"comboYAxisMode";
			this->comboYAxisMode->Size = System::Drawing::Size(42, 21);
			this->comboYAxisMode->TabIndex = 31;
			// 
			// comboXAxisMode
			// 
			this->comboXAxisMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboXAxisMode->FormattingEnabled = true;
			this->comboXAxisMode->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0", L"1", L"2", L"3", L"4" });
			this->comboXAxisMode->Location = System::Drawing::Point(30, 18);
			this->comboXAxisMode->Name = L"comboXAxisMode";
			this->comboXAxisMode->Size = System::Drawing::Size(42, 21);
			this->comboXAxisMode->TabIndex = 30;
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(149, 21);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(17, 13);
			this->label67->TabIndex = 29;
			this->label67->Text = L"Z:";
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(78, 21);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(17, 13);
			this->label66->TabIndex = 28;
			this->label66->Text = L"Y:";
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(6, 20);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(17, 13);
			this->label65->TabIndex = 27;
			this->label65->Text = L"X:";
			// 
			// groupBox26
			// 
			this->groupBox26->Controls->Add(this->buttonSetJoyVel);
			this->groupBox26->Controls->Add(this->buttonGetJoyVel);
			this->groupBox26->Controls->Add(this->textJoystickVelocity);
			this->groupBox26->Controls->Add(this->label61);
			this->groupBox26->Controls->Add(this->checkJoystickEnabled);
			this->groupBox26->Location = System::Drawing::Point(491, 146);
			this->groupBox26->Name = L"groupBox26";
			this->groupBox26->Size = System::Drawing::Size(308, 90);
			this->groupBox26->TabIndex = 28;
			this->groupBox26->TabStop = false;
			this->groupBox26->Text = L"Joystick";
			// 
			// buttonSetJoyVel
			// 
			this->buttonSetJoyVel->Location = System::Drawing::Point(210, 44);
			this->buttonSetJoyVel->Name = L"buttonSetJoyVel";
			this->buttonSetJoyVel->Size = System::Drawing::Size(34, 23);
			this->buttonSetJoyVel->TabIndex = 34;
			this->buttonSetJoyVel->Text = L"Set";
			this->buttonSetJoyVel->UseVisualStyleBackColor = true;
			this->buttonSetJoyVel->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonSetJoyVel_Click);
			// 
			// buttonGetJoyVel
			// 
			this->buttonGetJoyVel->Location = System::Drawing::Point(174, 44);
			this->buttonGetJoyVel->Name = L"buttonGetJoyVel";
			this->buttonGetJoyVel->Size = System::Drawing::Size(34, 23);
			this->buttonGetJoyVel->TabIndex = 33;
			this->buttonGetJoyVel->Text = L"Get";
			this->buttonGetJoyVel->UseVisualStyleBackColor = true;
			this->buttonGetJoyVel->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetJoyVel_Click);
			// 
			// textJoystickVelocity
			// 
			this->textJoystickVelocity->Location = System::Drawing::Point(59, 46);
			this->textJoystickVelocity->Name = L"textJoystickVelocity";
			this->textJoystickVelocity->Size = System::Drawing::Size(109, 20);
			this->textJoystickVelocity->TabIndex = 13;
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(6, 46);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(47, 13);
			this->label61->TabIndex = 12;
			this->label61->Text = L"Velocity:";
			// 
			// checkJoystickEnabled
			// 
			this->checkJoystickEnabled->AutoSize = true;
			this->checkJoystickEnabled->Location = System::Drawing::Point(7, 23);
			this->checkJoystickEnabled->Name = L"checkJoystickEnabled";
			this->checkJoystickEnabled->Size = System::Drawing::Size(65, 17);
			this->checkJoystickEnabled->TabIndex = 0;
			this->checkJoystickEnabled->Text = L"Enabled";
			this->checkJoystickEnabled->UseVisualStyleBackColor = true;
			this->checkJoystickEnabled->CheckedChanged += gcnew System::EventHandler(this, &Wp2CommGUI::checkJoystickEnabled_CheckedChanged);
			// 
			// groupBox24
			// 
			this->groupBox24->Controls->Add(this->checkMoveRelAutoReply);
			this->groupBox24->Controls->Add(this->buttonMoveRel);
			this->groupBox24->Controls->Add(this->label31);
			this->groupBox24->Controls->Add(this->label32);
			this->groupBox24->Controls->Add(this->label53);
			this->groupBox24->Controls->Add(this->label54);
			this->groupBox24->Controls->Add(this->label55);
			this->groupBox24->Controls->Add(this->label56);
			this->groupBox24->Controls->Add(this->textZMoveRel);
			this->groupBox24->Controls->Add(this->textYMoveRel);
			this->groupBox24->Controls->Add(this->textXMoveRel);
			this->groupBox24->Location = System::Drawing::Point(603, 300);
			this->groupBox24->Name = L"groupBox24";
			this->groupBox24->Size = System::Drawing::Size(139, 171);
			this->groupBox24->TabIndex = 27;
			this->groupBox24->TabStop = false;
			this->groupBox24->Text = L"Move Relative";
			// 
			// checkMoveRelAutoReply
			// 
			this->checkMoveRelAutoReply->AutoSize = true;
			this->checkMoveRelAutoReply->Location = System::Drawing::Point(11, 97);
			this->checkMoveRelAutoReply->Name = L"checkMoveRelAutoReply";
			this->checkMoveRelAutoReply->Size = System::Drawing::Size(78, 17);
			this->checkMoveRelAutoReply->TabIndex = 52;
			this->checkMoveRelAutoReply->Text = L"Auto Reply";
			this->checkMoveRelAutoReply->UseVisualStyleBackColor = true;
			this->checkMoveRelAutoReply->CheckedChanged += gcnew System::EventHandler(this, &Wp2CommGUI::checkMoveRelAutoReply_CheckedChanged);
			// 
			// buttonMoveRel
			// 
			this->buttonMoveRel->Location = System::Drawing::Point(27, 135);
			this->buttonMoveRel->Name = L"buttonMoveRel";
			this->buttonMoveRel->Size = System::Drawing::Size(100, 23);
			this->buttonMoveRel->TabIndex = 51;
			this->buttonMoveRel->Text = L"Move Relative";
			this->buttonMoveRel->UseVisualStyleBackColor = true;
			this->buttonMoveRel->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonMoveRel_Click);
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(112, 68);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(23, 13);
			this->label31->TabIndex = 50;
			this->label31->Text = L"mm";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(112, 46);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(23, 13);
			this->label32->TabIndex = 49;
			this->label32->Text = L"mm";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(112, 23);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(23, 13);
			this->label53->TabIndex = 48;
			this->label53->Text = L"mm";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(8, 68);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(17, 13);
			this->label54->TabIndex = 47;
			this->label54->Text = L"Z:";
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(8, 46);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(17, 13);
			this->label55->TabIndex = 46;
			this->label55->Text = L"Y:";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(8, 23);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(17, 13);
			this->label56->TabIndex = 45;
			this->label56->Text = L"X:";
			// 
			// textZMoveRel
			// 
			this->textZMoveRel->Location = System::Drawing::Point(27, 65);
			this->textZMoveRel->Name = L"textZMoveRel";
			this->textZMoveRel->Size = System::Drawing::Size(79, 20);
			this->textZMoveRel->TabIndex = 44;
			this->textZMoveRel->Text = L"1,000000";
			// 
			// textYMoveRel
			// 
			this->textYMoveRel->Location = System::Drawing::Point(27, 42);
			this->textYMoveRel->Name = L"textYMoveRel";
			this->textYMoveRel->Size = System::Drawing::Size(79, 20);
			this->textYMoveRel->TabIndex = 43;
			this->textYMoveRel->Text = L"1,000000";
			// 
			// textXMoveRel
			// 
			this->textXMoveRel->Location = System::Drawing::Point(27, 19);
			this->textXMoveRel->Name = L"textXMoveRel";
			this->textXMoveRel->Size = System::Drawing::Size(79, 20);
			this->textXMoveRel->TabIndex = 42;
			this->textXMoveRel->Text = L"1,000000";
			// 
			// groupBox23
			// 
			this->groupBox23->Controls->Add(this->labelMoveAbsState);
			this->groupBox23->Controls->Add(this->checkMoveAbsAutoReply);
			this->groupBox23->Controls->Add(this->buttonGetPosition);
			this->groupBox23->Controls->Add(this->label25);
			this->groupBox23->Controls->Add(this->label26);
			this->groupBox23->Controls->Add(this->label27);
			this->groupBox23->Controls->Add(this->label28);
			this->groupBox23->Controls->Add(this->label29);
			this->groupBox23->Controls->Add(this->label30);
			this->groupBox23->Controls->Add(this->textZMove);
			this->groupBox23->Controls->Add(this->textYMove);
			this->groupBox23->Controls->Add(this->textXMove);
			this->groupBox23->Location = System::Drawing::Point(435, 300);
			this->groupBox23->Name = L"groupBox23";
			this->groupBox23->Size = System::Drawing::Size(154, 171);
			this->groupBox23->TabIndex = 26;
			this->groupBox23->TabStop = false;
			this->groupBox23->Text = L"Move Absolute";
			// 
			// labelMoveAbsState
			// 
			this->labelMoveAbsState->AutoSize = true;
			this->labelMoveAbsState->Location = System::Drawing::Point(6, 117);
			this->labelMoveAbsState->Name = L"labelMoveAbsState";
			this->labelMoveAbsState->Size = System::Drawing::Size(0, 13);
			this->labelMoveAbsState->TabIndex = 43;
			// 
			// checkMoveAbsAutoReply
			// 
			this->checkMoveAbsAutoReply->AutoSize = true;
			this->checkMoveAbsAutoReply->Location = System::Drawing::Point(6, 97);
			this->checkMoveAbsAutoReply->Name = L"checkMoveAbsAutoReply";
			this->checkMoveAbsAutoReply->Size = System::Drawing::Size(78, 17);
			this->checkMoveAbsAutoReply->TabIndex = 42;
			this->checkMoveAbsAutoReply->Text = L"Auto Reply";
			this->checkMoveAbsAutoReply->UseVisualStyleBackColor = true;
			// 
			// buttonGetPosition
			// 
			this->buttonGetPosition->Location = System::Drawing::Point(24, 138);
			this->buttonGetPosition->Name = L"buttonGetPosition";
			this->buttonGetPosition->Size = System::Drawing::Size(100, 23);
			this->buttonGetPosition->TabIndex = 32;
			this->buttonGetPosition->Text = L"Move";
			this->buttonGetPosition->UseVisualStyleBackColor = true;
			this->buttonGetPosition->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetPosition_Click);
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(125, 68);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(23, 13);
			this->label25->TabIndex = 41;
			this->label25->Text = L"mm";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(125, 45);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(23, 13);
			this->label26->TabIndex = 40;
			this->label26->Text = L"mm";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(125, 23);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(23, 13);
			this->label27->TabIndex = 39;
			this->label27->Text = L"mm";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(6, 68);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(17, 13);
			this->label28->TabIndex = 38;
			this->label28->Text = L"Z:";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(6, 46);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(17, 13);
			this->label29->TabIndex = 37;
			this->label29->Text = L"Y:";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(6, 23);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(17, 13);
			this->label30->TabIndex = 36;
			this->label30->Text = L"X:";
			// 
			// textZMove
			// 
			this->textZMove->Location = System::Drawing::Point(25, 65);
			this->textZMove->Name = L"textZMove";
			this->textZMove->Size = System::Drawing::Size(99, 20);
			this->textZMove->TabIndex = 35;
			this->textZMove->Text = L"0,000000";
			// 
			// textYMove
			// 
			this->textYMove->Location = System::Drawing::Point(25, 42);
			this->textYMove->Name = L"textYMove";
			this->textYMove->Size = System::Drawing::Size(99, 20);
			this->textYMove->TabIndex = 34;
			this->textYMove->Text = L"0,000000";
			// 
			// textXMove
			// 
			this->textXMove->Location = System::Drawing::Point(25, 19);
			this->textXMove->Name = L"textXMove";
			this->textXMove->Size = System::Drawing::Size(99, 20);
			this->textXMove->TabIndex = 33;
			this->textXMove->Text = L"0,000000";
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->buttonRangeMeasure);
			this->groupBox10->Controls->Add(this->buttonCalibrate);
			this->groupBox10->Location = System::Drawing::Point(751, 242);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(154, 98);
			this->groupBox10->TabIndex = 25;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Calibrate, Range Measure";
			// 
			// buttonRangeMeasure
			// 
			this->buttonRangeMeasure->Location = System::Drawing::Point(27, 19);
			this->buttonRangeMeasure->Name = L"buttonRangeMeasure";
			this->buttonRangeMeasure->Size = System::Drawing::Size(100, 23);
			this->buttonRangeMeasure->TabIndex = 4;
			this->buttonRangeMeasure->Text = L"Range Measure";
			this->buttonRangeMeasure->UseVisualStyleBackColor = true;
			this->buttonRangeMeasure->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonRangeMeasure_Click);
			// 
			// buttonCalibrate
			// 
			this->buttonCalibrate->Location = System::Drawing::Point(27, 43);
			this->buttonCalibrate->Name = L"buttonCalibrate";
			this->buttonCalibrate->Size = System::Drawing::Size(100, 23);
			this->buttonCalibrate->TabIndex = 6;
			this->buttonCalibrate->Text = L"Calibrate";
			this->buttonCalibrate->UseVisualStyleBackColor = true;
			this->buttonCalibrate->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonCalibrate_Click);
			// 
			// groupBox22
			// 
			this->groupBox22->Controls->Add(this->buttonGetPos);
			this->groupBox22->Controls->Add(this->label24);
			this->groupBox22->Controls->Add(this->label23);
			this->groupBox22->Controls->Add(this->label22);
			this->groupBox22->Controls->Add(this->label21);
			this->groupBox22->Controls->Add(this->label20);
			this->groupBox22->Controls->Add(this->label19);
			this->groupBox22->Controls->Add(this->textZPos);
			this->groupBox22->Controls->Add(this->textYPos);
			this->groupBox22->Controls->Add(this->textXPos);
			this->groupBox22->Location = System::Drawing::Point(751, 346);
			this->groupBox22->Name = L"groupBox22";
			this->groupBox22->Size = System::Drawing::Size(156, 125);
			this->groupBox22->TabIndex = 24;
			this->groupBox22->TabStop = false;
			this->groupBox22->Text = L"Position";
			// 
			// buttonGetPos
			// 
			this->buttonGetPos->Location = System::Drawing::Point(26, 90);
			this->buttonGetPos->Name = L"buttonGetPos";
			this->buttonGetPos->Size = System::Drawing::Size(100, 23);
			this->buttonGetPos->TabIndex = 17;
			this->buttonGetPos->Text = L"Get Position";
			this->buttonGetPos->UseVisualStyleBackColor = true;
			this->buttonGetPos->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetPos_Click);
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(131, 67);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(23, 13);
			this->label24->TabIndex = 31;
			this->label24->Text = L"mm";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(131, 44);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(23, 13);
			this->label23->TabIndex = 30;
			this->label23->Text = L"mm";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(131, 25);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(23, 13);
			this->label22->TabIndex = 29;
			this->label22->Text = L"mm";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(5, 67);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(17, 13);
			this->label21->TabIndex = 28;
			this->label21->Text = L"Z:";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(5, 44);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(17, 13);
			this->label20->TabIndex = 27;
			this->label20->Text = L"Y:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(3, 22);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(17, 13);
			this->label19->TabIndex = 26;
			this->label19->Text = L"X:";
			// 
			// textZPos
			// 
			this->textZPos->Enabled = false;
			this->textZPos->Location = System::Drawing::Point(26, 64);
			this->textZPos->Name = L"textZPos";
			this->textZPos->Size = System::Drawing::Size(100, 20);
			this->textZPos->TabIndex = 25;
			// 
			// textYPos
			// 
			this->textYPos->Enabled = false;
			this->textYPos->Location = System::Drawing::Point(26, 41);
			this->textYPos->Name = L"textYPos";
			this->textYPos->Size = System::Drawing::Size(100, 20);
			this->textYPos->TabIndex = 24;
			// 
			// textXPos
			// 
			this->textXPos->Enabled = false;
			this->textXPos->Location = System::Drawing::Point(26, 18);
			this->textXPos->Name = L"textXPos";
			this->textXPos->Size = System::Drawing::Size(100, 20);
			this->textXPos->TabIndex = 23;
			// 
			// groupBox21
			// 
			this->groupBox21->Controls->Add(this->label64);
			this->groupBox21->Controls->Add(this->label63);
			this->groupBox21->Controls->Add(this->label62);
			this->groupBox21->Controls->Add(this->buttonGetLimits);
			this->groupBox21->Controls->Add(this->textZUpperLimit);
			this->groupBox21->Controls->Add(this->textZLowerLimit);
			this->groupBox21->Controls->Add(this->textYUpperLimit);
			this->groupBox21->Controls->Add(this->textYLowerLimit);
			this->groupBox21->Controls->Add(this->textXUpperLimit);
			this->groupBox21->Controls->Add(this->textXLowerLimit);
			this->groupBox21->Controls->Add(this->label17);
			this->groupBox21->Controls->Add(this->label14);
			this->groupBox21->Controls->Add(this->label13);
			this->groupBox21->Controls->Add(this->label12);
			this->groupBox21->Controls->Add(this->label11);
			this->groupBox21->Location = System::Drawing::Point(491, 6);
			this->groupBox21->Name = L"groupBox21";
			this->groupBox21->Size = System::Drawing::Size(308, 134);
			this->groupBox21->TabIndex = 23;
			this->groupBox21->TabStop = false;
			this->groupBox21->Text = L"Motion Limits";
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->Location = System::Drawing::Point(279, 79);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(23, 13);
			this->label64->TabIndex = 32;
			this->label64->Text = L"mm";
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(279, 57);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(23, 13);
			this->label63->TabIndex = 31;
			this->label63->Text = L"mm";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(279, 35);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(23, 13);
			this->label62->TabIndex = 30;
			this->label62->Text = L"mm";
			// 
			// buttonGetLimits
			// 
			this->buttonGetLimits->Location = System::Drawing::Point(108, 102);
			this->buttonGetLimits->Name = L"buttonGetLimits";
			this->buttonGetLimits->Size = System::Drawing::Size(100, 23);
			this->buttonGetLimits->TabIndex = 16;
			this->buttonGetLimits->Text = L"Get Limits";
			this->buttonGetLimits->UseVisualStyleBackColor = true;
			this->buttonGetLimits->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetLimits_Click);
			// 
			// textZUpperLimit
			// 
			this->textZUpperLimit->Enabled = false;
			this->textZUpperLimit->Location = System::Drawing::Point(158, 76);
			this->textZUpperLimit->Name = L"textZUpperLimit";
			this->textZUpperLimit->Size = System::Drawing::Size(117, 20);
			this->textZUpperLimit->TabIndex = 23;
			// 
			// textZLowerLimit
			// 
			this->textZLowerLimit->Enabled = false;
			this->textZLowerLimit->Location = System::Drawing::Point(38, 76);
			this->textZLowerLimit->Name = L"textZLowerLimit";
			this->textZLowerLimit->Size = System::Drawing::Size(117, 20);
			this->textZLowerLimit->TabIndex = 22;
			// 
			// textYUpperLimit
			// 
			this->textYUpperLimit->Enabled = false;
			this->textYUpperLimit->Location = System::Drawing::Point(158, 54);
			this->textYUpperLimit->Name = L"textYUpperLimit";
			this->textYUpperLimit->Size = System::Drawing::Size(117, 20);
			this->textYUpperLimit->TabIndex = 21;
			// 
			// textYLowerLimit
			// 
			this->textYLowerLimit->Enabled = false;
			this->textYLowerLimit->Location = System::Drawing::Point(38, 54);
			this->textYLowerLimit->Name = L"textYLowerLimit";
			this->textYLowerLimit->Size = System::Drawing::Size(117, 20);
			this->textYLowerLimit->TabIndex = 20;
			// 
			// textXUpperLimit
			// 
			this->textXUpperLimit->Enabled = false;
			this->textXUpperLimit->Location = System::Drawing::Point(158, 32);
			this->textXUpperLimit->Name = L"textXUpperLimit";
			this->textXUpperLimit->Size = System::Drawing::Size(117, 20);
			this->textXUpperLimit->TabIndex = 19;
			// 
			// textXLowerLimit
			// 
			this->textXLowerLimit->Enabled = false;
			this->textXLowerLimit->Location = System::Drawing::Point(38, 32);
			this->textXLowerLimit->Name = L"textXLowerLimit";
			this->textXLowerLimit->Size = System::Drawing::Size(117, 20);
			this->textXLowerLimit->TabIndex = 16;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 79);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(17, 13);
			this->label17->TabIndex = 18;
			this->label17->Text = L"Z:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 57);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(17, 13);
			this->label14->TabIndex = 17;
			this->label14->Text = L"Y:";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 35);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(17, 13);
			this->label13->TabIndex = 16;
			this->label13->Text = L"X:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(183, 16);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(63, 13);
			this->label12->TabIndex = 10;
			this->label12->Text = L"Upper Limit:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(64, 16);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(63, 13);
			this->label11->TabIndex = 9;
			this->label11->Text = L"Lower Limit:";
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->buttonSetVelocity);
			this->groupBox9->Controls->Add(this->buttonGetVelocity);
			this->groupBox9->Controls->Add(this->textVelocity);
			this->groupBox9->Controls->Add(this->label7);
			this->groupBox9->Controls->Add(this->label6);
			this->groupBox9->Controls->Add(this->textAcceleration);
			this->groupBox9->Controls->Add(this->buttonSetAcceleration);
			this->groupBox9->Controls->Add(this->buttonGetAcceleration);
			this->groupBox9->Location = System::Drawing::Point(6, 396);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(422, 75);
			this->groupBox9->TabIndex = 22;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Velocity, Acceleration";
			// 
			// buttonSetVelocity
			// 
			this->buttonSetVelocity->Location = System::Drawing::Point(314, 39);
			this->buttonSetVelocity->Name = L"buttonSetVelocity";
			this->buttonSetVelocity->Size = System::Drawing::Size(100, 23);
			this->buttonSetVelocity->TabIndex = 14;
			this->buttonSetVelocity->Text = L"Set Velocity";
			this->buttonSetVelocity->UseVisualStyleBackColor = true;
			this->buttonSetVelocity->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonSetVelocity_Click);
			// 
			// buttonGetVelocity
			// 
			this->buttonGetVelocity->Location = System::Drawing::Point(208, 40);
			this->buttonGetVelocity->Name = L"buttonGetVelocity";
			this->buttonGetVelocity->Size = System::Drawing::Size(100, 23);
			this->buttonGetVelocity->TabIndex = 13;
			this->buttonGetVelocity->Text = L"Get Velocity";
			this->buttonGetVelocity->UseVisualStyleBackColor = true;
			this->buttonGetVelocity->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetVelocity_Click);
			// 
			// textVelocity
			// 
			this->textVelocity->Location = System::Drawing::Point(85, 42);
			this->textVelocity->Name = L"textVelocity";
			this->textVelocity->Size = System::Drawing::Size(117, 20);
			this->textVelocity->TabIndex = 12;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(10, 45);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(47, 13);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Velocity:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Acceleration:";
			// 
			// textAcceleration
			// 
			this->textAcceleration->Location = System::Drawing::Point(85, 19);
			this->textAcceleration->Name = L"textAcceleration";
			this->textAcceleration->Size = System::Drawing::Size(117, 20);
			this->textAcceleration->TabIndex = 8;
			// 
			// buttonSetAcceleration
			// 
			this->buttonSetAcceleration->Location = System::Drawing::Point(314, 16);
			this->buttonSetAcceleration->Name = L"buttonSetAcceleration";
			this->buttonSetAcceleration->Size = System::Drawing::Size(100, 23);
			this->buttonSetAcceleration->TabIndex = 10;
			this->buttonSetAcceleration->Text = L"Set Acceleration";
			this->buttonSetAcceleration->UseVisualStyleBackColor = true;
			this->buttonSetAcceleration->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonSetAcceleration_Click);
			// 
			// buttonGetAcceleration
			// 
			this->buttonGetAcceleration->Location = System::Drawing::Point(208, 16);
			this->buttonGetAcceleration->Name = L"buttonGetAcceleration";
			this->buttonGetAcceleration->Size = System::Drawing::Size(100, 23);
			this->buttonGetAcceleration->TabIndex = 9;
			this->buttonGetAcceleration->Text = L"Get Acceleration";
			this->buttonGetAcceleration->UseVisualStyleBackColor = true;
			this->buttonGetAcceleration->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetAcceleration_Click);
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->buttonClearStack);
			this->groupBox12->Controls->Add(this->buttonGetParamsOnStack);
			this->groupBox12->Controls->Add(this->textParameter);
			this->groupBox12->Controls->Add(this->label18);
			this->groupBox12->Controls->Add(this->buttonGetError);
			this->groupBox12->Controls->Add(this->buttonGetStatus);
			this->groupBox12->Controls->Add(this->buttonIdentify);
			this->groupBox12->Controls->Add(this->textError);
			this->groupBox12->Controls->Add(this->label10);
			this->groupBox12->Controls->Add(this->textState);
			this->groupBox12->Controls->Add(this->label9);
			this->groupBox12->Controls->Add(this->textIdentify);
			this->groupBox12->Controls->Add(this->label8);
			this->groupBox12->Location = System::Drawing::Point(6, 272);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(422, 118);
			this->groupBox12->TabIndex = 21;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Information";
			// 
			// buttonClearStack
			// 
			this->buttonClearStack->Location = System::Drawing::Point(312, 79);
			this->buttonClearStack->Name = L"buttonClearStack";
			this->buttonClearStack->Size = System::Drawing::Size(100, 23);
			this->buttonClearStack->TabIndex = 26;
			this->buttonClearStack->Text = L"Clear Stack";
			this->buttonClearStack->UseVisualStyleBackColor = true;
			this->buttonClearStack->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonClearStack_Click);
			// 
			// buttonGetParamsOnStack
			// 
			this->buttonGetParamsOnStack->Location = System::Drawing::Point(153, 79);
			this->buttonGetParamsOnStack->Name = L"buttonGetParamsOnStack";
			this->buttonGetParamsOnStack->Size = System::Drawing::Size(155, 23);
			this->buttonGetParamsOnStack->TabIndex = 25;
			this->buttonGetParamsOnStack->Text = L"Get Parameter On Stack";
			this->buttonGetParamsOnStack->UseVisualStyleBackColor = true;
			this->buttonGetParamsOnStack->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetParamsOnStack_Click);
			// 
			// textParameter
			// 
			this->textParameter->Enabled = false;
			this->textParameter->Location = System::Drawing::Point(63, 81);
			this->textParameter->Name = L"textParameter";
			this->textParameter->Size = System::Drawing::Size(89, 20);
			this->textParameter->TabIndex = 24;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(4, 84);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(58, 13);
			this->label18->TabIndex = 23;
			this->label18->Text = L"Parameter:";
			// 
			// buttonGetError
			// 
			this->buttonGetError->Location = System::Drawing::Point(342, 44);
			this->buttonGetError->Name = L"buttonGetError";
			this->buttonGetError->Size = System::Drawing::Size(70, 23);
			this->buttonGetError->TabIndex = 22;
			this->buttonGetError->Text = L"Get Error";
			this->buttonGetError->UseVisualStyleBackColor = true;
			this->buttonGetError->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetError_Click);
			// 
			// buttonGetStatus
			// 
			this->buttonGetStatus->Location = System::Drawing::Point(153, 44);
			this->buttonGetStatus->Name = L"buttonGetStatus";
			this->buttonGetStatus->Size = System::Drawing::Size(70, 23);
			this->buttonGetStatus->TabIndex = 21;
			this->buttonGetStatus->Text = L"Get Status";
			this->buttonGetStatus->UseVisualStyleBackColor = true;
			this->buttonGetStatus->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonGetStatus_Click);
			// 
			// buttonIdentify
			// 
			this->buttonIdentify->Location = System::Drawing::Point(312, 17);
			this->buttonIdentify->Name = L"buttonIdentify";
			this->buttonIdentify->Size = System::Drawing::Size(100, 23);
			this->buttonIdentify->TabIndex = 20;
			this->buttonIdentify->Text = L"Identify";
			this->buttonIdentify->UseVisualStyleBackColor = true;
			this->buttonIdentify->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonIdentify_Click);
			// 
			// textError
			// 
			this->textError->Enabled = false;
			this->textError->Location = System::Drawing::Point(264, 45);
			this->textError->Name = L"textError";
			this->textError->Size = System::Drawing::Size(78, 20);
			this->textError->TabIndex = 19;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(226, 48);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(32, 13);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Error:";
			// 
			// textState
			// 
			this->textState->Enabled = false;
			this->textState->Location = System::Drawing::Point(63, 46);
			this->textState->Name = L"textState";
			this->textState->Size = System::Drawing::Size(89, 20);
			this->textState->TabIndex = 17;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(4, 49);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 13);
			this->label9->TabIndex = 16;
			this->label9->Text = L"State:";
			// 
			// textIdentify
			// 
			this->textIdentify->Enabled = false;
			this->textIdentify->Location = System::Drawing::Point(63, 19);
			this->textIdentify->Name = L"textIdentify";
			this->textIdentify->Size = System::Drawing::Size(243, 20);
			this->textIdentify->TabIndex = 15;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 22);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(44, 13);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Identify:";
			// 
			// groupBox25
			// 
			this->groupBox25->Controls->Add(this->buttonExecute);
			this->groupBox25->Controls->Add(this->textLines);
			this->groupBox25->Controls->Add(this->label60);
			this->groupBox25->Controls->Add(this->textAnswer);
			this->groupBox25->Controls->Add(this->label59);
			this->groupBox25->Controls->Add(this->textCommand);
			this->groupBox25->Controls->Add(this->label58);
			this->groupBox25->Location = System::Drawing::Point(6, 193);
			this->groupBox25->Name = L"groupBox25";
			this->groupBox25->Size = System::Drawing::Size(422, 73);
			this->groupBox25->TabIndex = 20;
			this->groupBox25->TabStop = false;
			this->groupBox25->Text = L"Execute Command";
			// 
			// buttonExecute
			// 
			this->buttonExecute->Location = System::Drawing::Point(102, 40);
			this->buttonExecute->Name = L"buttonExecute";
			this->buttonExecute->Size = System::Drawing::Size(100, 23);
			this->buttonExecute->TabIndex = 25;
			this->buttonExecute->Text = L"Execute";
			this->buttonExecute->UseVisualStyleBackColor = true;
			this->buttonExecute->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonExecute_Click);
			// 
			// textLines
			// 
			this->textLines->Location = System::Drawing::Point(63, 42);
			this->textLines->Name = L"textLines";
			this->textLines->Size = System::Drawing::Size(33, 20);
			this->textLines->TabIndex = 24;
			this->textLines->Text = L"1";
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(10, 45);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(35, 13);
			this->label60->TabIndex = 23;
			this->label60->Text = L"Lines:";
			// 
			// textAnswer
			// 
			this->textAnswer->Enabled = false;
			this->textAnswer->Location = System::Drawing::Point(252, 14);
			this->textAnswer->Multiline = true;
			this->textAnswer->Name = L"textAnswer";
			this->textAnswer->Size = System::Drawing::Size(160, 48);
			this->textAnswer->TabIndex = 22;
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(208, 17);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(45, 13);
			this->label59->TabIndex = 21;
			this->label59->Text = L"Answer:";
			// 
			// textCommand
			// 
			this->textCommand->Location = System::Drawing::Point(63, 14);
			this->textCommand->Name = L"textCommand";
			this->textCommand->Size = System::Drawing::Size(139, 20);
			this->textCommand->TabIndex = 20;
			this->textCommand->Text = L"p";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(6, 17);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(57, 13);
			this->label58->TabIndex = 14;
			this->label58->Text = L"Command:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkPreprocess);
			this->groupBox1->Controls->Add(this->buttonResetComm);
			this->groupBox1->Controls->Add(this->textAsyncAnswer);
			this->groupBox1->Controls->Add(this->label57);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->radioAsynchron);
			this->groupBox1->Controls->Add(this->radioSynchron);
			this->groupBox1->Controls->Add(this->comboPort);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->comboAxes);
			this->groupBox1->Controls->Add(this->textLastCommand);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->comboMode);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->comboBaudrate);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->buttonInit);
			this->groupBox1->Controls->Add(this->buttonOpenController);
			this->groupBox1->Controls->Add(this->buttonCloseController);
			this->groupBox1->Location = System::Drawing::Point(6, 6);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(479, 181);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Connection";
			// 
			// checkPreprocess
			// 
			this->checkPreprocess->AutoSize = true;
			this->checkPreprocess->Checked = true;
			this->checkPreprocess->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkPreprocess->Location = System::Drawing::Point(258, 75);
			this->checkPreprocess->Name = L"checkPreprocess";
			this->checkPreprocess->Size = System::Drawing::Size(109, 17);
			this->checkPreprocess->TabIndex = 17;
			this->checkPreprocess->Text = L"Preprocess Reply";
			this->checkPreprocess->UseVisualStyleBackColor = true;
			this->checkPreprocess->CheckedChanged += gcnew System::EventHandler(this, &Wp2CommGUI::checkPreprocess_CheckedChanged);
			// 
			// buttonResetComm
			// 
			this->buttonResetComm->Location = System::Drawing::Point(373, 88);
			this->buttonResetComm->Name = L"buttonResetComm";
			this->buttonResetComm->Size = System::Drawing::Size(100, 23);
			this->buttonResetComm->TabIndex = 16;
			this->buttonResetComm->Text = L"Reset Comm";
			this->buttonResetComm->UseVisualStyleBackColor = true;
			this->buttonResetComm->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonResetComm_Click);
			// 
			// textAsyncAnswer
			// 
			this->textAsyncAnswer->Location = System::Drawing::Point(127, 98);
			this->textAsyncAnswer->Multiline = true;
			this->textAsyncAnswer->Name = L"textAsyncAnswer";
			this->textAsyncAnswer->Size = System::Drawing::Size(240, 48);
			this->textAsyncAnswer->TabIndex = 15;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(6, 102);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(115, 13);
			this->label57->TabIndex = 14;
			this->label57->Text = L"Asynchronous Answer:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 155);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(80, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Last Command:";
			// 
			// radioAsynchron
			// 
			this->radioAsynchron->AutoSize = true;
			this->radioAsynchron->Location = System::Drawing::Point(95, 70);
			this->radioAsynchron->Name = L"radioAsynchron";
			this->radioAsynchron->Size = System::Drawing::Size(91, 17);
			this->radioAsynchron->TabIndex = 12;
			this->radioAsynchron->Text = L"asynchronous";
			this->radioAsynchron->UseVisualStyleBackColor = true;
			// 
			// radioSynchron
			// 
			this->radioSynchron->AutoSize = true;
			this->radioSynchron->Checked = true;
			this->radioSynchron->Location = System::Drawing::Point(7, 70);
			this->radioSynchron->Name = L"radioSynchron";
			this->radioSynchron->Size = System::Drawing::Size(85, 17);
			this->radioSynchron->TabIndex = 11;
			this->radioSynchron->TabStop = true;
			this->radioSynchron->Text = L"synchronous";
			this->radioSynchron->UseVisualStyleBackColor = true;
			// 
			// comboPort
			// 
			this->comboPort->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboPort->FormattingEnabled = true;
			this->comboPort->Location = System::Drawing::Point(65, 18);
			this->comboPort->Name = L"comboPort";
			this->comboPort->Size = System::Drawing::Size(121, 21);
			this->comboPort->TabIndex = 10;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 24);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(56, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"COM-Port:";
			// 
			// comboAxes
			// 
			this->comboAxes->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboAxes->FormattingEnabled = true;
			this->comboAxes->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1", L"2", L"3" });
			this->comboAxes->Location = System::Drawing::Point(246, 43);
			this->comboAxes->Name = L"comboAxes";
			this->comboAxes->Size = System::Drawing::Size(121, 21);
			this->comboAxes->TabIndex = 8;
			// 
			// textLastCommand
			// 
			this->textLastCommand->Enabled = false;
			this->textLastCommand->Location = System::Drawing::Point(127, 152);
			this->textLastCommand->Name = L"textLastCommand";
			this->textLastCommand->Size = System::Drawing::Size(346, 20);
			this->textLastCommand->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(205, 45);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Axes:";
			// 
			// comboMode
			// 
			this->comboMode->Enabled = false;
			this->comboMode->FormattingEnabled = true;
			this->comboMode->Location = System::Drawing::Point(246, 21);
			this->comboMode->Name = L"comboMode";
			this->comboMode->Size = System::Drawing::Size(121, 21);
			this->comboMode->TabIndex = 6;
			this->comboMode->Text = L"Corvus";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(205, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Mode:";
			// 
			// comboBaudrate
			// 
			this->comboBaudrate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBaudrate->FormattingEnabled = true;
			this->comboBaudrate->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
				L"110", L"300", L"1200", L"2400", L"4800",
					L"9600", L"19200", L"38400", L"57600", L"115200", L"230400", L"460800", L"921600"
			});
			this->comboBaudrate->Location = System::Drawing::Point(65, 40);
			this->comboBaudrate->Name = L"comboBaudrate";
			this->comboBaudrate->Size = System::Drawing::Size(121, 21);
			this->comboBaudrate->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Baudrate:";
			// 
			// buttonInit
			// 
			this->buttonInit->Location = System::Drawing::Point(373, 16);
			this->buttonInit->Name = L"buttonInit";
			this->buttonInit->Size = System::Drawing::Size(100, 23);
			this->buttonInit->TabIndex = 0;
			this->buttonInit->Text = L"Init Controller";
			this->buttonInit->UseVisualStyleBackColor = true;
			this->buttonInit->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonInit_Click);
			// 
			// buttonOpenController
			// 
			this->buttonOpenController->Location = System::Drawing::Point(373, 40);
			this->buttonOpenController->Name = L"buttonOpenController";
			this->buttonOpenController->Size = System::Drawing::Size(100, 23);
			this->buttonOpenController->TabIndex = 1;
			this->buttonOpenController->Text = L"Open Controller";
			this->buttonOpenController->UseVisualStyleBackColor = true;
			this->buttonOpenController->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonOpenController_Click);
			// 
			// buttonCloseController
			// 
			this->buttonCloseController->Location = System::Drawing::Point(373, 64);
			this->buttonCloseController->Name = L"buttonCloseController";
			this->buttonCloseController->Size = System::Drawing::Size(100, 23);
			this->buttonCloseController->TabIndex = 2;
			this->buttonCloseController->Text = L"Close Controller";
			this->buttonCloseController->UseVisualStyleBackColor = true;
			this->buttonCloseController->Click += gcnew System::EventHandler(this, &Wp2CommGUI::buttonCloseController_Click);
			// 
			// Wp2CommGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(944, 532);
			this->Controls->Add(this->tabControl1);
			this->MaximumSize = System::Drawing::Size(960, 570);
			this->MinimumSize = System::Drawing::Size(960, 570);
			this->Name = L"Wp2CommGUI";
			this->Text = L"Wp2Comm Demo (C++)";
			this->Load += gcnew System::EventHandler(this, &Wp2CommGUI::Wp2CommGUI_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox27->ResumeLayout(false);
			this->groupBox27->PerformLayout();
			this->groupBox26->ResumeLayout(false);
			this->groupBox26->PerformLayout();
			this->groupBox24->ResumeLayout(false);
			this->groupBox24->PerformLayout();
			this->groupBox23->ResumeLayout(false);
			this->groupBox23->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox22->ResumeLayout(false);
			this->groupBox22->PerformLayout();
			this->groupBox21->ResumeLayout(false);
			this->groupBox21->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			this->groupBox25->ResumeLayout(false);
			this->groupBox25->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void Wp2CommGUI_Load(System::Object^  sender, System::EventArgs^  e) {

		try{
			array<String^>^ serialPorts = listComports();
			for each(String^ port in serialPorts)
			{
				comboPort->Items->Add(port->Substring(3));
			}
		}
		catch (int x){
		}

	}

	private: System::Void buttonInit_Click(System::Object^  sender, System::EventArgs^  e) {
		HWND hWnd = static_cast<HWND>(Handle.ToPointer());

		String ^ baudStr = comboBaudrate->Text->ToString();
		string baudstr = marshal_as<string>(baudStr);
		int ibaud = atoi(baudstr.c_str());

		String ^ portStr = comboPort->Text->ToString();
		string portstr = marshal_as<string>(portStr);
		int iport = atoi(portstr.c_str());

		String ^ axesStr = comboAxes->Text->ToString();
		string axesstr = marshal_as<string>(axesStr);
		int iAxes = atoi(axesstr.c_str());

		int mode = 2308;
		if (!radioSynchron->Checked)
			mode = 2564;

		int ret = wp2Comm.InitController(64, iAxes, iport, ibaud, hWnd, WMU_ASYNCMSG, mode);
		if (ret == 0){
			textLastCommand->Text = "Initialization -> OK";
		}
		else{
			textLastCommand->Text = "Initialization -> Failure (" + ret +")";
		}
	}

	private: System::Void buttonOpenController_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.OpenController();
		double Version = 0;
		if (ret == 0){
			textLastCommand->Text = "Open Controller -> OK";
			int ret = wp2Comm.GetDllVersion(&Version);
			textLastCommand->Text = "Open Controller -> OK " + Version;
		}
		else{
			textLastCommand->Text = "Open Controller -> Failure (" + ret + ")";
		}
	}

	private: System::Void buttonCloseController_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.CloseController();
		if (ret == 0)
			textLastCommand->Text = "Close Controller -> OK";
		else
			textLastCommand->Text = "Close Controller -> Failure (" + ret + ")";
	}
	private: System::Void buttonResetComm_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.ResetComm();
		if (ret == 0)
			textLastCommand->Text = "ResetComm -> OK";
		else
			textLastCommand->Text = "ResetComm -> Failure (" + ret + ")";
		
	}
	private: System::Void checkPreprocess_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		int ret = 0;
		if (checkPreprocess->Checked)
			 ret = wp2Comm.PreprocessReply(1);
		else
			ret = wp2Comm.PreprocessReply(0);
		if (ret == 0)
		{
			textLastCommand->Text = "PreprocessReply -> OK";
		}
		else{
			textLastCommand->Text = "PreprocessReply -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonExecute_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			if ((textCommand->Text->Length > 0) && (textLines->Text->Length > 0)){
				string command = marshal_as<string>(textCommand->Text);
				string lines = marshal_as<string>(textLines->Text);
				char reply[256];

				if (isnumeric(lines)){
					char *pCommand = &command[0];
					char *pLines = &lines[0];
					char *pReply = &reply[0];

					int ret = wp2Comm.ExecuteCommand(pCommand, atoi(pLines), pReply);
					if (ret == 0){
						if (radioSynchron->Checked){
							string answerstr = pReply;
							String ^ answerStr = marshal_as<String ^>(answerstr);
							textAnswer->Text = answerStr;
						}
						textLastCommand->Text = "ExecuteCommand -> OK";
					}
					else{
						textLastCommand->Text = "ExecuteCommand -> Failure (" + ret + ")";
					}
				}
			}
		}
		catch (int x){
		}
	}
	private: System::Void buttonIdentify_Click(System::Object^  sender, System::EventArgs^  e) {
		string id = "";
		char *pId = &id[0];

		int ret = wp2Comm.Identify(pId);
		if (ret == 0){
			string answerstr = pId;
			String ^ answerStr = marshal_as<String ^>(answerstr);
			textIdentify->Text = answerStr;
			textLastCommand->Text = "Identify -> OK";
		}
		else{
			textIdentify->Text = "";
			textLastCommand->Text = "Identify -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonGetStatus_Click(System::Object^  sender, System::EventArgs^  e) {
		DWORD state = -1;
		LPDWORD pState = &state;

		int ret = wp2Comm.GetStatus(pState);
		if (ret == 0){
			if (radioSynchron->Checked)
				textState->Text = (*pState).ToString();
			else
				textState->Text = "";
				textLastCommand->Text = "Get Status -> OK";
		}
		else{
			textState->Text = "";
			textLastCommand->Text = "Get Status -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonGetError_Click(System::Object^  sender, System::EventArgs^  e) {
		DWORD error = -1;
		LPDWORD pError = &error;

		int ret = wp2Comm.GetError(pError);
		if (ret == 0){
			if (radioSynchron->Checked)
				textError->Text = (*pError).ToString();
			else
				textError->Text = "";
			textLastCommand->Text = "Get Error -> OK";
		}
		else{
			textError->Text = "";
			textLastCommand->Text = "Get Error -> Failure (" + ret + ")";
		}
	}

	void getParameterOnStack(){
		DWORD param = -1;
		LPDWORD pParam = &param;

		int ret = wp2Comm.GetParamsOnStack(pParam);
		if (ret == 0){
			if (radioSynchron->Checked)
				textParameter->Text = (*pParam).ToString();
			else
				textParameter->Text = "";
			textLastCommand->Text = "Get Parameters on Stack -> OK";
		}
		else{
			textParameter->Text = "";
			textLastCommand->Text = "Get Parameters on Stack -> Failure (" + ret + ")";
		}

	}

	private: System::Void buttonGetParamsOnStack_Click(System::Object^  sender, System::EventArgs^  e) {
		getParameterOnStack();
	}

	private: System::Void buttonClearStack_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.ClearParameterStack();
		if (ret == 0){
			getParameterOnStack();
			textLastCommand->Text = "Clear Parameter Stack -> OK";
		}
		else{
			textParameter->Text = "";
			textLastCommand->Text = "Clear Parameter Stack -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonGetAcceleration_Click(System::Object^  sender, System::EventArgs^  e) {
		string accel = "";
		char *pAccel = &accel[0];

		int ret = wp2Comm.GetAcceleration(pAccel);
		if (ret == 0){
			string answerstr = pAccel;
			String ^ answerStr = marshal_as<String ^>(answerstr);
			textAcceleration->Text = answerStr;
			textLastCommand->Text = "Get Acceleration -> OK";
		}
		else{
			textAcceleration->Text = "";
			textLastCommand->Text = "Get Acceleration -> Failure (" + ret + ")";
		}
	}

	private: System::Void buttonSetAcceleration_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			if ((textAcceleration->Text->Length > 0)){
				string accel = marshal_as<string>(textAcceleration->Text);

				if (isnumeric(accel)){
					char *pAccel = &accel[0];

					int ret = wp2Comm.SetAcceleration(pAccel);
					if (ret == 0){
						textLastCommand->Text = "Set Acceleration -> OK";
					}
					else{
						textLastCommand->Text = "Set Acceleration -> Failure (" + ret + ")";
					}
				}
			}
		}
		catch (int x){
		}
	}
	private: System::Void buttonGetVelocity_Click(System::Object^  sender, System::EventArgs^  e) {
		string vel = "";
		char *pVel = &vel[0];

		int ret = wp2Comm.GetVelocity(pVel);
		if (ret == 0){
			string answerstr = pVel;
			String ^ answerStr = marshal_as<String ^>(answerstr);
			textVelocity->Text = answerStr;
			textLastCommand->Text = "Get Velocity -> OK";
		}
		else{
			textVelocity->Text = "";
			textLastCommand->Text = "Get Velocity -> Failure (" + ret + ")";
		}
	}
		private: System::Void buttonSetVelocity_Click(System::Object^  sender, System::EventArgs^  e) {
			 try{
				 if ((textVelocity->Text->Length > 0)){
					 string vel = marshal_as<string>(textVelocity->Text);

					 if (isnumeric(vel)){
						 char *pVel = &vel[0];

						 int ret = wp2Comm.SetVelocity(pVel);
						 if (ret == 0){
							 textLastCommand->Text = "Set Velocity -> OK";
						 }
						 else{
							 textLastCommand->Text = "Set Velocity -> Failure (" + ret + ")";
						 }
					 }
				 }
			 }
			 catch (int x){
			 }
		}
	private: System::Void buttonGetLimits_Click(System::Object^  sender, System::EventArgs^  e) {
		string xLow = "";
		char *pXLow = &xLow[0];

		string xUpper = "";
		char *pXUpper = &xUpper[0];

		string yLow = "";
		char *pYLow = &yLow[0];

		string yUpper = "";
		char *pYUpper = &yUpper[0];

		string zLow = "";
		char *pZLow = &zLow[0];

		string zUpper = "";
		char *pZUpper = &zUpper[0];

		string aLow = "";
		char *pALow = &aLow[0];

		string aUpper = "";
		char *pAUpper = &aUpper[0];

		int ret = wp2Comm.GetLimits(pXLow, pXUpper, pYLow, pYUpper, pZLow, pZUpper, pALow, pAUpper);
		if (ret == 0){
			string answerstr = pXLow;
			String ^ answerStr = marshal_as<String ^>(answerstr);
			textXLowerLimit->Text = answerStr;

			answerstr = pXUpper;
			answerStr = marshal_as<String ^>(answerstr);
			textXUpperLimit->Text = answerStr;

			answerstr = pYLow;
			answerStr = marshal_as<String ^>(answerstr);
			textYLowerLimit->Text = answerStr;

			answerstr = pYUpper;
			answerStr = marshal_as<String ^>(answerstr);
			textYUpperLimit->Text = answerStr;

			answerstr = pZLow;
			answerStr = marshal_as<String ^>(answerstr);
			textZLowerLimit->Text = answerStr;

			answerstr = pZUpper;
			answerStr = marshal_as<String ^>(answerstr);
			textZUpperLimit->Text = answerStr;

			textLastCommand->Text = "Get Limits -> OK";
		}
		else{
			textXLowerLimit->Text = "";
			textXUpperLimit->Text = "";
			textYLowerLimit->Text = "";
			textYUpperLimit->Text = "";
			textZLowerLimit->Text = "";
			textZUpperLimit->Text = "";
			textLastCommand->Text = "Get Limits -> Failure (" + ret + ")";
		}

	}

	void getPositions(){
		string xPos = "";
		char *pXPos = &xPos[0];

		string yPos = "";
		char *pYPos = &yPos[0];

		string zPos = "";
		char *pZPos = &zPos[0];

		string aPos = "";
		char *pAPos = &aPos[0];

		int ret = wp2Comm.GetPos(pXPos, pYPos, pZPos, pAPos);

		if (ret == 0){
			string answerstr = pXPos;
			String ^ answerStr = marshal_as<String ^>(answerstr);
			textXPos->Text = answerStr;

			answerstr = pYPos;
			answerStr = marshal_as<String ^>(answerstr);
			textYPos->Text = answerStr;

			answerstr = pZPos;
			answerStr = marshal_as<String ^>(answerstr);
			textZPos->Text = answerStr;
			textLastCommand->Text = "Get Pos -> OK";
		}
		else{
			textXPos->Text = "";
			textYPos->Text = "";
			textZPos->Text = "";
			textLastCommand->Text = "Get Pos -> Failure (" + ret + ")";
		}

	}

	private: System::Void buttonGetPos_Click(System::Object^  sender, System::EventArgs^  e) {
		getPositions();
	}

	private: System::Void buttonGetPosition_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			if ((textXMove->Text->Length > 0) && (textXMove->Text->Length > 0) && (textYMove->Text->Length > 0) && (textYMove->Text->Length > 0)){
				string xMove = marshal_as<string>(textXMove->Text);
				string yMove = marshal_as<string>(textYMove->Text);
				string zMove = marshal_as<string>(textZMove->Text);
				string aMove = "";

				if (isnumeric(xMove) && isnumeric(yMove) && isnumeric(zMove)){
					char *pXMove = &xMove[0];
					char *pYMove = &yMove[0];
					char *pZMove = &zMove[0];
					char *pAMove = &aMove[0];

					if (checkMoveAbsAutoReply->Checked){
						int ret = wp2Comm.MoveAbsoluteAutoReply(pXMove, pYMove, pZMove, pAMove);
						if (ret == 0){
							getPositions();
							textLastCommand->Text = "Move Absolute Auto Reply -> OK";
						}
						else{
							textLastCommand->Text = "Move Absolute Auto Reply -> Failure (" + ret + ")";
						}
					}
					else{
						int ret = wp2Comm.MoveAbsolute(pXMove, pYMove, pZMove, pAMove);
						if (ret == 0){
							textLastCommand->Text = "Move Absolute -> OK";
						}
						else{
							textLastCommand->Text = "Move Absolute -> Failure (" + ret + ")";
						}
					}
				}
			}
		}
		catch (int x){
		}
	}
	private: System::Void buttonMoveRel_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			if ((textXMoveRel->Text->Length > 0) && (textXMoveRel->Text->Length > 0) && (textYMoveRel->Text->Length > 0) && (textYMoveRel->Text->Length > 0)){
				string xMove = marshal_as<string>(textXMoveRel->Text);
				string yMove = marshal_as<string>(textYMoveRel->Text);
				string zMove = marshal_as<string>(textZMoveRel->Text);
				string aMove = "";

				if (isnumeric(xMove) && isnumeric(yMove) && isnumeric(zMove)){
					char *pXMove = &xMove[0];
					char *pYMove = &yMove[0];
					char *pZMove = &zMove[0];
					char *pAMove = &aMove[0];

					if (checkMoveRelAutoReply->Checked){
						int ret = wp2Comm.MoveRelativeAutoReply(pXMove, pYMove, pZMove, pAMove);
						if (ret == 0){
							getPositions();
							textLastCommand->Text = "Move Relative Auto Reply -> OK";
						}
						else{
							textLastCommand->Text = "Move Relative Auto Reply -> Failure (" + ret + ")";
						}
					}
					else{
						int ret = wp2Comm.MoveRelative(pXMove, pYMove, pZMove, pAMove);
						if (ret == 0){
							textLastCommand->Text = "Move Relative -> OK";
						}
						else{
							textLastCommand->Text = "Move Relative -> Failure (" + ret + ")";
						}
					}
				}
			}
		}
		catch (int x){
		}
	}
	private: System::Void buttonRangeMeasure_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.RangeMeasure();
		if (ret == 0)
			textLastCommand->Text = "Range Measure -> OK";
		else
			textLastCommand->Text = "Range Measure -> Failure (" + ret + ")";
	}
	private: System::Void buttonCalibrate_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.Calibrate();
		if (ret == 0)
			textLastCommand->Text = "Calibrate -> OK";
		else
			textLastCommand->Text = "Calibrate -> Failure (" + ret + ")";
	}
	private: System::Void checkJoystickEnabled_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (checkJoystickEnabled->Checked){
			int ret = wp2Comm.JoystickEnable();
			if (ret == 0){
				textLastCommand->Text = "JoystickEnable -> OK";
			}
			else{
				textLastCommand->Text = "JoystickEnable -> Failure (" + ret + ")";
			}
		}
		else{
			int ret = wp2Comm.JoystickDisable();
			if (ret == 0){
				textLastCommand->Text = "JoystickDisable -> OK";
			}
			else{
				textLastCommand->Text = "JoystickDisable -> Failure (" + ret + ")";
			}
		}
	}
	private: System::Void buttonGetJoyVel_Click(System::Object^  sender, System::EventArgs^  e) {
		string empty = "";
		char *JoyVel = &empty[0];
		int ret = wp2Comm.GetJoystickVelocity(JoyVel);
		if (ret == 0){
			if (radioSynchron->Checked){
				string answerstr = JoyVel;
				String ^ answerStr = marshal_as<String ^>(answerstr);
				textJoystickVelocity->Text = answerStr;
			}
			textLastCommand->Text = "GetJoystickVelocity -> OK";
		}
		else{
			textLastCommand->Text = "GetJoystickVelocity -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonSetJoyVel_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			if ((textJoystickVelocity->Text->Length > 0)){
				string vel = marshal_as<string>(textJoystickVelocity->Text);

				if (isnumeric(vel)){
					char *pVel = &vel[0];

					int ret = wp2Comm.SetJoystickVelocity(pVel);
					if (ret == 0){
						textLastCommand->Text = "Set Joystick Velocity -> OK";
					}
					else{
						textLastCommand->Text = "Set Joystick Velocity -> Failure (" + ret + ")";
					}
				}
			}
		}
		catch (int x){
		}
	}
	private: System::Void buttonXGetAxisMode_Click(System::Object^  sender, System::EventArgs^  e) {
		DWORD axismode1 = 0;
		LPDWORD AxisMode1 = &axismode1;

		DWORD axismode2 = 0;
		LPDWORD AxisMode2 = &axismode2;

		DWORD axismode3 = 0;
		LPDWORD AxisMode3 = &axismode3;

		DWORD axismode4 = 0;
		LPDWORD AxisMode4 = &axismode4;

		int ret = wp2Comm.GetAxisMode(AxisMode1, AxisMode2, AxisMode3, AxisMode4);
		if (ret == 0)
		{
			if (radioSynchron->Checked){
				comboXAxisMode->SelectedIndex = *AxisMode1;
				comboYAxisMode->SelectedIndex = *AxisMode2;
				comboZAxisMode->SelectedIndex = *AxisMode3;
			}

			textLastCommand->Text = "GetAxis -> OK";
		}
		else{
			textLastCommand->Text = "GetAxis -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonXSetAxisMode_Click(System::Object^  sender, System::EventArgs^  e) {
		string axismode1 = marshal_as<string>(comboXAxisMode->Text);
		char *AxisMode1 = &axismode1[0];

		string axismode2 = marshal_as<string>(comboYAxisMode->Text);
		char *AxisMode2 = &axismode2[0];

		string axismode3 = marshal_as<string>(comboZAxisMode->Text);
		char *AxisMode3 = &axismode3[0];

		string axismode4 = "";
		char *AxisMode4 = &axismode4[0];

		int ret = wp2Comm.SetAxisMode(AxisMode1, AxisMode2, AxisMode3, AxisMode4);
		if (ret == 0)
		{

			textLastCommand->Text = "SetAxis -> OK";
		}
		else{
			textLastCommand->Text = "SetAxis -> Failure (" + ret + ")";
		}
	}
	private: System::Void buttonAbortCommand_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.AbortCommand();
		if (ret == 0)
			textLastCommand->Text = "Abort Command -> OK";
		else
			textLastCommand->Text = "Abort Command -> Failure (" + ret + ")";
	}
	private: System::Void buttonSetOrigin_Click(System::Object^  sender, System::EventArgs^  e) {
		int ret = wp2Comm.SetOrigin();
		if (ret == 0)
		{
			textLastCommand->Text = "SetOrigin -> OK";
		}
		else{
			textLastCommand->Text = "SetOrigin -> Failure (" + ")";
		}
	}
private: System::Void checkMoveRelAutoReply_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
