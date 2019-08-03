//******************************
//
//  Author: Zach Tumbleson
//  Class: CS 3610
//  Date: 11/1/2017
//
//  Brief: Implementation of the
//         knight's tour problem
//
//********************************


#include <iostream>
#include <iomanip>
#include "knights_tour.h"
using namespace std;

KnightsTour::KnightsTour(int board_size) {
  this->board_size = board_size;

  this->board.resize(board_size);
  for (int i = 0; i < board_size; ++i) {
    this->board[i].resize(board_size);
  }
}

void KnightsTour::print() {
  for (int i = 0; i < this->board_size; i++) {
    for (int j = 0; j < this->board_size; j++)
      cout << setw(4) << this->board[i][j] << " ";
    cout << endl;
  }
  cout << endl << endl;
}

//Function: isValidMove()
//      Desc: Returns true is the move is valid, false otherwise
//            Does not check that a move is "proper" i.e. down 2 spaces and left 1
//
//      int row             - Current row position of the knight
//      int col             - Current column position of the knight
//

bool KnightsTour::isValidMove(int row, int col)
{
    //If move is off the board, return false
    if(row >= 5 || row < 0)
        return false;
    else if(col >= 5 || col < 0){
        return false;
    }
    // If space has already been visited, return false
    else if(board[row][col] <=25 && board[row][col] > 0)
        return false;
    else
        return true;
}

// Function: get_moves()
//    Desc: Get the row and column indices of all valid
//          knight moves reachable from position row, col.
//          An invalid move would be one that sends the
//          knight off the edge of the board or
//          to a position that has already been visited.
//          
//    int row         - Current row position of knight.
//    int col         - Current column position of knight.
//    int row_moves[] - Array to store row indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int col_moves[] - Array to store column indices
//                      of all valid new moves reachable from
//                      the current position row, col.
//    int num_moves -   Number of valid moves found. Corresponds
//                      to the sizes of row_moves and col_moves.

void KnightsTour::get_moves(
  int row, int col, 
  int row_moves[], int col_moves[], int& num_moves
) {
    int next_row = 0;
    int next_col = 0;

    //These two arrays represent the 8 possible moves by the knight
    const int row_test[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    const int col_test[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for(int i = 0; i < 8; i++)
    {
        //Set next_row and next_col to the next possible move
        next_row = row + row_test[i];
        next_col = col + col_test[i];
        
        //If the move is valid, add to the list of valid moves, increment num_moves
        if(isValidMove(next_row, next_col)){
            row_moves[num_moves] = next_row;
            col_moves[num_moves] = next_col;
            num_moves++;
            
        }
    }
}
    

// Function: move() --> Recursive
//     int row        - Current row position of knight.
//     int col        - Current column position of knight.
//     int& m         - Current move id in tour.
//                      Stored in board at position
//                      row, col.
//     int& num_tours - Total number of tours found.

void KnightsTour::move(int row, int col, int& m, int& num_tours) {
    
    int moves_by_row[8]; // 8 possible moves
    int moves_by_col[8]; // 8 possible moves
    int num_moves = 0;   // Becomes number of valid moves for a given space
                         // size of moves_by_row and moves_by_col
    
    //Place knight at board[row][col], then get_moves for new position
    m++;
    board[row][col] = m;
    
    //Debugging: cout << "Placing knight " << m << " at " << row << ", " << col << endl;
    
    get_moves(row, col, moves_by_row, moves_by_col, num_moves);
    
    if(m == 25){
        //Tour completed, increment num_tours and print solution.
        print();
        num_tours++;

        //Tour completed, backtrack -> m = 24, board[row][col] set to empty
        m = board[row][col] - 1;
        board[row][col] = 0;
    }
    
    else{
        for(int i = 0; i < num_moves; i++){
            //Debugging: cout << "Testing move " << (i + 1) << " of " << num_moves << "\n";
            
            //Move night to new position and continue
            move(moves_by_row[i], moves_by_col[i], m, num_tours);
            //All moves evaluated for the next knight, now try this -> next move
        }
        
        //Out of moves, m = last knight placed, board[row][col] set to empty
        m = board[row][col] - 1;
        board[row][col] = 0;
        
    }
    
    //Debugging: cout << "Out of moves, backtracking...\n";
}

int KnightsTour::generate(int row, int col) {
  int m = 0;
  int num_tours = 0;
  move(row, col, m, num_tours);

  return num_tours;
}


