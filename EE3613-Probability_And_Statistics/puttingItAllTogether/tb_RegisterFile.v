`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:21:08 12/01/2017 
// Design Name: 
// Module Name:    tb_RegisterFile 
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
module tb_RegisterFile(  );
reg [4:0] ReadRegister1_tb, ReadRegister2_tb; // Two registers to be read
reg [4:0] WriteRegister_tb; // Register address to write into
reg [31:0] WriteData_tb; // Data to be written into WriteRegister
reg Clk_tb; // very important!
reg RegWrite_tb; // RegWrite control signal. Data is written only when this signal is enabled
wire [31:0] ReadData1_tb, ReadData2_tb;

RegisterFile registerfile(ReadRegister1_tb, ReadRegister2_tb, WriteRegister_tb, WriteData_tb, 
									RegWrite_tb, Clk_tb, ReadData1_tb, ReadData2_tb); 
									
initial
begin

	ReadRegister1_tb<= 5'b00001; ReadRegister2_tb <= 5'b00010; WriteRegister_tb <=00001; WriteData_tb <= 32'h11111111; 
	Clk_tb <= 0; RegWrite_tb <= 0; 

end

always 
	#5 Clk_tb =! Clk_tb; 
endmodule
