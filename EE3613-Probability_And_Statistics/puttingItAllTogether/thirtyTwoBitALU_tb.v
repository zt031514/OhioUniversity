`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:23:00 12/04/2017 
// Design Name: 
// Module Name:    thirtyTwoBitALU_tb 
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
module thirtyTwoBitALU_tb();

	reg[31:0] a;
	reg[31:0] b;
	reg[3:0] op;
	reg clk;

	wire[31:0] result;
	wire cout;
	wire zero;

	thirtyTwoBitALU uut (.a(a), .b(b), .op(op), .result(result), .cout(cout), .zero(zero));
	initial
		begin
		a = 32'b 0;
		b = 32'b 0;
		op = 4'b 0010;
		clk = 0;
		
		
			//Test AND
			@(posedge clk); 
			#1 $display("AND: %b", result);
			
		end

endmodule
