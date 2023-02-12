/*
 * passwordInterface.ino
 * 
 * Interface for the password lock
 * 
 * Author: Kyle Mitard
 * Created 10 Feb 2023
 */
// #include "soc/rtc_wdt.h"
// #include "task_wdt.h"

// serial port baud rate
#define BAUD_RATE 9600

// number bits in password
#define PW_WIDTH 7

// GPIO pin for open output from FPGA
#define OPEN 18

// GPIO pin for enter input to FPGA
#define ENTER 19

// // GPIO pin for incorrect password
#define WRONG 21

// input pins to XOR gate (currently set up for an ESP32)
const int PW_IN[PW_WIDTH] = {13, 12, 14, 27, 26, 25, 33};

// 1 if lock is closed, 0 otherwise
bool closed = 1;

// flag for 
bool lockFlag = 0;

/*
 * ISR set lock flag - interrupt routine triggered whenever open output changes
 */
void IRAM_ATTR ISR_open() {
	lockFlag = 1;
}


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
	attachInterrupt(OPEN, ISR_open, FALLING); // for some bizzare reason, using falling edge will make it panic all the time

	Serial.println("enter password...");
	// esp_int_wdt_delete();
}


/*
 * Does a thing upon receiving a byte over serial - interrupt routine triggered with every byte recieved over serial
 */
void serialEvent() {

	// read byte
	char rxByte = Serial.read();

	// don't do anything if not closed
	if (closed) {

		Serial.print("Entered password ");

		// parallel write the byte, while printing it
		for (int i = PW_WIDTH-1; i >= 0; i--) {
			Serial.print((rxByte >> i) & 1);
			if (rxByte & (1 << i))
				digitalWrite(PW_IN[i], HIGH);
			else
				digitalWrite(PW_IN[i], LOW);
		}

		Serial.print(" ... ");

		// press enter
		digitalWrite(ENTER, HIGH);
		delay(2);
		digitalWrite(ENTER, LOW);

		// report access granted if it is open and was closed before
		if (closed && digitalRead(OPEN) == HIGH) {
			closed = 0;
			Serial.println("access granted. welcome to downtown coolsville.");
		// shame you for the wrong password if it is still closed
		} else if (digitalRead(OPEN) == LOW)
			Serial.println("wrong password, you knucklehead mcspazatron.");
	}
}


/*
 * Does nothing - loops indefinitely
 */
void loop() {
	if (lockFlag) {
		lockFlag = 0;
		Serial.println("locked");
	}
}
