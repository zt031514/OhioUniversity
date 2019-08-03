`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:15:44 12/04/2017 
// Design Name: 
// Module Name:    ee3613cpu 
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
module ee3613cpu(pcClk, clk);
	input pcClk; //slower clock
	input clk;   //faster clock for datapath
	
	wire [31:0] jumpToPC; //wire from jump mux to pc In
	wire [31:0] pcOut;   //wire from PC to Instruction Memory
	wire [31:0] Instruction;	 //wire containing instruction from Inst. Mem.
	wire ALUsrc;
	wire [1:0] ALUOp;
	wire RegDst;
	wire MemWrite;
	wire MemRead;
	wire Branch;
	wire Jump;
	wire MemToReg;
	wire RegWrite;
	wire [4:0] RegDstMux; //Wire from mux to determine write reg address
	wire [31:0] Writeback; //output from MemtoReg MUX
	wire [31:0] RD1; // Read Data 1 output from register file
	wire [31:0] RD2; // Read Data 2 output from register file
	wire [31:0] ALUSrcMux; //wire from ALUSrc mux to ALU input 2
	wire [31:0] signExtOut; //Output of sign extension module
	wire [3:0] ALUCtrl; // Wire from ALU control module to ALU
	wire overflow; //overflow bit from ALU
	wire zero; //zero output from ALU
	wire [31:0] ALUResult;
	wire [31:0] pcAdderOut; //Output of PC adder ALU
	wire [31:0] dMemOut; //Output from data memory	
	wire [31:0] shiftLeftOut; //output of shifting left
	wire [31:0] branchAddress;
	wire [31:0] jumpAddress;
	
	//Top Program Counter Block
	ProgramCounter PC(jumpToPC, pcClk, pcOut);
	PCAdder pcAdder(pcOut, pcAdderOut);
	LeftShifterTwoBits calcjumpAddress(Instruction[25:0], jumpAddress[27:0]); 
	assign jumpAddress[31:28] = pcAdderOut[31:28];
	
	//Critical Path
	InstructionMemory InstMem(pcOut, clk, Instruction);
	Control control(Instruction[31:26], ALUSrc, ALUOp, RegDst, MemWrite, MemRead, Branch, Jump, MemToReg, RegWrite);
	Mux5Bit2To1 RegDestMux(Instruction[20:16], Instruction[15:11], RegDst, RegDstMux); 
	RegisterFile RF(Instruction[25:21], Instruction[20:16], RegDstMux, Writeback, RegWrite, clk, RD1, RD2);
	SignExtension signExt(Instruction[15:0], signExtOut);
	Mux32Bit2To1 ALUsrcMux(RD2, signExtOut, ALUSrc, ALUSrcMux);
	ALUOpToALIControl calcALUCtrl(ALUOp, Instruction[5:0], ALUCtrl); 
	thirtyTwoBitALU ALU(RD1, ALUSrcMux, ALUCtrl, ALUResult, overflow, zero);
	dataMemory DMEM(ALUResult, RD2, MemRead, MemWrite, clk, dMemOut);
	Mux32Bit2To1 WBMux(ALUResult, dMemOut, MemToReg, Writeback);
	
	//Branching block
	LeftShifterWithDiscard shiftLeft2(signExtOut, shiftLeftOut);
	BEQAdderv branchAdder(pcAdderOut, shiftLeftOut, branchAddress);
	Mux32Bit2To1 pcMux(pcAdderOut, branchAddress, (Branch & zero), jumpToPC);
	

		
	
	
endmodule
