//******************************************************
//
//  File: hw1_2.cc
//  Author: Zach Tumbleson
//  Created: 2/1/2019
//  Description: Sequential program to find the highest
//				 value of multiplications given an length
//				 m and a modulo q. Code to read in m, q,
//				 and input matrix taken from read_data.cc
//				 provided by Dr. Juedes
//******************************************************

//********************************************************
//File:read_data.cc
//Author: David W. Juedes
//
//Purpose: This example program reads the data for homework #1
// It reads m q
// and then, a n x n matrix of integers 
// This code is not elegant, but it is sufficient for the
// purpose of this class.
//***********************************************************
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <omp.h>
using namespace std;


//***************************************************************
// Function read_q(istream &in) 
// Parameters: istream in --- 
// Return value: q
// Purpose: Read the value q (the modulus for the assigment)
//****************************************************************
int read_q(istream &in) {
  int q;
  in >> q;
  return q;
}
//***************************************************************
// Function read_m(istream &in) 
// Parameters: istream in --- 
// Return value: m
// Purpose: Read the value m (the number of values in the product)
//****************************************************************
int read_m(istream &in) {
  int m;
  in >> m;
  return m;
}
//***************************************************************
// Function read_M(istream &in) 
// Parameters: istream in --- 
// Return value: vector<vector<int> > M
// Purpose: Read the value M, the matrix, which exists to the end of the 
// input.
// Assumption: each row of the matrix is stored on a line by itself.
//****************************************************************
vector<vector<int> > read_M(istream &in) {
  string line;
  vector<vector<int> > M;
  while (!in.eof()) {
    getline(in,line);
    if (!in.fail()) {
      istringstream in1(line);
      vector<int> row;
      while (!in1.eof()) {
	int x;
	in1 >> x;
	if (!in1.fail()) {
	  row.push_back(x);
	}
      }
      M.push_back(row);
    }
  }


  return M;
}

//********************************************************************************
//Function getLocalMax(int m, int row, int col, vector<vector<int>> &matrix)
//Parameters: int m: length of mulitply chain
//			  int row: current row in the matrix
//			  int col: current column in the matrix
//			  vector<vector<int>> &matrix: matrix of values used for calculations
//
//Return Value: int local_max
//
//Purpose: Calculates the maximum product  
//in a line of m spaces for a single location in the matrix
//
//Assumption: Every matrix location contains a non-zero 
//value (contains a 1 if "empty")
//*********************************************************************************
unsigned int getLocalMax(int m, int q, int row, int col, vector<vector<int> > &matrix);


//********************************************************************************
//Function multiplyRow(int m, int row, int col, vector<vector<int>> &matrix)
//Parameters: int m: length of mulitply chain
//			  int row: current row in the matrix
//			  int col: current column in the matrix
//			  vector<vector<int>> &matrix: matrix of values used for calculations
//
//Return Value: int prod
//
//Purpose: Calculates the maximum product of an m long string
//		   for the given row in the matrix
//
//Assumption: Every matrix location contains a non-zero 
//value (contains a 1 if "empty")
//*********************************************************************************
unsigned int multiplyRow(int m, int q, int row, int col, vector<vector<int> > &matrix);


//********************************************************************************
//Function multiplyColumn(int m, int row, int col, vector<vector<int>> &matrix)
//Parameters: int m: length of mulitply chain
//			  int row: current row in the matrix
//			  int col: current column in the matrix
//			  vector<vector<int>> &matrix: matrix of values used for calculations
//
//Return Value: int prod
//
//Purpose: Calculates the maximum product of an m long string
//		   for the given column in the matrix
//
//Assumption: Every matrix location contains a non-zero 
//value (contains a 1 if "empty")
//*********************************************************************************
unsigned int multiplyColumn(int m, int q, int row, int col, vector<vector<int> > &matrix);




//********************************************************************************
//Function multiplyDiagonal(int m, int row, int col, vector<vector<int>> &matrix)
//Parameters: int m: length of mulitply chain
//			  int row: current row in the matrix
//			  int col: current column in the matrix
//			  vector<vector<int>> &matrix: matrix of values used for calculations
//
//Return Value: int prod
//
//Purpose: Calculates the maximum product of an m long string
//		   for a diagonal extend from M[row][col]
//
//Assumption: Every matrix location contains a non-zero 
//value (contains a 1 if "empty")
//*********************************************************************************
unsigned int multiplyDiagonal(int m, int q, int row, int col, vector<vector<int> > &matrix);
 
int main() {
	int q;
	int m;
	vector<vector<int> > M;
	m = read_m(cin);
	q = read_q(cin);
	string line;
	getline(cin,line);
	assert(line == "");

	M = read_M(cin);
	
	//Print matrix dimensions
	//cout << "Height: " << M.size() << " Width: "<< M[0].size() << endl;

	//print the matrix
	/*for(unsigned int i = 0; i < M.size(); i++){
		for(unsigned int j = 0; j < M[0].size(); j++){
			cout << M[i][j] << " ";
		}
		cout << endl;
	}*/
	

	unsigned int max = 0; //stores the value of the largest multiplication

	unsigned int i,j;
	for(i = 0; i < M.size(); i++){
		for(j = 0; j < M[i].size(); j++){
			
			
			#pragma omp parallel
			{
				unsigned int local_max;
				local_max = getLocalMax(m, q, i, j, M);

				if(local_max > max){
					#pragma omp critical
					max = local_max;
				}
			}	
		}
	}	
	cout << "Max is " << max << endl;
	return 0;
}

unsigned int multiplyRow(int m, int q, int row, int col, vector<vector<int> > &matrix){
	if( matrix.size() - col < m ){
		return 1;
	}
	else{
		unsigned int prod;
		int start_col = col;
		prod = 1;
		while( col < start_col + m ){
			prod = ( prod % q ) * ( matrix[row][col] % q);
			col++;
		}
		return prod;
	}
}

unsigned int multiplyColumn(int m, int q, int row, int col, vector<vector<int> > &matrix){
	if( matrix.size() - row < m ){
		return 1;
	}
	else{
		unsigned int prod;
		int start_row = row;
		prod = 1;
		while(row < start_row + m){
			prod = ( prod % q ) * ( matrix[row][col] % q );
			row++;
		}
		return prod;
	}
}

unsigned int multiplyDiagonal(int m, int q, int row, int col, vector<vector<int> > &matrix){
	
	//Check for downward diagonal
	if( ( ( matrix.size() - row < m ) || ( matrix[row].size() - col < m ) ) ){
		//Check for upward diagonal
		if( ( row + 1 < m ) && ( matrix[row].size() - col < m ) ){
			//no diagonals of length m available, return 1
			return 1;
		}
		else{ //No downward diagonal, calculate upward diagonal
			
			unsigned int prod;
			int start_row = row;
			int start_col = col;
			prod = 1;
			
			while( ( row > start_row - m ) && (col  < start_col + m) ){
				prod = ( prod % q ) * ( matrix[row][col] % q );
				row--;
				col++;
			}
			return prod;
		} 
	}
	else{ //both diagonals are available, check both
		unsigned int prod;
		int start_row = row;
		int start_col = col;
		prod = 1;
		
		//check downward diagonal
		while( ( row < start_row + m ) && ( col < start_col + m ) ){
			prod = ( prod % q ) * ( matrix[row][col] % q );
			row++;
			col++;
		}
		
		unsigned int down_max = prod;
		row = start_row;
		col = start_col;
		
		//check upward diagonal
		if( ( start_row + 1 >= m ) && ( matrix[row].size() - start_col >= m) )
		{
			while( ( row > start_row ) && (col  < start_col + m) ){
				prod = ( prod % q )  * ( matrix[row][col] % q );
				row--;
				col++;
			}
		}
		if(prod > down_max){ //upward diagonal product is larger
			return prod;
		}
		else{				 //downward diagonal product is larger
			return down_max;
		}
	}
}

unsigned int getLocalMax(int m, int q, int row, int col, vector<vector<int> > &matrix){

	
	unsigned int row_max, col_max, diag_max, local_max;

	row_max = multiplyRow( m, q, row, col, matrix) % q; 
	col_max = multiplyColumn( m, q, row, col, matrix) % q;
	diag_max = multiplyDiagonal( m, q, row, col, matrix) % q;
	//cout << "Finished Diagonal multiplies for [" << row << ", " << col << "]" << endl; 

	//cout << "rowMax, colMax, diagMax: " << row_max << " " << col_max << " " << diag_max << endl;
	local_max = row_max;
	
	
	if( col_max > local_max ){
		local_max = col_max;
	}
	else if( diag_max > local_max ){
		local_max = diag_max;
	}
	return local_max;
}