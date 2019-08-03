`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Ohio University
// Engineer: 	Zach Tumbleson
// 
// Create Date:    22:37:33 10/25/2017 
// Design Name: 
// Module Name:    fourBitALU 
// Project Name: EE 3613 Homework 3B #3
// Target Devices: 
// Tool versions: 
// Description: Implements a 4 bit ALU with the following operations:
//						AND,OR, ADD, SLT
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module fourBitALU(a, b, op, result, cout, less, set);
	//inputs
	input [3:0] a;
	input [3:0] b;  
	input [3:0] op; //LSB is op[0], op[3] is ainv, op[2] is binv, op[0:1] is op code
	input less; //less input bit
	
	output [3:0] result;
	output cout;
	output set;
	
	//used for error workaround
	reg disconnected;
	
	wire msb_set;   // Wire from MSB set to LSB less
	wire cout1; // Carry out bit from 1st adder
	wire cout2; // " from 2nd adder
	wire cout3; // " from 3rd adder
	
				   //a,  b,     cin,   ainv,  binv, less, op,    result,    cout,   set
	OneBitALU alu1(a[0], b[0], op[2], op[3], op[2], less, op[1:0], result[0], cout1, disconnected);
	OneBitALU alu2(a[1], b[1], cout1, op[3], op[2], disconnected, op[1:0], result[1], cout2, disconnected);
	OneBitALU alu3(a[2], b[2], cout2, op[3], op[2], disconnected, op[1:0], result[2], cout3, disconnected);
	OneBitALU alu4(a[3], b[3], cout3, op[3], op[2], disconnected, op[1:0], result[3], cout, set);
		
endmodule

