`timescale 1ns / 1ps
/*
	xor_gate_noRO_top.v
	
	an XOR gate to be attacked with laser, but this time we directly locate
	it using the clock on one of the inputs
	
	Author: Kyle Mitard
	Created 23 Jan 2023
*/


module xor_gate_top(
	input [4:0] a,        
	input       osc_en,   // active high clock enable
	input       sysclk_n, // diff clock input
	input       sysclk_p, // diff clock input
	output      q
	);

	wire in5;

	// clock for locating XOR gate
	IBUFDS_IBUFDISABLE #(
		.DIFF_TERM("FALSE"),      // Differential Termination
		.IBUF_LOW_PWR("TRUE"),    // Low power="TRUE", Highest performance="FALSE" 
		.IOSTANDARD("DEFAULT"),   // Specify the input I/O standard
		.USE_IBUFDISABLE("TRUE")  // Set to "TRUE" to enable IBUFDISABLE feature
	) IBUFDS_IBUFDISABLE_inst (
		.O(in5),   // Buffer output
		.I(sysclk_p),   // Diff_p buffer input (connect directly to top-level port)
		.IB(sysclk_n), // Diff_n buffer input (connect directly to top-level port)
		.IBUFDISABLE(~osc_en) // Buffer disable input, high=disable
	);

	(* dont_touch = "true" *)
	assign q = a[0] ^ a[1] ^ a[2] ^ a[3] ^ a[4] ^ in5;

endmodule



