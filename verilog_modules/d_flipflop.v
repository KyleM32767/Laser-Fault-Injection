/*
 * d_glipflop.v
 * 
 * an array of registers to be attacked by laser
 * 
 * Author: Kyle Mitard
 * Created 14 Feb 2023
 * 
 * NOTE: you must use the keep_equivalent_regiters option or else the registers will combine to one!!
 */

module d_flipflop #(
	parameter N            = 8,     // number of flip flops
	parameter DB_COUNT_MAX = 20000, // clock cycles @ 100MHz
	parameter DB_COUNT_N   = 15     // bits for debouncer counter
) (
	input              sysclk_p, // clock signal
	input              sysclk_n,
	input              reset,    // synchronous active-high reset
	input              en,       // active-high write enable
	input      [N-1:0] d,        // input
	output reg [N-1:0] q_db      // debounced output
	);

	wire clk;

	// raw output
	reg [N-1:0] q;

	// debouncer counter
	reg [DB_COUNT_N-1:0] db_count [N-1:0];

	// clock wizard to generate 100 MHz clock signal
	clk_wiz_0 mmcm0(
		.reset(reset),
		.clk_in1_p(sysclk_p),
		.clk_in1_n(sysclk_n),
		.clk_out1(clk)
	);

	// register latched on positive clock
	always @(posedge clk) begin 
		if (en) begin
			q <= reset ? 1'b0 : d;
		end
	end
	
	
	// generate counters for each debouncer
	genvar i;
	generate
		for (i = 0; i < N; i++) begin
			always @(posedge clk) begin
				// count up if difference in outputs
				db_count[i] <= (q_db == q) ? 1'b0 : db_count[i] + 1'b1;

				// change debounced output if the db_count exceeds the max
				q_db[i] <= (db_count[i] < DB_COUNT_MAX) ? q_db[i] : q[i];
			end
		end
	endgenerate

endmodule