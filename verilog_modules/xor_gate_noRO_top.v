`timescale 1ns / 1ps
/*
	xor_gate_noRO_top.v
	
	an XOR gate to be attacked with laser, but this time we directly locate
	it using the clock on one of the inputs
	
	Author: Kyle Mitard
	Created 23 Jan 2023
*/


module xor_gate_noRO_top(
	input [4:0] a,        
	input       osc_en,   // active high clock enable
	input       sysclk_n, // diff clock input
	input       sysclk_p, // diff clock input
	output      q
	);

	wire clk;

	clk_wiz_0 mmcm0(
		.resetn(osc_en),
		.clk_in1_p(sysclk_p),
		.clk_in1_n(sysclk_n),
		.clk_out1(clk)
	);

	(* dont_touch = "true" *)
	assign q = a[0] ^ a[1] ^ a[2] ^ a[3] ^ a[4] ^ clk;

endmodule



