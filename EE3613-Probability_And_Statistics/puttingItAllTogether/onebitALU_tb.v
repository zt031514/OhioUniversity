`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:56:46 10/25/2017 
// Design Name: 
// Module Name:    ALU_tb 
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
module ALU_tb();

//inputs
reg a;
reg b;
reg cin;
reg ainv;
reg binv;
reg less;
reg[0:1] op;
reg clk;

//outputs
wire result;
wire cout;
wire set;

//new module
OneBitALU uut (.a(a), .b(b), .cin(cin), .ainv(ainv), .binv(binv), .less(less), .op(op), .result(result), .cout(cout), .set(set));
initial

	begin
		//Init inputs
		a = 0;
		b = 0;
		cin = 0;
		ainv = 0;
		binv = 0;
		less = 0;
		op = 2'b 00;
		clk = 0;
		
		//Test AND
		@(posedge clk); a = 0;
		#1 $display("A & B is %b", result);
		@(posedge clk); b = 1;
		#1 $display("A & B is %b", result);
		@(posedge clk); a = 1; b = 0;
		#1 $display("A & B is %b", result);
		@(posedge clk); b = 1; cin = 0;
		#1 $display("A & B is %b", result);
	
		//Test NOR
		@(posedge clk); a = 0; b = 0; op = 2'b 00; ainv = 1; binv = 1;
		#1 $display("NOR is %b", result);
		@(posedge clk); a = 1;
		#1 $display("NOR is %b", result);
		@(posedge clk); a = 0; b = 1;
		#1 $display("NOR is %b", result);
		@(posedge clk); a = 1;
		#1 $display("NOR is %b", result);
		
		//Test OR
		@(posedge clk); a = 0; b = 0; op = 2'b 01; ainv = 0; binv = 0;
		#1 $display("A | B is %b", result);
		@(posedge clk); a = 1;
		#1 $display("A | B is %b", result);
		@(posedge clk); a = 0; b = 1;
		#1 $display("A | B is %b", result);
		@(posedge clk); a = 1;
		#1 $display("A | B is %b", result);
		
		//Test ADD
		@(posedge clk); a = 0; b = 0; op = 2'b 10;
		#1 $display("ADD is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); a = 1;
		#1 $display("ADD is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); a = 0; b = 1;
		#1 $display("ADD is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); a = 1;
		#1 $display("ADD is %b", result);
		#1 $display("Carry is %b", cout);
		
		//Test SUBTRACT
		@(posedge clk); a = 0; b = 0; binv = 1; op = 2'b 10; cin = 1;
		#1 $display("SUB is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); b = 1; 
		#1 $display("SUB is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); a = 1; b = 0;
		#1 $display("SUB is %b", result);
		#1 $display("Carry is %b", cout);
		@(posedge clk); b = 1;
		#1 $display("SUB is %b", result);
		#1 $display("Carry is %b", cout);
		
	end
	
	always
	begin
		clk = ! clk; #1;
	end

endmodule
