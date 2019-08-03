`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:38:42 11/28/2017 
// Design Name: 
// Module Name:    tb_signExt 
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
module tb_signExt(
    );

reg [15:0] a_tb;
reg [31:0] result_tb;

SignExtension tb_se (.a(a_tb), .result(result_tb));

initial
begin
	a_tb = 16'b0000_0000_0000_0000;
end

initial 
begin
	#10 a_tb = 16'b0000_0000_1111_1111;
end
endmodule
