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
	parameter N = 8
) (
	input              sysclk_p, // clock signal
	input              sysclk_n,
	input              reset,    // synchronous active-high reset
	input              en,       // active-high enable
	input      [N-1:0] d,        // input
	output reg [N-1:0] q         // output
	);

	wire clk;

	// clock wizard to generate 100 MHz clock signal
	clk_wiz_0 mmcm0(
		.reset(reset),
		.clk_in1_p(sysclk_p),
		.clk_in1_n(sysclk_n),
		.clk_out1(clk)
	);

	always @(posedge clk) begin 
		if (en) begin
			q <= reset ? 1'b0 : d;
		end
	end
	

endmodule