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
	input        reset,    // PMOD header B1: active high reset
	input  [6:0] pw,       // PMOD header A0-6: password input
	input        enter,    // PMOD header A7: enter
	output       open      // PMOD header B0: open indicator
	);

	// generated clock signal
	wire clk;
	
	// locked output from clock gen, serving as reset for FSM
	wire lock;

	// clock wizard to generate FSM clock signal
	clk_wiz_0 mmcm0(
		.reset(reset),
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