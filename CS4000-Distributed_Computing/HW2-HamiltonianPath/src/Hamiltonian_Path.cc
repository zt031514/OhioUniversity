

//***************************************************************
// File: Hamiltonian_Path.cc
// Author: David W. Juedes, Zach Tumbleson
// Purpose: This code finds whether there exists a Hamiltonian Path 
// from one vertex to another in a graph.
//
// OpenMP components "added" by Zach Tumbleson to produce "speedup."
//
//****************************************************************
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include "omp.h"

using namespace std;

//*********************************************************************
//
// Function valid_tour
//
// Parameters: vector<list<int>> &adj_list
//             |->Represents the adjacency list for a given node
//             vector<int> &tour
//             |->Represents all the nodes in the current tour
//
// Return value: bool valid
//               |-> Returns true if the tour parameter represents
//               |-> a valid path through the graph given by adj_list
//               |-> and returns false otherwise
//
//**********************************************************************

bool valid_tour(vector<list<int> >&adj_list,
                vector<int> &tour) {
  // Tests whether the tour is valid
  // Returns the total distance

  //int start = tour[0];
  bool valid = true;
  for (size_t i=1;i<tour.size();i++) {
    bool found = false;
    
    // Is there an edge from tour[i-1] to tour[i]
    
    //TODO: Fix this so that the threads check a shared found value
    //      before each iteration, then exit immediately if found is set to true
    //***************************************************************

    for (list<int >::iterator p = adj_list[tour[i-1]].begin();
       p!=adj_list[tour[i-1]].end();++p) {
          
          if (*p == tour[i]) {
            found = true;
            break; 
          }
    }

    //****************************************************************
    
    if (!found) valid = false;
  }
  return valid;
}

//**********************************************************************
//
// Function valid_tour
//
// Parameters: vector<list<int> >& adj_list
//             |->Represents the adjacency list for a given node
//             int i1
//             |->Represents the start node in the graph
//             int j1
//             |->Represents the end node in the graph
//             bool found_it
//             |->set to true if a Hamiltonian tour is found,
//             |->remains false otherwise
//
// Return value: vector<int> tour OR vector<int>
//               |->Returns tour if a valid hamiltonian tour is found,
//               |->Returns perm otherwise
//
//***********************************************************************

vector<int> Hamiltonian_tour(vector<list<int> >&adj_list, int i1, int j1, bool &found_it) {


  int n = adj_list.size();
  vector<int> perm;
  vector<int> opt;
  
  //add all nodes to test that are not the start or end nodes
  //I don't think I can parallelize this easily
  for (int i=0;i<n;i++) {
    if ((i!=i1)&&(i!=j1)) {
      perm.push_back(i);
    }
  }

  //bool t_found = false;
  //int c = 0;
  
  //test nodes to see if a tour is found
  
  //TODO: Fix this part, it needs parallelized, that while clause is nasty
  //***************************************************

  do {
    vector<int> tour;
    tour.resize(n);
    tour[0] = i1;
    tour[n-1] = j1;

    for (int i=0;i<n-2;i++) {
      tour[i+1] = perm[i];
    }

    bool found;
    found = valid_tour(adj_list,tour);
    if (found) {
      found_it=true;
      return tour;
    }

  }  while (next_permutation(perm.begin(),perm.end()));

  //****************************************************
  
  //No tour found
  found_it = false;
  return perm;
}


//**************
//
// MAIN
//
//**************

int main() {
  int n;
  int i1;
  int j1;
  cin >> n;
  cin >> i1;
  cin >> j1;
  string line;
  getline(cin,line); // Get the newline
  
  vector<list<int> > adj_list;
  adj_list.resize(n);

  //read input file
  while (!cin.eof()) {
    
    getline(cin,line);
    
    if (!cin.fail()) {
      
      istringstream in(line);
      int j;
      in >> j;
      char c;
      in >> c;
      assert(c==':'); //Assert that the character read into c is not a number
      
      while (!in.eof()) {
        
        int i;
        in >> i;
        
        if (!in.fail()) {
          adj_list[j].push_back(i);
        }
      }
    }
  }
  //End of reading input
  
  //Begin Hamiltonian search
  bool found=false;
  vector<int> opt; //wow, very optimal
  
  opt = Hamiltonian_tour(adj_list,i1,j1,found);
  
  if (found) {
    cout << "Tour = ";
   
    //Print the tour (please don't do this in parallel) 
    for (size_t i=0;i<opt.size();i++) {
      cout << opt[i] << " ";
    }
    
    cout << endl;
  } 
  else {
    cout << "No Hamiltonian Tour" << endl;
  }
}