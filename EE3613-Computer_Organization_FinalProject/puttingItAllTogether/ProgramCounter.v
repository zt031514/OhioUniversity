`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:50:55 12/01/2017 
// Design Name: 
// Module Name:    ProgramCounter 
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
module ProgramCounter(PCIn, Clk, PCOut);
input [31:0] PCIn; // 32-bit address
input Clk; // PC is updated on each posedge of Clk. Period may be longer than regular clock!
output [31:0] PCOut; // 32-bit address

reg [31:0] PCOut;

//always @(posedge Clk)
//begin
//	assign PCOut = PCIn; 
//end
initial
begin
PCOut = 32'h 00001000;
end

endmodule 