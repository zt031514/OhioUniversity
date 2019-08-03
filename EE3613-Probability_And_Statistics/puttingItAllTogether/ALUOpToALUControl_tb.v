`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:27:54 11/30/2017 
// Design Name: 
// Module Name:    ALUOpToALUControl_tb 
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
module ALUOpToALUControl_tb();
reg [1:0] ALUOp_tb;
reg [5:0] Funct_tb;
wire [3:0] ALUControl_tb;

ALUOpToALIControl Control_tb(ALUOp_tb, Funct_tb, ALUControl_tb);

initial
begin

	//case 
	ALUOp_tb <= 2'b10; Funct_tb <= 6'b100000;
	#1 $display("ALUControl = %b", ALUControl_tb);
	
end
endmodule
