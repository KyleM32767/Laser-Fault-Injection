/*
 * passwordInterface.ino
 * 
 * Interface for the password lock
 * 
 * Author: Kyle Mitard
 * Created 10 Feb 2023
 */

// serial port baud rate
#define BAUD_RATE 9600

// number bits in password
#define PW_WIDTH 7

// GPIO pin for open output from FPGA
#define OPEN 18

// GPIO pin for enter input to FPGA
#define ENTER 19

// input pins to XOR gate (currently set up for an ESP32)
const int PW_IN[PW_WIDTH] = {13, 12, 14, 27, 26, 25, 33};

// 1 if lock is closed, 0 otherwise
bool closed = 1;

// flag for if the door was locked
bool lockFlag = 0;

// flag for if the door was opened
bool openFlag = 0;


/*
 * ISR set lock flag
 * 
 * [interrupt routine triggered whenever open pin changes]
 */
void IRAM_ATTR ISR_open() {
	if (digitalRead(OPEN) == LOW)
		lockFlag = 1;
	else
		openFlag = 1;
}


/*
 * configures pins and serial bus
 * 
 * [called once on startup]
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
	attachInterrupt(OPEN, ISR_open, CHANGE); // for some bizzare reason, using falling edge will make it panic all the time

	Serial.println("enter password...");
	// esp_int_wdt_delete();
}


/*
 * Does a thing upon receiving a byte over serial
 * 
 * [interrupt routine triggered with every byte recieved over serial]
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

		Serial.println();

		// press enter
		digitalWrite(ENTER, HIGH);
		delay(2);
		digitalWrite(ENTER, LOW);
	}
}


/*
 * Main loop: Does nothing unless there is a flag
 * 
 * [loops indefinitely]
 */
void loop() {
	
	// if lock flag is set, reset lock flag and print message
	if (lockFlag) {
		lockFlag = 0;
		Serial.println("the coolsville gate has been locked");
	
	// if the open flag is set, 
	} else if (openFlag) {
		openFlag = 0;
		closed = 0;
		Serial.println("access granted. welcome to downtown coolsville");
	}
}
