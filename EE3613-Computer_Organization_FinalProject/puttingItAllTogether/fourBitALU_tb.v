`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:25:22 10/25/2017 
// Design Name: 
// Module Name:    fourBitALU_tb 
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
module fourBitALU_tb();

	reg[3:0] a;
	reg[3:0] b;
	reg[3:0] op;
	reg clk;

	wire[3:0] result;
	wire cout;
	wire zero;

	fourBitALU uut (.a(a), .b(b), .op(op), .result(result), .cout(cout), .less(less), .set(set));
	initial
		begin
		a = 4'b 0000;
		b = 4'b 0000;
		op = 4'b 0000;
		clk = 0;
		less = 0;
		set = 0;
		
		
			//Test AND
			@(posedge clk); a = 4'b 0000; b = 4'b 0000; op = 4'b 0000;
			#1 $display("AND: %b", result);
			@(posedge clk); a = 4'b 0111; b = 4'b 0111; op = 4'b 0000;
			#1 $display("AND: %b", result);
			@(posedge clk); a = 4'b 0010; b = 4'b 1000; op = 4'b 0000;
			#1 $display("AND: %b", result);
			@(posedge clk); a = 4'b 0101; b = 4'b 1010; op = 4'b 0001;
			#1 $display("OR: %b", result);
			@(posedge clk); a = 4'b 0111; b = 4'b 0001; op = 4'b 0001;
			#1 $display("OR: %b", result);
			@(posedge clk); a = 4'b 0100; b = 4'b 0010; op = 4'b 0010;
			#1 $display("4+2: %d", result);
			@(posedge clk); a = 4'b 0001; b = 4'b 0001; op = 4'b 0010;
			#1 $display("1+1: %d", result);
			@(posedge clk); a = 4'b 0100; b = 4'b 0011; op = 4'b 0110;
			#1 $display("4-3: %d", result);
			@(posedge clk); a = 4'b 0110; b = 4'b 0000; op = 4'b 0110;
			#1 $display("6-0: %d", result);
			@(posedge clk); a = 4'b 0000; b = 4'b 0000; op = 4'b 0010;
			#1 $display("0+0: %d", result);
			@(posedge clk); a = 4'b 0010; b = 4'b 0111; op = 4'b 0111;
			#1 $display("2 < 7?: %b", result);
			@(posedge clk); a = 4'b 0111; b = 4'b 0000; op = 4'b 0111;
			#1 $display("7 < 0?: %b", result);
			@(posedge clk); a = 4'b 0100; b = 4'b 0100; op = 4'b 0111;
			#1 $display("4 < 4?: %b", result);
		end

	always
		begin
				clk = ! clk; #1;
		end
endmodule

