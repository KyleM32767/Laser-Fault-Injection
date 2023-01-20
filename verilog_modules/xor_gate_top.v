`timescale 1ns / 1ps
/*
	xor_gate_top.v
	
	an XOR gate to be attacked with laser
	
	Author: Kyle Mitard
	Created 17 Jan 2023
*/


module xor_gate_top(
	input [5:0] a,
	//input       ro_en,
	///output      ro_out,
	output      q
	);

	// ring oscillator for finding the gate
//	(* dont_touch = "true" *)
//	ring_oscillator osc0(
//		.en(ro_en),
//		.osc_out(ro_out)
//		);
	
	assign q = a[0] ^ a[1] ^ a[2] ^ a[3] ^ a[4] ^ a[5];

endmodule



