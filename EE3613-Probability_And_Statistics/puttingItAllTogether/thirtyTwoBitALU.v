`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:15:35 12/04/2017 
// Design Name: 
// Module Name:    thirtyTwoBitALU 
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
module thirtyTwoBitALU(a, b, op, result, cout, zero);

		//inputs
	input [31:0] a;
	input [31:0] b;  
	input [3:0] op; //LSB is op[0], op[3] is ainv, op[2] is binv, op[0:1] is op code
	
	output [31:0] result;
	output cout;
	output zero;
	reg zero;
	
	initial
	begin
			#1 $display("Input 1 is %d", a);
			#1 $display("Input 2 is %d", b);
	end
	
	
	//Used for error workaround
	reg disconnected;

	wire cout1; // Carry out bit from 8th adder to 9th adder

	wire msb_set; //wire from msb set to lsb less input
		
		sixteenBitALU block1_8(a[15:0], b[15:0], op, result[15:0], cout1, msb_set, disconnected );
		sixteenBitALU block9_16(a[31:16], b[31:16], op, result[31:16], cout, disconnected, msb_set);
		
always @result
	begin
		if(result == 32'b 0)begin
			zero = 1;
		end
		
		else
		begin
			zero = 0;
		end
		
		$display("Result is %d", result);
end
			
endmodule
