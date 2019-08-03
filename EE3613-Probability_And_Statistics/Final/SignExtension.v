`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:20:23 11/28/2017 
// Design Name: 
// Module Name:    SignExtension 
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
module SignExtension(a, result);

input [15:0] a; // 16-bit input
output [31:0] result; // 32-bit output

reg[31:0] result;

always @(*)
begin
assign result = {{16{a[15]}}, a};
end

endmodule
