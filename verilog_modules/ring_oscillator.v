`timescale 1ns / 1ps
/*
	ring_oscillator.v
	
	a parameterized ring oscillator
	
	Author: Kyle Mitard
	Created 9 Dec 2022
	
	NOTE: this will only synthesize/implement properly with all optimizations disabled!
*/


module ring_oscillator
#(
	parameter N_STAGES = 11 // number of stages - MUST BE ODD AND > 1
)(
	input  en,              // active high enable   
	output osc_out          // ring oscillator output
	);

	// output of each inverter
	(* S = "true" *)
	(* dont_touch = "true" *)
	reg [N_STAGES-1:0] b;

	// generate n stages feeding into each other
	generate
		genvar i;
		for (i = N_STAGES-1; i > 0; i = i-1) begin
			(* dont_touch = "true" *)
			always @(*) begin
				b[i] = ~b[i-1];
			end
		end
	endgenerate
	
	// first stage feeds into last
	(* dont_touch = "true" *)
	always @(*) begin
		b[0] = ~b[N_STAGES-1] & en;
	end
	
	// output is just one of those stages
	assign osc_out = b[0];

endmodule
