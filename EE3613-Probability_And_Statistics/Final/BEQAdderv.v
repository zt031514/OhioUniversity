`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:04:32 12/01/2017 
// Design Name: 
// Module Name:    BEQAdderv 
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
module BEQAdderv(ValueIn1, ValueIn2, ValueOut);
input [31:0] ValueIn1, ValueIn2; // 32-bit inputs
output [31:0] ValueOut; // sum of inputs
reg[31:0] ValueOut;

always @(*)
begin
	assign ValueOut = ValueIn1 + ValueIn2 + 4;
end
endmodule
