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
	input        sysclk_n, // system differential clock
	input        sysclk_p,
	input        btnc,     // center button: reset
	input  [6:0] pw,       // PMOD header A0-6: password input
	input        enter,      // PMOD header B1: enter
	output       open      // PMOD header A7: open indicator
	);

	wire clk;
	wire lock;

	// clock wizard to generate FSM clock signal
	clk_wiz_0 mmcm0(
		.reset(btnc),
		.clk_in1_p(sysclk_p),
		.clk_in1_n(sysclk_n),
		.locked(lock),
		.clk_out1(clk)
	);

	// password finite state machine
	pw_fsm pw0 (
		.clk(clk),
		.reset_n(lock),
		.char_in(pw),
		.enter(enter),
		.open(open)
	);

endmodule