/*
 * passwordInterface.ino
 * 
 * Interface for the password lock
 * 
 * Author: Kyle Mitard
 * Created 10 Feb 2023
 */
//#include "soc/rtc_wdt.h"

// serial port baud rate
#define BAUD_RATE 115200

// number bits in password
#define PW_WIDTH 7

// GPIO pin for open output from FPGA
#define OPEN 18

// GPIO pin for enter input to FPGA
#define ENTER 19

// // GPIO pin for incorrect password
// #define WRONG 21

// input pins to XOR gate (currently set up for an ESP32)
const int PW_IN[PW_WIDTH] = {13, 12, 14, 27, 26, 25, 33};

bool openFlag = 0;

/*
 * ISR to report on status of door - interrupt routine triggered whenever open output changes
 */
void IRAM_ATTR ISR_open() {
	openFlag = 1;
}

/*
 * ISR to shame you for wrong password - interrupt routine triggered on rising edge of wrong output
 */
// void IRAM_ATTR ISR_wrong() {
// 	if (digitalRead(WRONG) == HIGH)
// 		Serial.println("wrong password, you knucklehead mcspazatron.");
// }


/*
 * configures pins and serial bus - called once on startup
 */
void setup() {
	
	// start serial
	Serial.begin(BAUD_RATE);
	
	// set PW bits and enter as output
	for (int i = 0; i < PW_WIDTH; i++) {
		pinMode(PW_IN[i], OUTPUT);
		digitalWrite(PW_IN[i], HIGH);
	}
	pinMode(ENTER, OUTPUT);
	digitalWrite(ENTER, LOW);

	// set open indicator as input with an interrupt
	pinMode(OPEN, INPUT);
	attachInterrupt(OPEN, ISR_open, CHANGE);

	// set wrong indicator as input with an interrupt
	// pinMode(WRONG, INPUT);
	// attachInterrupt(WRONG, ISR_wrong, CHANGE);

	Serial.println("enter password...");
}


/*
 * Does a thing upon receiving a byte over serial - interrupt routine triggered with every byte recieved over serial
 */
void serialEvent() {

	// read byte
	char rxByte = Serial.read();

	Serial.println(rxByte, BIN);

	// parallel write the byte
	for (int i = 0; i < PW_WIDTH; i++) {
		if (rxByte & 0x01)
			digitalWrite(PW_IN[i], HIGH);
		else
			digitalWrite(PW_IN[i], LOW);
		rxByte = rxByte >> 1;
	}

	// press enter
	digitalWrite(ENTER, HIGH);
	delay(2);
	digitalWrite(ENTER, LOW);
}


/*
 * Does nothing - loops indefinitely
 */
void loop() {
	if (openFlag) {
		openFlag = 0;
		// report new status of lock
		if (digitalRead(OPEN) == HIGH)
			Serial.println("access granted. welcome to downtown coolsville.");
		else
			Serial.println("locked");
	}
}
