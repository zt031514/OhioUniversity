//******************************
//
//  Author: Zach Tumbleson
//  Class: CS 3610
//  Date: 11/1/2017
//
//  Brief: Header file for the
//         implementation of the
//         knight's tour problem
//
//********************************



#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

#include <vector>
using namespace std;

class KnightsTour {

public:
	KnightsTour(int board_size);

	int generate(int row, int col);

private:
	void move(int row, int col, int& m, int& num_tours);
  void get_moves(
    int row, int col, 
		int row_moves[], int col_moves[], int& num_moves
  );
    //Returns whether a move is valid or not
    bool isValidMove(int row, int col);
	void print();

	int board_size;
	vector<vector<int> > board;

};

#endif
