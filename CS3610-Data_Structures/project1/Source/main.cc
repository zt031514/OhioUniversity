//********************************************************
//
//	Author: Zach Tumbleson
//	Title: Project 1 - The Sieve of Eratosthenes
//	Class: CS 3610 - Fall 2017
//	Date Created: 9/12/2017
//
//	This program implements the sieve of Eratosthenes,
//	an algorithm to find the prime numbers between 2
//	and a given positive integer n.
//
//********************************************************/

#ifndef MAIN_CC
#define MAIN_CC

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;


//===================================================================================
//BEGIN DECLARATIONS

int *Numbers(const int n);
// Pre-condition: n is a positive integer greater than 2
//
// Post-condition: Returns an array of consecutive integers
// from 2 to n inclusive ([2, n]).

bool *Markers(const int n);
// Pre-condition: n is a positive integer greater than 2
//
// Post-condition: Returns an array of consecutive integers
// from 2 to n inclusive ([2, n]). All elements are marked false (not prime) initially.

void sieve(int *numbers, bool* markers, const int n);
// Pre-condition: Takes the array of integers from create(), and the array
// of bool markers.
// 
// Post-conditon: The indexes of composite numbers have been marked
// as true in the markers array.

void output(const int *numbers, const bool *markers, const int n);
// Pre-condition: Takes a standard output stream
//
// Post-condition: Prints the prime numbers between 2 and n on one line,
// followed by the composite numbers between 0 and n on the next line.

//END DECLARATIONS

//=====================================================================================
//BEGIN MAIN

const int SMALLEST = 2;
const int LARGEST = 30000;

int main(int argc, const char *argv[])
{
	// Check for argument
	if(argc < 2){
		cout << endl << "No input argument." << endl << endl;
		exit(1);
	}

	// get argument from the command line argument	
	int max = atoi(argv[1]);	

	// check that argument is an integer
	for(int a = 0; a < int(strlen(argv[1])); a++){	
		if(!isdigit(argv[1][a])){
			cout << "\nError: Input NaN.\n\n";
			exit(1);
		}
	}
	
	// check range
	if(max < SMALLEST || max > LARGEST){
		cout << endl << "Error: Out of range." << endl << endl;
		exit(1);
	}
	
	
	// Find primes
	else{
		// Initialize arrays of numbers and markers
		int *numbers = Numbers(max-1);
		bool *markers = Markers(max-1);

		// Mark all composites true
		sieve(numbers, markers, (max-1));
	
		output(numbers, markers, (max-1));
	
		delete numbers;
		delete markers;
	}
	return 0;
}

// END MAIN

//===============================================================================
// BEGIN FUNCTION IMPLEMENTATION


// Returns an array of consecutive integers from 2 to n.
int *Numbers(const int n)
{
	int *temp = new int[n];
	int m = 2;

	for(int k = 0; k < n; ++k, m++)
	{
		temp[k] = m;
	}
	
	return temp;
}

// Returns an array of bool markers of size n.
// All markers are initially set to false.
bool *Markers(const int n)
{
	bool *temp = new bool[n];
	
	for(int i = 0; i < n; i++){
		temp[i] = false;
	}
	
	return temp;
}

// Marks composite numbers as true, leaves primes as false
void sieve(int *numbers, bool* markers, const int n)
{
	// value of the current prime being evaluated
	int p = 2;
	// index of p
	int p_index = 0;

	while (p <= floor(sqrt(double(n+1))))
	{
		
		// Sieve working
		for(int h = p_index+p; h < n; h += p)
		{
			markers[h] = true;
		}
		

		// Find next unmarked number
		for(int c = p_index + 1; c < n; c++)
		{
			if(markers[c] == false){
				p_index = c;
				p = numbers[c];
				break;
			}
		}	
	}
}

// Outputs a list of prime numbers, then a list of composite numbers.
void output(const int *numbers, const bool *markers, const int n)
{
	// Print primes
	for(int p = 0; p < n; p++)
	{
		if(markers[p] == false){
			cout << numbers[p] << " ";
		}
	}
	cout << endl;
	//Print composites
	for(int q = 0; q < n; q++)
	{
		if(markers[q] == true){
			cout << numbers[q] << " ";
		}
	}
	cout << endl;
	
}


// END FUNCTION IMPLEMENTATION

//=============================================================================

#endif
// END OF FILE
