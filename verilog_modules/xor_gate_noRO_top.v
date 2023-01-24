`timescale 1ns / 1ps
/*
	xor_gate_noRO_top.v
	
	an XOR gate to be attacked with laser, but this time we directly locate
	it using the clock on one of the inputs
	
	Author: Kyle Mitard
	Created 23 Jan 2023
*/


module xor_gate_top(
	input [5:0] a,
	input       osc_en,
	input       sysclk_n,
	output      q
	);

	wire in0;

	// first input is clock if enabled in order to have photon emission
	assign in0 = osc_en ? sysclk_n : a[0];

	(* dont_touch = "true" *)
	assign q = in0 ^ a[1] ^ a[2] ^ a[3] ^ a[4] ^ a[5];

endmodule



