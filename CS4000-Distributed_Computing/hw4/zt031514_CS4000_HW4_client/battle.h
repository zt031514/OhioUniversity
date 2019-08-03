//******************************************************************
//
//  battle.h	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Contains functions to draw the board and place a ship in battle_client.cc
//		   and the enums and structs used.
//
//
//	Note*: The client defined in this file and battle_client.cc is largely based on the 
//		   code provided by Dr. Juedes in battle_example.cc and rsp_client.cc.
//
//*****************************************************************

#ifndef BATTLE_H
#define BATTLE_H

#include <ncurses.h>
#include <iostream>
#include <vector>
using namespace std;

// enum direction
//
// used to keep track of the direction the ship extends from
// its first point, using the following enumeration(proceeds clockwise):
//
//	Value |  Direction
//----------+-------------
//	  0	  |  down_right
//	  1	  |  	down
//	  2	  |	 down_left
//	  3	  |  	left
//	  4	  |    up_left
//	  5	  |	  	 up
//	  6	  |	  up_right
//	  7	  |     right
//
enum Direction {down_right = 0, down, down_left, left, up_left, up, up_right, right};


// struct passed to is_legal() function
// used to keep track of the 3 ship coordinates
// while the ship rotates
struct nextShip{
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
};

//struct used to pass a move between functions
//contains a single row and column value
struct Move{
	int x;
	int y;
};

//used for encoding ships as network messages
const int SHIP_X1 = 100000;
const int SHIP_Y1 = 10000;
const int SHIP_X2 = 1000;
const int SHIP_Y2 = 100;
const int SHIP_X3 = 10;
const int SHIP_Y3 = 1;

// offset factor used when drawing the second board
// to avoid drawing over the first
const int SECOND_BOARD = 10;

//**************************************************************************************
// Function: draw_top_matrix()
//
// Brief: Draws the matrix to be printed based on the changes in the board parameter
// 		  and moves the cursor to the current row and column given by the user
//
// Parameters: vector<vector<int> > &my_board | matrix containing the values for the users board
//			   vector<vector<int> > &opp_board | matrix containing the values for the opponents board
//			   int cur_row | row value of the underlying board
//			   int cur_col | column value of the underlying board
//			   bool placed | If a ship has already been placed, keep the cursor in the top (opponent's) board,
//							 otherwise, keep the cursor moving in the user's board
//
// Return value: N/A
//
//**************************************************************************************
void draw_top_matrix(vector<vector<int> > &my_board, vector<vector<int> > opp_board, int cur_row, int cur_col, bool placed) {
  
  // print the top line of the board
  for (int j=0;j<4;j++) {
      move(0,2*j);
      printw("+-");
  }
  // move to the end of the first line and print a plus
  move(0,2*4);
  printw("+");
  

  // print my board
  for (int i=0;i<4;i++) {
  	for (int j=0;j<4;j++) {
    	
    	// print a line 
    	move(2*i+1,2*j);
      	printw("|");
      	
      	// print each space according to the following table:
      	// board[i][j] |  Print
      	// ------------+----------------------
      	//		 0	   |	" " (empty)
      	//		 1	   |  	"X"	(ship)
      	//		 2	   |	"M" (shot missed)
      	//		 3	   |	"H"	(shot hit) 
      	//
      	move(2*i+1,2*j+1);  	
      	if (my_board[i][j] == 0) { //empty
			printw(" ");
      	
      	} else if(my_board[i][j] == 1){ // ship
			printw("X");
      	} else if(my_board[i][j] == 2){ // miss
      		printw("M");
      	} else { // board[i][j] == 3 - hit
      		printw("H");
      	}
    }

    // move to the end of the row and print a final vertical bar
    move(2*i+1,2*4);
    printw("|");

    // print the bottom line of the board
    for (int j=0;j<4;j++) {
      move(2*i+2,2*j);
      printw("+-");
    }
    // move to the end of the line and print a final plus
    move(2*i+2,2*4);
    printw("+");
  }

  //print the oppoent's board
  // print the top line of the board
  for (int j=0;j<4;j++) {
      move(10,2*j);
      printw("+-");
  }
  // move to the end of the first line and print a plus
  move(10,2*4);
  printw("+");
  
  for (int i=0;i<4;i++) {
  	for (int j=0;j<4;j++) {
    	
    	// print a line 
    	move(2*i+SECOND_BOARD+1,2*j);
      	printw("|");
      	
      	// print each space according to the following table:
      	// board[i][j] |  Print
      	// ------------+----------------------
      	//		 0	   |	" " (empty)
      	//		 1	   |  	"X"	(ship)
      	//		 2	   |	"M" (shot missed)
      	//		 3	   |	"H"	(shot hit) 
      	//
      	move(2*i+SECOND_BOARD+1,2*j+1);  	
      	if (opp_board[i][j] == 0) { //empty
			printw(" ");
      	
      	} else if(opp_board[i][j] == 1){ // ship
			printw("X");
      	} else if(opp_board[i][j] == 2){ // miss
      		printw("M");
      	} else { // board[i][j] == 3 - hit
      		printw("H");
      	}
    }

    // move to the end of the row and print a final vertical bar
    move(2*i+SECOND_BOARD+1,2*4);
    printw("|");

    // print the bottom line of the board
    for (int j=0;j<4;j++) {
      move(2*i+SECOND_BOARD+2,2*j);
      printw("+-");
    }
    // move to the end of the line and print a final plus
    move(2*i+SECOND_BOARD+2,2*4);
    printw("+");
  }
  
  // Convert current row and col on the stored board to
  // the row and col on the printed board and place the cursor there
  //
  //If ship has been placed, user does not need to edit their own board again
  if(placed){
  	move(2*cur_row + SECOND_BOARD+1,2*cur_col+1);
  } else{ //Ship has not been placed, keep the cursor on the user board
  	move(2*cur_row+1, 2*cur_col+1);
  }
}


//**************************************************************************************
// Function: place_ship()
//
// Brief: User has selected a space to place a ship. This function places the ship
//		  on the board, redraws the screen, and returns.
//
// Parameters: vector<vector<int> > &board | matrix containing the values for the board
//			   int row | user specified row to begin ship placement
//			   int col | user specified col to begin ship placement
//
// Return value: Returns the enumerated value of the direction the ship is pointing
//
//**************************************************************************************
Direction place_ship(vector<vector<int> > &board, int row, int col, nextShip &ship){
	

	// This function will try to place the ship diagonally to start,
	// or choose a different orientation if the ship will fall of the board
	Direction dir;

	switch(row){
		case 0:
			switch(col){
				case 0: // Valid, place diagonally
					board[row][col] = 1;
					board[row+1][col+1] = 1;
					board[row+2][col+2] = 1;
					dir = ::down_right;
					
					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row + 1;
					ship.y2 = col + 1;
					ship.x3 = row + 2;
					ship.y3 = col + 2;
					break;
				case 1: // Valid, place diagonally
					board[row][col] = 1;
					board[row+1][col+1] = 1;
					board[row+2][col+2] = 1;
					dir = ::down_right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row + 1;
					ship.y2 = col + 1;
					ship.x3 = row + 2;
					ship.y3 = col + 2;
					break;
				case 2: // Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
				case 3:	// Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
			}
			break;
		case 1: 
			switch(col){
				case 0: // Valid, place diagonally
					board[row][col] = 1;
					board[row+1][col+1] = 1;
					board[row+2][col+2] = 1;
					dir = ::down_right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row + 1;
					ship.y2 = col + 1;
					ship.x3 = row + 2;
					ship.y3 = col + 2;
					break;
				case 1: // Valid, place diagonally
					board[row][col] = 1;
					board[row+1][col+1] = 1;
					board[row+2][col+2] = 1;
					dir = ::down_right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row + 1;
					ship.y2 = col + 1;
					ship.x3 = row + 2;
					ship.y3 = col + 2;
					break;
				case 2: // Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
				case 3:	// Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
					dir = ::left;
			}
			break;
		case 2: 
			switch(col){
				case 0: // Falls off the board diagonally and left, place right
					board[row][col] = 1;
					board[row][col+1] = 1;
					board[row][col+2] = 1;
					dir = ::right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col + 1;
					ship.x3 = row;
					ship.y3 = col + 2;
					break;
				case 1: //Falls off the board diagonally and left, place right
					board[row][col] = 1;
					board[row][col+1] = 1;
					board[row][col+2] = 1;
					dir = ::right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col + 1;
					ship.x3 = row;
					ship.y3 = col + 2;
					break;
				case 2: // Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
				case 3:	// Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
			}
			break;
		case 3:
			switch(col){
				case 0: // Falls off the board, place horizontally right
					board[row][col] = 1;
					board[row][col+1] = 1;
					board[row][col+2] = 1;
					dir = ::right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col + 1;
					ship.x3 = row;
					ship.y3 = col + 2;
					break;
				case 1: // Falls off the board, place horizontally right
					board[row][col] = 1;
					board[row][col+1] = 1;
					board[row][col+2] = 1;
					dir = ::right;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col + 1;
					ship.x3 = row;
					ship.y3 = col + 2;
					break;
				case 2: // Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
				case 3:	// Falls off the board, place horizontally left
					board[row][col] = 1;
					board[row][col-1] = 1;
					board[row][col-2] = 1;
					dir = ::left;

					//initialize ship
					ship.x1 = row;
					ship.y1 = col;
					ship.x2 = row;
					ship.y2 = col - 1;
					ship.x3 = row;
					ship.y3 = col - 2;
					break;
			}
			break;
	}

	return dir;
}

#endif