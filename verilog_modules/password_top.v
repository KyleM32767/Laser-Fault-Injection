/*
 * password_top.v
 * 
 * Top-level module for the simple password lock
 * 
 * Author: Kyle Mitard
 * Created 9 Feb 2022
 * 
 * This only exists for laser fault injection research, and it probably
 * should not be relied on in a real security application. Chances are,
 * it is hilariously insecure!
 */

module password_top (
	input        sysclk_n,
	input        sysclk_p,
	input        btnc,     // center button: reset
	input        btnd,     // down button: enter
	input  [7:0] ja,
	output [2:0] led
	);

	wire clk;
	wire lock;

	// clock wizard to generate FSM clock signal
	clk_wiz_0 mmcm0(
		.resetn(~btnc),
		.clk_in1_p(sysclk_p),
		.clk_in1_n(sysclk_n),
		.locked(lock),
		.clk_out1(clk)
	);

	// password finite state machine
	pw_fsm pw0 (
		.clk(clk),
		.reset_n(lock),
		.char_in(ja),
		.enter(btnd),
		.open(led[0]),
		.wrong(led[1])
	);

endmodule