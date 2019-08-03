//******************************************************************
//
//  battle.h	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Helper functions for battle_client.cc
//
//	Note*: The client defined in this file and battle_client.cc is largely based on the 
//		   code provided by Dr. Juedes in battle_example.cc and rsp_client.cc.
//
//*****************************************************************

#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include "battle.h"
using namespace std;


//**************************************************************************************
// Function: clear_board()
//
// Brief: Clear the board to return it to its original state.
//
// Parameters: vector<vector<int> > &board | matrix containing the values for the board
//
// Return value: N/A
//
//**************************************************************************************
void clear_board(vector<vector<int> > &board){
	for(int i = 0; i < (int)(board.size()); i++){
		for(int j = 0; j < (int)(board.size()); j++){
			board[i][j] = 0;
		}
	}
}


//**************************************************************************************
// Function: is_legal()
//
// Brief: Determine whether the given ship is legal or if it falls off the board.
//
// Parameters: nextShip Ship | struct containing the coordinates of the ship
//			   int size | square size of the board
//
// Return value: True if the ship is on the board, false otherwise
//
//**************************************************************************************
bool is_legal(nextShip ship, int size){
	if(ship.x3 < size && ship.x3 >= 0 && ship.y3 < size && ship.y3 >= 0){
		if(ship.x2 < size && ship.x2 >= 0 && ship.y2 < size && ship.y2 >= 0){
			return true;
		} else{
			return false;
		}
	} else {
		return false;
	}
}


//**************************************************************************************
// Function: convert_ship()
//
// Brief: Take a ship's coordinates and convert to an integer for network transfer
//
// Parameters: nextShip Ship | struct containing the coordinates of the ship
//
// Return value: ship_sum, the encoded ship coordinates as an integer
//
//**************************************************************************************
int convert_ship(nextShip ship){
	int ship_sum = 0;

	ship_sum += ship.x1 * SHIP_X1;
	ship_sum += ship.y1 * SHIP_Y1;
	ship_sum += ship.x2 * SHIP_X2;
	ship_sum += ship.y2 * SHIP_Y2;
	ship_sum += ship.x3 * SHIP_X3;
	ship_sum += ship.y3 * SHIP_Y3;

	return ship_sum;
}

//**************************************************************************************
// Function: convert_move()
//
// Brief: Takes a move in the form of a row and column and converts it to a single number
//
// Parameters: int cur_row | the row of the desired attack point
//			   int cur_col | the column of the desired attack point
//
// Return value: move_sum, the encoded move coordinates as an integer
//
//**************************************************************************************
int convert_move(int row, int col){
	int move_sum = 0;

	move_sum += row * 10;
	move_sum += col;

	return move_sum;
}


//**************************************************************************************
// Function: is_hit
//
// Brief: Takes a move and a board and returns whether the board has a ship at that position
//
// Parameters: Move move | struct containing the coordinates of the move
//			   vector<vector<int> > board | board containing a ship
//
// Return value: true if board[x][y] is 1 (a ship), false otherwise
//
//**************************************************************************************
bool is_hit(Move move, vector<vector<int> > board){
	if(board[move.x][move.y] == 1){
		return true;
	}
	else{
		return false;
	}
}

#endif