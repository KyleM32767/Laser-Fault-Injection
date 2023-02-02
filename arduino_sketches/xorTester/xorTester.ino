/*
 * xorTester.ino
 * 
 * tests the XOR gate on a Genesys2 FPGA for faults
 * 
 * Author: Kyle Mitard
 * Created 19 Jan 2023
 */

// number of XOR gate inputs
#define N_INPUTS 5

// GPIO pin for XOR gate output
#define OUTPUT_PIN 15

// GPIO pin for ring oscillator enable
#define OSC_EN 2

// RX bytes corresponding to various commands
#define CMD_TEST_VERBOSE   'a'
#define CMD_TEST_NORMAL    'b'
#define CMD_TEST_FAULTTYPE 'c'
#define CMD_TOGGLE_OSC     'r'

// input pins to XOR gate (currently set up for an ESP32)
const int INPUT_PINS[N_INPUTS] = {13, 12, 14, 27, 26};

// true if ring oscillator is enabled, false otherwise
bool oscEnabled = true;


/*
 * Tests an XOR gate with a given input
 * 
 * Params:
 *  - x        = test input
 *  - expected = pointer to where expected output is written
 *  - actual   = pointer to where actual output is written
 */
void testXOR(unsigned int x, bool* expected, bool* actual) {

	// set expected to zero
	*expected = 0; 

	// parse through every bit
	for (int i = 0; i < N_INPUTS; i++) {

		// write bit to output
		if (x & (1<<i))
			digitalWrite(INPUT_PINS[i], HIGH);
		else
			digitalWrite(INPUT_PINS[i], LOW);

		// update expected value
		*expected ^= (x>>i) & 1;
	}

	delay(10);

	// read actual output
	*actual = (digitalRead(OUTPUT_PIN) == HIGH);
}


/*
 * configures pins and 
 */
void setup() {
	Serial.begin(115200);
	for (int i = 0; i < N_INPUTS; i++) {
		pinMode(INPUT_PINS[i], OUTPUT);
	}
	pinMode(OUTPUT_PIN, INPUT);
	pinMode(OSC_EN, OUTPUT);
	digitalWrite(OSC_EN, HIGH);

//	Serial.println("Ready\n\n");
}


/*
 * Does a thing upon receiving a byte over serial
 */
void serialEvent() {

	char rxByte = Serial.read();


	// initiate gate test, verbose output - to be used in arduino serial monitor or equivalent
	if (rxByte == CMD_TEST_VERBOSE) {

		// expected result from XOR gate
		bool expected;

		// actual result from XOR gate
		bool actual;

		Serial.println("testing begin...");
		for (unsigned int i = 0; i < (1<<N_INPUTS); i++) {

			// do a test
			testXOR(i, &expected, &actual);

			// print result
			Serial.print("testing input ");
			Serial.print(i, BIN);
			Serial.print("    expected ");
			Serial.print(expected);
			Serial.print("    recieved ");
			Serial.print(actual);
			if (expected != actual)
				Serial.print("    FAULT!");
			Serial.println();
		}
	
	// initiate gate test with normal output - to be used in automation
	} else if (rxByte == CMD_TEST_NORMAL) {
		for (unsigned int i = 0; i < (1<<N_INPUTS); i++) {

			// expected result from XOR gate
			bool expected;

			// actual result from XOR gate
			bool actual;

			// do a test
			testXOR(i, &expected, &actual);

			// send a byte for the result
			if (expected != actual)
				Serial.print('F'); // fault
			else 
				Serial.write('~'); // no fault
		}
		Serial.println();

	
	} else if (rxByte == CMD_TEST_FAULTTYPE) {
		for (unsigned int i = 0; i < (1<<N_INPUTS); i++) {

			// expected result from XOR gate
			bool expected;

			// actual result from XOR gate
			bool actual;

			// do a test
			testXOR(i, &expected, &actual);

			// send a byte for the result
			if (expected == actual)
				Serial.print('~'); // no fault
			else if (actual == 0)
				Serial.write('1'); // 1 to 0 fault
			else if (actual == 1)
				Serial.write('0'); // 0 to 1 fault
		}
		Serial.println();

	// toggle ring oscillator or clock
	} else if (rxByte == CMD_TOGGLE_OSC) {
		oscEnabled ^= 1;
		if (oscEnabled) {
			digitalWrite(OSC_EN, HIGH);
			Serial.println("oscillator enabled");
		} else {
			digitalWrite(OSC_EN, LOW);
			Serial.println("oscillator disabled");
		}
	}
}


void loop() {
}
