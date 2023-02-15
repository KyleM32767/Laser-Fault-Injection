/*
 * whereisthisreg_top.v
 * 
 * an array of registers fed by a ring oscillator to determine where is this register?
 * 
 * Author: Kyle Mitard
 * Created 14 Feb 2023
 * 
 * NOTE: you must use the keep_equivalent_regiters option or else the registers will combine to one!!
 */

module d_flipflop #(
	parameter N = 1
) (
	input              reset, // synchronous active-high reset
	input              clk,   // clock signal
	input      [N-1:0] d,     // input
	output reg [N-1:0] q      // output
	);

	// latch on rising edge
	always @(posedge clk) begin 
		q <= reset ? 1'b0 : d;
	end

endmodule