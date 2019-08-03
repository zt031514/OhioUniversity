`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:11:48 11/29/2017 
// Design Name: 
// Module Name:    RegisterFile 
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
module RegisterFile(ReadRegister1, ReadRegister2, WriteRegister, WriteData, RegWrite,
Clk, ReadData1, ReadData2);

input [4:0] ReadRegister1, ReadRegister2; // Two registers to be read
input [4:0] WriteRegister; // Register address to write into
input [31:0] WriteData; // Data to be written into WriteRegister
input RegWrite; // RegWrite control signal. Data is written only when this signal is enabled
input Clk; // very important!
output [31:0] ReadData1, ReadData2;


reg [31:0] ReadData1, ReadData2;
reg [31:0] Registers [0:31]; // 32x32 bit registers 

initial
begin
		Registers[0] <= 32'h00000000;
		Registers[1] <= 32'hAAAAAAAA;
		Registers[2] <= 32'hBBBBBBBB;
		Registers[3] <= 32'h00000000;
		Registers[4] <= 32'h00000000;
		Registers[5] <= 32'h00000000;
		Registers[6] <= 32'h00000000;
		Registers[7] <= 32'h00000000;
		Registers[8] <= 32'h00000000;
		Registers[9] <= 32'h00000000;
		Registers[10] <= 32'h00000000;
		Registers[11] <= 32'h00000000;
		Registers[12] <= 32'h00000000;
		Registers[13] <= 32'h00000000;
		Registers[14] <= 32'h00000000;
		Registers[15] <= 32'h00000000;
		Registers[16] <= 32'h00000000;
		Registers[17] <= 32'h00000000;
		Registers[18] <= 32'h00000000;
		Registers[19] <= 32'h00000000;
		Registers[20] <= 32'h00000000;
		Registers[21] <= 32'h00000000;
		Registers[22] <= 32'h00000000;
		Registers[23] <= 32'h00000000;
		Registers[24] <= 32'h00000000;
		Registers[25] <= 32'h00000000;
		Registers[26] <= 32'h00000000;
		Registers[27] <= 32'h00000000;
		Registers[28] <= 32'h00000000;
		Registers[29] <= 32'h00000000;
		Registers[30] <= 32'h00000000;
		Registers[31] <= 32'h00000000;

end
always @(posedge Clk)
begin
	if	(RegWrite ==1)
		begin
			Registers[WriteRegister] <= WriteData;
		end
end

always @(negedge Clk)
	begin
		ReadData1 <= Registers[ReadRegister1];
		
		ReadData2 <= Registers[ReadRegister2];
		
	end
endmodule
