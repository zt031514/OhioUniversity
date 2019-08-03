//******************************************************************
//
//  rotate.h	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Contains the functions to rotate a ship left and right.
//				
//
//	Note*: The client defined in this file and battle_client.cc is largely based on the 
//		   code provided by Dr. Juedes in battle_example.cc and rsp_client.cc.
//
//*****************************************************************

#ifndef ROTATE_H
#define ROTATE_H

#include <vector>
#include "battle.h"
using namespace std;

//**************************************************************************************
// Function: rotate_left()
//
// Brief: Ship has been placed on the board; now the user trying to change its orientation.
//		  This function finds the next legal rotation of the ship to the left (clockwise), and changes
//		  the board to reflect the rotation.
//
// Parameters: vector<vector<int> > &board | matrix containing the values for the board
//			   int row | user specified row to begin ship placement
//			   int col | user specified col to begin ship placement
//			   Direction &orientation | current direction the ship is pointing
//
// Return value: N/A
//
//**************************************************************************************
nextShip rotate_left(vector<vector<int> > &board, int row, int col, Direction &orientation){

	Direction newDir;
	nextShip ship;
	ship.x1 = row;
	ship.y1 = col;

	switch(orientation){
		case ::down_right: // Check if the ship is legal when placed in the "right" position
			ship.x2 = row;
			ship.y2 = col + 1;
			ship.x3 = row;
			ship.y3 = col + 2;
			newDir = ::right;
			break;
		case ::right: // check if the ship is legal when placed in the up-right position
			ship.x2 = row - 1;
			ship.y2 = col + 1;
			ship.x3 = row - 2;
			ship.y3 = col + 2;
			newDir = ::up_right;
			break;
		case ::up_right: // check if the ship is legal when placed in the up position
			ship.x2 = row - 1;
			ship.y2 = col;
			ship.x3 = row - 2;
			ship.y3 = col;
			newDir = ::up;
			break;
		case ::up: //check if the ship is legal in the up-left position
			ship.x2 = row - 1;
			ship.y2 = col - 1;
			ship.x3 = row - 2;
			ship.y3 = col - 2;
			newDir = ::up_left;
			break;
		case ::up_left: //check if the ship is legal in the left position
			ship.x2 = row;
			ship.y2 = col - 1;
			ship.x3 = row;
			ship.y3 = col - 2;
			newDir = ::left;
			break;
		case ::left: // check if the ship is legal in the down-left position
			ship.x2 = row + 1;
			ship.y2 = col - 1;
			ship.x3 = row + 2;
			ship.y3 = col - 2;
			newDir = ::down_left;
			break;
		case ::down_left: // check if the ship is legal in the down position
			ship.x2 = row + 1;
			ship.y2 = col;
			ship.x3 = row + 2;
			ship.y3 = col;
			newDir = ::down;
			break;
		case ::down: // check if the ship is legal in the down-right position
			ship.x2 = row + 1;
			ship.y2 = col + 1;
			ship.x3 = row + 2;
			ship.y3 = col + 2;
			newDir = ::down_right;
			break;
	}

	orientation = newDir;
	return ship;
}


//**************************************************************************************
// Function: rotate_right()
//
// Brief: Ship has been placed on the board; now the user trying to change its orientation.
//		  This function finds the next legal rotation of the ship to the right (counterclockwise), and changes
//		  the board to reflect the rotation.
//
// Parameters: vector<vector<int> > &board | matrix containing the values for the board
//			   int row | user specified row to begin ship placement
//			   int col | user specified col to begin ship placement
//			   Direction &orientation | current direction the ship is pointing
//
// Return value: N/A
//
//**************************************************************************************
nextShip rotate_right(vector<vector<int> > &board, int row, int col, Direction &orientation){

	Direction newDir;
	nextShip ship;
	ship.x1 = row;
	ship.y1 = col;

	switch(orientation){
		case ::down_right: // Check if the ship is legal when placed in the down position
			ship.x2 = row + 1;
			ship.y2 = col;
			ship.x3 = row + 2;
			ship.y3 = col;
			newDir = ::down;
			break;
		case ::down: // check if the ship is legal when placed in the down-left position
			ship.x2 = row + 1;
			ship.y2 = col - 1;
			ship.x3 = row + 2;
			ship.y3 = col - 2;
			newDir = ::down_left;
			break;
		case ::down_left: // check if the ship is legal when placed in the left position
			ship.x2 = row;
			ship.y2 = col - 1;
			ship.x3 = row;
			ship.y3 = col - 2;
			newDir = ::left;
			break;
		case ::left: //check if the ship is legal in the up-left position
			ship.x2 = row - 1;
			ship.y2 = col - 1;
			ship.x3 = row - 2;
			ship.y3 = col - 2;
			newDir = ::up_left;
			break;
		case ::up_left: //check if the ship is legal in the up position
			ship.x2 = row - 1;
			ship.y2 = col;
			ship.x3 = row - 2;
			ship.y3 = col;
			newDir = ::up;
			break;
		case ::up: // check if the ship is legal in the up-right position
			ship.x2 = row - 1;
			ship.y2 = col + 1;
			ship.x3 = row - 2;
			ship.y3 = col + 2;
			newDir = ::up_right;
			break;
		case ::up_right: // check if the ship is legal in the right position
			ship.x2 = row;
			ship.y2 = col + 1;
			ship.x3 = row;
			ship.y3 = col + 2;
			newDir = ::right;
			break;
		case ::right: // check if the ship is legal in the down-right position
			ship.x2 = row + 1;
			ship.y2 = col + 1;
			ship.x3 = row + 2;
			ship.y3 = col + 2;
			newDir = ::down_right;
			break;
	}

	orientation = newDir;
	return ship;
}

#endif