//**************************************************************************
//
//  server_helpers.cc	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Helper functions for the battleship server defined in
//		   battle_server.cc
//
//***************************************************************************

#ifndef SERVER_HELPERS_H
#define SERVER_HELPERS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>
#include <string>
#include "battle.h"
using namespace std;


//**************************************************************************************
// Function: getBoard()
//
// Brief: Takes an integer representing a ship and creates the rest of the gaeme board
//
// Parameters: int ship_int | integer representing the coordinates of the ship
// Return value: vector<vector<int> > board | matrix of the game board with the ship placed on it
//
//**************************************************************************************
vector<vector<int> > getBoard(int ship_int){
	vector<vector<int>> board;

	nextShip ship;

	//Decode ship_int as the ship position
	ship.x1 = ship_int / SHIP_X1;
	ship_int = ship_int % SHIP_X1;

	ship.y1 = ship_int / SHIP_Y1;
	ship_int = ship_int % SHIP_Y1;

	ship.x2 = ship_int / SHIP_X2;
	ship_int = ship_int % SHIP_X2;

	ship.y2 = ship_int / SHIP_Y2;
	ship_int = ship_int % SHIP_Y2;

	ship.x3 = ship_int / SHIP_X3;
	ship_int = ship_int % SHIP_X3;

	ship.y3 = ship_int / SHIP_Y3;
	ship_int = ship_int % SHIP_Y3;

	if(ship_int != 0)
		cout << "Error\n";

	//Initialize an empty board
	vector<vector<int> > my_board, opp_board;
    for (int i=0;i<4;i++) {
    	vector<int> t;
    	for (int j=0;j<4;j++) {
    		t.push_back(0);
    	}
    	board.push_back(t);
    }

    board[ship.x1][ship.y1] = 1;
    board[ship.x2][ship.y2] = 1;
    board[ship.x3][ship.y3] = 1;

	return board;
}

//**************************************************************************************
// Function: get_move()
//
// Brief: takes an encoded move integer and returns it as a Move object
//
// Parameters: int move_int | integer representing the move coordinates
//
// Return value: Move move | contains the x and y coordinates of the move on the board
//
//**************************************************************************************
Move get_move(int move_int){
	Move move;

	move.x = move_int / 10;
	move_int = move_int % 10;
	move.y = move_int;

	return move;
}


//**************************************************************************************
// Function: is_hit()
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