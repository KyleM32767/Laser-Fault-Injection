/*
 * dffTester.ino
 * 
 * tester for whether a D flip flop has been flipped by laser
 * 
 * Author: Kyle Mitard
 * Created 16 Feb 2023
 * 
 * Every DFF output has an interrupt, which flips a bit to 1 in EEPROM. These
 * bits can then be read and reset using the serial interface. The EEPROM is
 * needed because a reset happens every time the serial port is opened, and
 * the EEPROM allows the values to be preserved between resets 
 */

#include <EEPROM.h>

// serial port baud rate
#define BAUD_RATE 9600

// number of flip flops to test
#define N_FF 8

// byte to send over serial to trigger a read
#define CMD_READ 'r'

// byte to send over serial to reset EEPROM register
#define CMD_RESET '~'

// EEPROM address to write to
#define EEPROM_ADDR 0

// output pins from each flip flop (currently set up for an ESP32)
const int FF_OUT[N_FF] = {13, 12, 14, 27, 26, 25, 33, 32};


/*
 * flips a bit in the EEPROM value that indicates whether a bit flipped
 * 
 * Params:
 *  n = bit to set 1
 */
void IRAM_ATTR flipBit(int n) {
	EEPROM.write(EEPROM_ADDR, EEPROM.read(EEPROM_ADDR) | (1 << n));
}


/*
 * The respective ISRs to flip each bit in EEPROM
 * (it pains me that there is no better way to do this)
 */
void IRAM_ATTR ISR_pin0() { flipBit(0); }
void IRAM_ATTR ISR_pin1() { flipBit(1); }
void IRAM_ATTR ISR_pin2() { flipBit(2); }
void IRAM_ATTR ISR_pin3() { flipBit(3); }
void IRAM_ATTR ISR_pin4() { flipBit(4); }
void IRAM_ATTR ISR_pin5() { flipBit(5); }
void IRAM_ATTR ISR_pin6() { flipBit(6); }
void IRAM_ATTR ISR_pin7() { flipBit(7); }


/*
 * Array of ISR pointers
 */
void (*ISR[N_FF])() = {ISR_pin0, ISR_pin1, ISR_pin2, ISR_pin3, ISR_pin4, ISR_pin5, ISR_pin6, ISR_pin7};


/*
 * configures pins and serial bus
 * 
 * [called once on startup]
 */
void setup() {
	
	// start serial
	Serial.begin(BAUD_RATE);


	// set each flip flop output as input
	for (int i = 0; i < N_FF; i++) {
		pinMode(FF_OUT[i], INPUT);
		attachInterrupt(FF_OUT[i], ISR[i], CHANGE);
	}

	EEPROM.begin(12);
}


/*
 * Does a thing upon receiving a byte over serial
 * 
 * [interrupt routine triggered with every byte recieved over serial]
 */
void serialEvent() {

	// read byte
	char rxByte = Serial.read();

	// reset or read EEPROM if the signal is given
	if (rxByte == CMD_RESET) {
		EEPROM.write(EEPROM_ADDR, 0);
		EEPROM.commit();
		Serial.println("reset");
	} else if (rxByte == CMD_READ) {
		char b = EEPROM.read(EEPROM_ADDR);
		for (int i = 0; i < N_FF; i++) {
			Serial.print(b & 1);
			b = b >> 1;
		}
	}
}


/*
 * Main loop: Does nothing unless there is a flag
 * 
 * [loops indefinitely]
 */
void loop() {
	EEPROM.commit();
}