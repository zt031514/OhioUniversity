`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:21:44 11/28/2017 
// Design Name: 
// Module Name:    Mux5Bit2To1 
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
module Mux5Bit2To1(a, b, op, result);

input [4:0] a, b; // 5-bit inputs
input op; // one-bit selection input
output [4:0] result; // 5-bit output
reg [4:0] result; 

always @(*)
begin
	if (op ==0)
		result = a;
	else
		result = b;
end

endmodule
