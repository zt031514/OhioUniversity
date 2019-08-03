`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:17:04 12/04/2017 
// Design Name: 
// Module Name:    instructionMemory 
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

`define SIZE 2**20 //Number of memory locations

module InstructionMemory(Address, Clk, Instruction);
	input [31:0] Address; // 32-bit address to memory.
	input Clk; // very important!
	
	output [31:0] Instruction;
	reg [31:0] Instruction;// Value read from memory location Address
	
	reg [31:0] instMem [0:`SIZE]; // Memory array for instructions
	reg [19:0] tb_Address; //20 bit address converted from 32-bit address
	reg [31:0] i; //used to initialize instruction memory
	
	
	initial
		begin
			instMem[20'b 00000000010000000000] = 32'b 0000_0010_0001_0001_0100_0000_0001_0000;	
		end
	
always @(posedge Clk)
	begin	
		tb_Address = Address[21:2];
	
		 
		Instruction = instMem[tb_Address];
		#1 $display("Reading %b from address %b", instMem[tb_Address], tb_Address);
	end

endmodule
	
