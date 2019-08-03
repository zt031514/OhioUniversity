`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:23:09 11/28/2017 
// Design Name: 
// Module Name:    Control 
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
module Control(opcode, ALUSrc, ALUOp, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite);

input [5:0] opcode; // 6-bit opertion code

output  ALUSrc, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite; //Output control lines
output [1:0] ALUOp; // 2-bit intermediate output for controlling ALU

reg  ALUSrc, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite;
reg [1:0] ALUOp; 

always @(opcode)
begin
case (opcode)
		6'b000000: 	begin
					RegDst = 1'b1;
					ALUSrc = 1'b0;
					MemToReg = 1'b0; 
					RegWrite = 1'b1;
					MemRead = 1'b0;
					MemWrite = 1'b0;
					Branch = 1'b0;
					ALUOp = 2'b10;
					Jump = 1'bx; 
					end
					
		6'b100011:	begin
					RegDst = 1'b0;
					ALUSrc = 1'b1;
					MemToReg = 1'b1;
					RegWrite = 1'b1;
					MemRead = 1'b1;
					MemWrite = 1'b0;
					Branch = 1'b0;
					ALUOp = 2'b00;
					Jump = 1'bx; 
					end
					
		6'b101011:	begin	
					RegDst = 1'bx;
					ALUSrc = 1'b1;
					MemToReg = 1'bX;
					RegWrite = 1'b0;
					MemRead = 1'b0;
					MemWrite = 1'b1;
					Branch = 1'b0;
					ALUOp = 2'b00;
					Jump = 1'bx; 
					end
					
		6'b000100: 	begin
					RegDst = 1'bx;
					ALUSrc = 1'b0;
					MemToReg = 1'bx;
					RegWrite = 1'b0;
					MemRead = 1'b0;
					MemWrite = 1'b0;
					Branch = 1'b1;
					ALUOp = 2'b01;
					Jump = 1'bx; 
					end
					
		6'b000010:	begin 
					Jump = 1'b1;
					end	
endcase	
end				
endmodule
