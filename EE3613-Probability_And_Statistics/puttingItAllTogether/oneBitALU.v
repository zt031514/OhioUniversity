`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Ohio University EECS
// Engineer: Zach Tumbleson
// 
// Create Date:    12/3/17 
// Design Name: 
// Module Name:   oneBitALU 
// Project Name: 	EE 3613 Final Project
// Target Devices: 
// Tool versions: 
// Description: Implements a 1 bit ALU with the following operations:
//						AND, OR, ADD, SLT
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module OneBitALU(a, b, cin, ainv, binv, less, op, result, cout, set);
	input a, b, cin;  // Inputs to the one-bit ALU, "cin" is the carry-in bit.
	input ainv, binv; // A_invert and Bnegate bits (see table below)
	input less; 		// This input will be set as 0 for all ALUs for now but the one
							//corresponding to the most-significant bit (see Problem 3).
	input [1:0] op;   // 2-bit operation code. op[0] is the LSB.
	
	//intermediate results
	reg int_and;		//a & b
	reg int_or;		//a | b
	reg int_add;		//LSB of a+b+cin
	reg select_a;		//mux(a)
	reg select_b;     //mux(b)
	reg[1:0] temp_add;//stores two bit temp value of addition
	
	output result;		// The result of the ALU (depends on the operation chosen)
	reg  result;
	output cout;      // Carry out bit of the full adder
	reg cout;
	output set;    	// This is the "sum" output of the full-adder (see Problem 3).
	reg set;
	
always @(a or b or cin or ainv or binv or less or op)
	begin	
		
		//SELECT INPUTS
		//a or ~a mux, select_a is output
		case (ainv)
			
			1'b 0: begin
				select_a = a;
			end
			
			1'b 1: begin
				select_a = ~a;
			end
		endcase
		
		//b or ~b mux, select_b is output
		case (binv)
			
			1'b 0: begin
				select_b = b;
			end
			
			1'b 1: begin
				select_b = ~b;
			end
		endcase

		//CALCULATE AND
		int_and = select_a & select_b;
		
		//CALCULATE OR
		int_or = select_a | select_b;
		
		//CALCULATE ADD
				
		//perform addition
		temp_add = select_a + select_b + cin;
		
		//partition results
		int_add = temp_add[0];
		cout = temp_add[1];
		
		//Set value for SET output
		set = int_add;

		//SET RESULT
		case (op)
			2'b 00 : begin
				result = int_and;
			end
			
			2'b 01 : begin
				result = int_or;
			end
			
			2'b 10 : begin
				result = int_add;
			end
			
			2'b 11 : begin
				result = less;
			end
		endcase
	end
					
endmodule