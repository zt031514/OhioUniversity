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

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class GameOfLife {
	public:
		vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
	private:
		int getNumNeighbors(vector<vector<int> > &board, int row, int col);
		void newBoard(vector<vector<int> >&board);
};

#endif