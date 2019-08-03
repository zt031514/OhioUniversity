`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:23:36 11/28/2017 
// Design Name: 
// Module Name:    ALUOpToALIControl 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:23:36 11/28/2017 
// Design Name: 
// Module Name:    ALUOpToALIControl 
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
module ALUOpToALIControl(ALUOp, Funct, ALUControl);
input [1:0] ALUOp; // from the above Control
input [5:0] Funct; // from the instruction
output [3:0] ALUControl; // to ALU (HW3B): {ainv, binv, op[1:0]}
reg	[3:0] ALUControl; 

always @(ALUOp) 
begin
case(ALUOp)
		2'b00:	begin
					ALUControl = 4'b0010;
					end
		
		2'b01:	begin
					ALUControl = 4'b0110;
					end
					
		2'b10:	begin
						case(Funct)
							6'b10_0000:	begin
											ALUControl = 4'b0010;
											end
							6'b10_0010:	begin
											ALUControl = 4'b0110;
											end
							6'b10_0100:	begin
											ALUControl = 4'b000;
											end
							6'b10_0101:	begin
											ALUControl = 4'b0001;
											end
							6'b10_1010:	begin
											ALUControl = 4'b0111;
											end
						endcase
					end
	endcase
	end
endmodule

