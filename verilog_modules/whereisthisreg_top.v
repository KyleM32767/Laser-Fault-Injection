/*
 * whereisthisreg_top.v
 * 
 * an array of registers fed by a ring oscillator to determine where is this register?
 * 
 * Author: Kyle Mitard
 * Created 14 Feb 2023
 * 
 * NOTE: you must use the keep_equivalent_regiters option, or else the registers will combine to one!!
 */

module whereisthisreg_top #(
	parameter N_REGS     = 8, // number of registers to locate
	parameter OSC_STAGES = 11 // number of ring oscillator stages
)(
	input                   sysclk_n, // system differential clock
	input                   sysclk_p, 
	input      [N_REGS-1:0] ja,       // active-high register enable
	// input                   jb1,      // active-high reset
	input                   jb2,      // active-high ring oscillator enable
	output                  jb3,      // ring oscillator output
	output reg [N_REGS-1:0] jc        // the registers to locate
	);

	// a ring oscillator
	ring_oscillator #(
		.N_STAGES(OSC_STAGES)
	) osc0 (
		.en(jb2),
		.osc_out(jb3)
	);

	wire clk;

	// // clock wizard to generate 100 MHz clock signal
	// clk_wiz_0 mmcm0(
	// 	.reset(jb1),
	// 	.clk_in1_p(sysclk_p),
	// 	.clk_in1_n(sysclk_n),
	// 	.clk_out1(clk)
	// );


	// Differential Clock Buffer to create 200 Mhz Clock
	IBUFGDS #(
		.DIFF_TERM   ("FALSE"),
		.IBUF_LOW_PWR("TRUE" ),
		.IOSTANDARD  ("LVDS" )
	) get_clk (
		.O(clk   ),
		.I(sysclk_p ),
		.IB(sysclk_n)
	);

	// generate n registers constantly toggling at every clock cycle when enabled
	(* dont_touch = "true" *)
	generate
		genvar i;
		for (i = 0; i < N_REGS; i = i+1) begin
			always @(posedge clk) begin
				jc[i] <= ja[i] ? ~jc[i] : 1'b0;
			end
		end
	endgenerate

endmodule