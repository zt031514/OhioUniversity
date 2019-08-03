`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:49:42 12/04/2017 
// Design Name: 
// Module Name:    dataMemory 
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

module dataMemory(Address, WriteData, MemRead, MemWrite, Clk, ReadData);

	input [31:0] Address; // 32-bit address to memory.
	input [31:0] WriteData; // Data to be written into WriteRegister
	input MemRead; // Data in memory location Address is read if this control is set
	input MemWrite; // WriteData is written in Address during positive clock edge if this control is set
	input Clk; // very important!
	output[31:0] ReadData;// Value read from memory location Ad
	reg [31:0] ReadData; //temp read data

	reg [19:0] tb_Address; // 20 bit word address converted from 32 bit address
	reg [31:0] dataMem [0:`SIZE]; //2^20 32-bit memory locations
	reg [31:0] i;	//used to initialize memory
	
initial
begin
		
end

always @(posedge Clk)
begin

	//to find 20 bit word address, ignore right 2 bits (byte address), and take bits 3 through 22
	tb_Address = Address[21:2];
	
	if	(MemWrite == 1)
		begin
			dataMem[tb_Address] = WriteData;
		end
end

always @(negedge Clk)
	begin		
		//to find 20 bit word address, ignore right 2 bits (byte address), and take bits 3 through 22
	   tb_Address = Address[21:2];
		
		if(MemRead == 1)begin
			ReadData = dataMem[tb_Address];
		end
	end
	
endmodule
