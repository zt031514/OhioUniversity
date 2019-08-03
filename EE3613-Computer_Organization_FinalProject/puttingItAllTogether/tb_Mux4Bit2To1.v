`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:04:27 11/30/2017 
// Design Name: 
// Module Name:    tb_Mux4Bit2To1 
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
module tb_Mux4Bit2To1();
reg [4:0] a_tb, b_tb;
reg op_tb;
wire [4:0] result_tb;

Mux5Bit2To1 Mux5 (a_tb, b_tb, op_tb, result_tb);

initial
begin
a_tb <= 5'b00000; b_tb <= 5'b111111; op_tb <= 1; 
#1 $display("Result = %d", result_tb); 

end
endmodule
