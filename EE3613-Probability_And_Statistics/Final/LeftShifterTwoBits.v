`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:57:19 12/01/2017 
// Design Name: 
// Module Name:    LeftShifterTwoBits 
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
module LeftShifterTwoBits(ValueIn, ValueOut);
input [25:0] ValueIn; // 26-bit input
output [27:0] ValueOut; // 28-bit output\
reg [27:0] ValueOut;

always @(*)
begin
	assign ValueOut = {ValueIn, 2'b00}; 
end
endmodule

