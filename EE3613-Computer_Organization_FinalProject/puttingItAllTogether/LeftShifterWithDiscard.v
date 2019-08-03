`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:01:13 12/01/2017 
// Design Name: 
// Module Name:    LeftShifterWithDiscard 
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
module LeftShifterWithDiscard(ValueIn, ValueOut );
input [31:0] ValueIn; // 32-bit input
output [31:0] ValueOut; // lower 30 bits of input concatenated with two zeroes
reg [31:0] ValueOut;

always @(*)
begin
	assign ValueOut = {ValueIn[29:0], 2'b00}; 
end
endmodule

