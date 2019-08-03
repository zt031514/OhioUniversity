`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:38:45 11/30/2017 
// Design Name: 
// Module Name:    Control_tb 
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
module Control_tb();
reg [5:0] opcode_tb;
wire ALUSrc_tb, RegDst_tb, MemWrite_tb, MemRead_tb, Branch_tb, Jump_tb, MemToReg_tb, RegWrite_tb;
wire  [1:0] ALUOp_tb; 

Control Conrol_1(opcode_tb, ALUSrc_tb, ALUOp_tb, RegDst_tb, MemWrite_tb, MemRead_tb, Branch_tb
						, Jump_tb, MemToReg_tb, RegWrite_tb);

initial
begin

	//case 000000
	opcode_tb <= 6'b000010;
	#1 $display("RegDst = %b", RegDst_tb); 
	
end
endmodule
