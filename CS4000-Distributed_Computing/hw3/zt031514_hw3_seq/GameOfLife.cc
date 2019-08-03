//**********************************************
//
//	gameOfLife.h
//
//	Author: Zach Tumbleson
//
//	Date:   02-24-2019
//	
//	Description: Implements the function that
//				 simulates the Game of Life
//
//**********************************************

#include "GameOfLife.h"
#include <assert.h>

//******************************************************************************
// Function: SimulateLife()
//
// Passes the board to newBoard
// and decrements the number of
// remaining life cycles.
//
// Parameters: board, a 2D vector of type int passed by reference
//			   life_cycles, the number of life cycles to be simulated as an int
//
// Return value: the board corresponding to the number of simulated life_cycles
//				 returned as a 2D int vector
//
//*******************************************************************************
vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){

	//get dimensions of the board
	int height = (int) board.size();
	int width = (int) board[0].size();
	
	assert(height == width);

	while(life_cycles > 0){
		newBoard(board);
		life_cycles -= 1;
	}

	return board;
}

//******************************************************************************
// Function: newBoard()
//
// Returns the next board based on the board that is passed in.
//
// Parameters: board, a 2D vector of type int passed by reference
//
//
// Return value: None
//
//*******************************************************************************
void GameOfLife::newBoard(vector<vector<int> >&board){

	//cast size as an int to avoid for loop comparison warnings
	int size = (int) board.size();

	const int OVERPOPULATED = 4;
	const int LONELY = 1;
	const int BORN = 3;

	enum state {dead, alive, eternal};

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			
			int numNeighbors = getNumNeighbors(board, i, j);
			int status = board[i][j];

			switch(status){
				case dead: //if neighbor is dead and 3 neighbors are alive
							// a new cell is born
						if(numNeighbors == BORN){
							board[i][j] = alive;
						}
						break;
				case alive: //if cell has more than 4 or less than 2 neighbors, it dies
						if(numNeighbors >= OVERPOPULATED || numNeighbors <= LONELY){
							board[i][j] = dead;
						}
						break;
				case eternal: //eternal cells cannot die
						break;
			}
		}
	}
}

//******************************************************************************
// Function: getNumNeighbors()
//
// Finds the number of alive neighbors that a given cell has
//
// Parameters: board, a 2D vector of type int passed by reference
//			   row, an int specifying the row of the current cell
//			   col, an int specifying the column of the current cell
//
// Return value: the number of live neighbors for board[row][col] as an int
//
//*******************************************************************************
int GameOfLife::getNumNeighbors(vector<vector<int> > &board, int row, int col){
	int numNeighbors = 0;

	enum state {dead, alive, eternal};

	int n = (int) board.size();

	if(board[((n+row+1) % n)][col] == alive){numNeighbors++;}
	if(board[((n+row-1) % n)][col] == alive){numNeighbors++;}
	if(board[((n+row-1) % n)][(n+col+1)%n] == alive){numNeighbors++;}
	if(board[((n+row-1) % n)][(n+col-1)%n] == alive){numNeighbors++;}
	if(board[((n+row+1) % n)][(n+col+1)%n] == alive){numNeighbors++;}
	if(board[((n+row+1) % n)][(n+col-1)%n] == alive){numNeighbors++;}
	if(board[row][(n+col+1) % n] == alive){numNeighbors++;}
	if(board[row][(n+col-1) % n] == alive){numNeighbors++;}

	return numNeighbors;
}