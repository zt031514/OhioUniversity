`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:20:58 11/28/2017 
// Design Name: 
// Module Name:    Mux32Bit2To1 
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
module Mux32Bit2To1(a, b, op, result);

input [31:0] a, b; // 32-bit inputs
input op; // one-bit selection input
output [31:0] result; // 32-bit output
reg [31:0] result;
always @(a or b or op)
begin
	case(op)
		1'b 0: begin
			result = a;
		end
	
		1'b 1: begin
			result = b;
		end	
	endcase 
end

endmodule
