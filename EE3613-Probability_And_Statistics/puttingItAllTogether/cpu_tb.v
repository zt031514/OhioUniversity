`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:17:44 12/04/2017 
// Design Name: 
// Module Name:    cpu_tb 
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
module cpu_tb();

reg pcClk;
reg clk;

ee3613cpu uut (.pcClk(pcClk), .clk(clk));
	initial
		begin
			pcClk = 0;
			clk = 0;
		end

always
	begin
		pcClk = ! pcClk; #5;
	end
	
always
	begin
		clk = ! clk; #1;
	end

endmodule
