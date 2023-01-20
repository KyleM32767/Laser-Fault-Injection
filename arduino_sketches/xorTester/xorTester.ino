/*
 * xorTester.ino
 * 
 * tests the XOR gate on a Genesys2 FPGA for faults
 * 
 * Author: Kyle Mitard
 * Created 19 Jan 2023
 */

// number of XOR gate inputs
#define N_INPUTS 6

// GPIO pin for XOR gate output
#define OUTPUT_PIN 15

// GPIO pin for ring oscillator enable
#define OSC_EN 2

// input pins to XOR gate (currently set up for an ESP32)
const int INPUT_PINS[N_INPUTS] = {13, 12, 14, 27, 26, 25};

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
	Serial.begin(9600);
	for (int i = 0; i < N_INPUTS; i++) {
		pinMode(INPUT_PINS[i], OUTPUT);
	}
	pinMode(OUTPUT_PIN, INPUT);
	pinMode(OSC_EN, OUTPUT);
	digitalWrite(OSC_EN, HIGH);

	Serial.println("Ready\n\n");
}


/*
 * Does a thing upon receiving a byte over serial
 */
void serialEvent() {

	char rxByte = Serial.read();

	// 'a' will initiate gate test
	if (rxByte == 'a') {

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
	// 'r' will toggle ring oscillator 
	} else if (rxByte == 'r') {
		oscEnabled ^= 1;
		if (oscEnabled)
			digitalWrite(OSC_EN, HIGH);
		else
			digitalWrite(OSC_EN, LOW);
	}
}


void loop() {
}
