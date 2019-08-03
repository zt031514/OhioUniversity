`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:53:45 12/01/2017 
// Design Name: 
// Module Name:    PCAdder 
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
module PCAdder(PCIn, PCOut);
input [31:0] PCIn; // 32-bit address
output [31:0] PCOut; // input incremented by 4

reg [31:0] PCOut;

always @(*)
begin
	assign PCOut = PCIn +4;
end
endmodule
