`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:04:22 12/03/2017 
// Design Name: 
// Module Name:    sixteenBitALU 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sixteenBitALU(a, b, op, result, cout, less, set);

		//inputs
	input [15:0] a;
	input [15:0] b;  
	input [3:0] op; //LSB is op[0], op[3] is ainv, op[2] is binv, op[0:1] is op code
	input less;
	
	output [15:0] result;
	output cout;
	output set;
	
	//Used for error workaround
	reg disconnected;

	wire cout1; // Carry out bit from 4th adder to 5th adder
	wire cout2; // " from 8th adder to 9th adder
	wire cout3; // " from 12th adder to 13th adder
		
		fourBitALU block1_4(a[3:0], b[3:0], op, result[3:0], cout1, less, disconnected);
		fourBitALU block5_8(a[7:4], b[7:4], op, result[7:4], cout2, disconnected, disconnected);
		fourBitALU block9_12(a[11:8], b[11:8], op, result[11:8], cout3, disconnected, disconnected);
		fourBitALU block13_16(a[15:12], b[15:12], op, result[15:12], cout, disconnected, set);

endmodule
