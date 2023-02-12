/*
 * pw_fsm.v
 * 
 * A finite state machine that implements a simple password lock.
 * 
 * Author: Kyle Mitard
 * Created 9 Feb 2022
 * 
 * This only exists for laser fault injection research, and it probably
 * should not be relied on in a real security application. Chances are,
 * it is hilariously insecure!
 */

module pw_fsm #(
	parameter PW_WIDTH = 7,     // size of a single password character in bits
	parameter PASSWORD = 7'h48 // ascii "H"
)(
	input               clk,     // clock input
	input               reset_n, // synchronous active low reset
	input  [PW_WIDTH:0] char_in, // parallel input for password character
	input               enter,   // enter character button
	output reg          open     // 1 if open
	);

	// labels for FSM states
	localparam STATE_LOCKED     = 2'b00; // idle and locked
	localparam STATE_INPUT_WAIT = 2'b01; // wait for enter to be released
	localparam STATE_AUTH       = 2'b10; // entering a password 
	localparam STATE_UNLOCK     = 2'b11; // idle and unlocked

	// current FSM state
	reg [1:0] fsmState;

	// next FSM state
	reg [1:0] nextState;

	// latch everything on rising edge
	always @(posedge clk) begin

		// apply next state
		fsmState <= nextState;

		// reset condition: turn off all indicators
		if (~reset_n) begin
			open <= 1'b0;
		end

		// synchronously set open if in unlocked state, or closed otherwise
		open <= (fsmState == STATE_UNLOCK);

	end


	// next state logic
	always @(*) begin

		// reset condition: idle and locked
		if (~reset_n) begin
			nextState = STATE_LOCKED;
		end

		else begin
			case (fsmState)
				
				// locked and idle: go to input wait if enter is pressed, 
				STATE_LOCKED: begin
					nextState = enter ? STATE_INPUT_WAIT : STATE_LOCKED;
				end

				// input buffer: wait for enter to be released
				STATE_INPUT_WAIT: begin
					nextState = enter ? STATE_INPUT_WAIT : STATE_AUTH;
				end

				// authentication: unlock if password is correct
				STATE_AUTH: begin
					nextState = (char_in == PASSWORD) ? STATE_UNLOCK : STATE_LOCKED;
				end

				// unlocked: stay open
				STATE_UNLOCK: begin
					nextState = STATE_UNLOCK;
				end

			endcase
		end
	end

endmodule