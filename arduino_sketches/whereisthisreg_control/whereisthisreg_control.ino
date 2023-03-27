/*
 * whereisthisreg_control.ino
 * 
 * tester for whether a D flip flop has been flipped by laser
 * 
 * Author: Kyle Mitard
 * Created 2 Mar 2023
 * 
 */

#include <EEPROM.h>

// serial port baud rate
#define BAUD_RATE 9600

// number of flip flops to test
#define N_FF 8

// byte to send over serial to trigger a read
#define CMD_READ 'a'

// byte to send to toggla ring oscillator
#define CMD_TOGGLE_OSC 'r'

// byte to send over serial to reset DFF enables
#define CMD_RESET '~'

// GPIO pin for ring oscillator enable
#define OSC_EN 13

// output pins from each flip flop (currently set up for an ESP32)
const int FF_OUT[N_FF] = {4, 5, 6, 7, 8, 9, 10, 11};

// bitfield for each enabled oscillator
uint8_t ff_en = 0b00000000;

// 1 if oscillator is enabled, 0 otherwise 
bool oscEnabled = 0;


/*
 * configures pins and serial bus
 * 
 * [called once on startup]
 */
void setup() {
	
	// start serial
	Serial.begin(BAUD_RATE);

	// set oscillator enable as input
	pinMode(OSC_EN, OUTPUT);
	digitalWrite(OSC_EN, LOW);

	// set each flip flop enable as output
	for (int i = 0; i < N_FF; i++) {
		pinMode(FF_OUT[i], OUTPUT);
		digitalWrite(FF_OUT[i], LOW);
	}
}


/*
 * Does a thing upon receiving a byte over serial
 * 
 * [interrupt routine triggered with every byte recieved over serial]
 */
void serialEvent() {

	// read byte and do a thing depending on byte
	char rxByte = Serial.read();

	// reset
	if (rxByte == CMD_RESET) {
		ff_en = 0;
		for (int i = 0; i < N_FF; i++) {		
			digitalWrite(FF_OUT[i], LOW);
		}
		Serial.println("reset");

	// set a D flip-flop
	} else if (rxByte >= '0' && rxByte < '0' + N_FF) {
		Serial.print("flip flop ");
		Serial.print(rxByte);
		ff_en ^= 1 << (rxByte - '0');
		if (ff_en & (1 << (rxByte - '0'))) {
			digitalWrite(FF_OUT[rxByte-'0'], HIGH);
			Serial.println(" enabled");
		} else {
			digitalWrite(FF_OUT[rxByte-'0'], LOW);
			Serial.println(" disabled");
		}
	
	// read status of all flip flops
	} else if (rxByte == CMD_READ) {
		char b = ff_en;
		for (int i = N_FF-1; i >= 0; i--) {
			Serial.print(b & 1);
			b = b >> 1;
		}
		Serial.println();

	// toggle ring oscillator
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


/*
 * Main loop: does nothing
 * 
 * [loops indefinitely]
 */
void loop() {
}