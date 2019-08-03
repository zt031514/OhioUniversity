//*************************************************************
//
//      Author: Zach Tumbleson
//
//      Class : Cs 3610 - Fall 2017
//
//      Date  : 11-30-17
//
//      Brief : Header file implementing the
//              weightedGraphType class for use
//              in implementing Dijkstra's shortest
//              path algorithm
//
//              Much of the algorithm is provided in
//              Data Structures with C++ by Malik. The input/output functions
//              are original.
//
//              weightedGraphType   : Pgs. 704-706
//
//************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <climits> //used for INT_MAX const
using namespace std;

//****************************
//BEGIN FUNCTION DECLARAIONS
//****************************

//
//Reads in input from the keyboard and stores data
//Post-condition: numNodes contains the number of vertexes in the graph
//                cities contains a list of the cities on the graph
//                edgeWeights is a 2D matrix containing the edge weights between cities
//
void getInput(int& numNodes, string* &cities, int** &edgeWeights);

//
//Determines the smallest weight to each vertex in the graph from the source, vertex.
//Post-condition: dist is a 1D array containing the smallest weighted path from source to dist[i]
//                prev is a 1D array containing the predecessor of each vertex in the graph, prev[i] is a given
//                vertex's predecessor
//
void shortestPath(int vertex, int* &dist, int ** edgeWeights, int numNodes, vector<int> &prev);

//
//Post-condition: Results of shortest path algorithm have been printed to the screen:
//                shortest path followed by path cost/weight
//
void printShortest(const int numNodes, const int *dist, const vector<int> prev, const string *cities);

//**************************
//END FUNCTION DECLARATIONS
//**************************



//***************
//BEGIN MAIN
//***************
int main()
{
    //
    int numNodes = 0, testCases = 0;
    
    //List of cities
    string *cities = 0;
    
    //Weight Matrix
    int **edgeWeights = 0;
    
    //Weight of shortest path from source to vertex n, dist[n]
    int *dist = 0;
    
    //Get number of testCases
    cin >> testCases;
    
    for(int i = 0; i < testCases; i++)
    {
        //Read in from keyboard
        getInput(numNodes, cities, edgeWeights);
        
        //size dependent containers
        dist = new int[numNodes];
        vector<int> prev(numNodes);
        
        //Do Dijkstra's Shortest Path
        shortestPath(0, dist, edgeWeights, numNodes, prev);
        printShortest(numNodes, dist, prev, cities);
        
        //Memory clean-up
        delete [] cities;
        for(int j = 0; j < numNodes; j++)
            delete [] edgeWeights[j];
        delete [] edgeWeights;
        delete [] dist;
    }
    
    return 0;
}

//***************
//END MAIN
//***************

//BEGIN FUNCTION DEFINITIONS
//*********************************************************************
//*********************************************************************

//
//Process keyboard input
//
void getInput(int& numNodes, string* &cities, int ** &edgeWeights)
{
    //Get the number of cities
    cin >> numNodes;
    
    //Create input arrays
    cities = new string[numNodes];
    
    //Create 2D weights array
    edgeWeights = new int*[numNodes];
    for(int c = 0; c < numNodes; c++)
        edgeWeights[c] = new int[numNodes];
    
    //eat newline character
    char junk;
    cin.get(junk);
    
    for(int i = 0; i < numNodes; i++)
    {
        getline(cin, cities[i]); //get list of all cities
    }
    
    for(int j = 0; j < numNodes; ++j)
    {
        for(int k = 0; k < numNodes; ++k)
        {
            cin >> edgeWeights[j][k]; //read in matrix of edge weights
        }
    }
}

//
//Print results
//
void printShortest(const int numNodes, const int* dist, const vector<int> prev, const string *cities)
{
    //List of nodes on the shortest path
    vector<bool> isOnPath(numNodes);
    
    isOnPath[numNodes - 1] = true; //Destination node is always on the path
    
    int m = numNodes - 1;
    while(m > 0)
    {
        isOnPath[prev[m]] = true; //Backtracking, the predecessor of the current node is on the path
        m = prev[m];
    }
    
    for(int k = 0; k < prev.size(); k++) //Output vertices on the shortest path
    {
        if(isOnPath[k])
            cout << cities[k] << " ";
    }
    
    cout << dist[numNodes - 1] << endl;
}

//BEGIN SHORTEST PATH ALGORITHM
//*******************************************************************************************
//*******************************************************************************************

void shortestPath(int vertex, int* &dist, int** edgeWeights, int numNodes, vector<int> &prev)
{
    if(dist == NULL || numNodes == 0 || edgeWeights == NULL)
        return;
    
    //initialize smallest weights to current known edges
    for(int i = 0; i < numNodes; i++)
        dist[i] = edgeWeights[vertex][i];
    
    bool *weightFound;
    weightFound = new bool[numNodes];
    
    //initialize array indicating smallest weights found
    for(int j = 0; j < numNodes; j++)
        weightFound[j] = false;
    
    weightFound[vertex] = true; // mark current vertex as weight found,  condition is true after loop iteration
    dist[vertex] = 0;   // distance from vertex to itself is 0
    
    //perform smallest weight algorithm
    for(int k = 0; k < numNodes - 1; k++)
    {
        int minWeight = INT_MAX;
        int v = 0;
        
        for(int m = 0; m < numNodes; m++)
        {
            if(!weightFound[m]) // if weight has been found, skip to next vertex
            {
                if(dist[m] < minWeight && dist[m] != 0)
                {    // nearest node found
                    v = m;                              // store new closest node
                    minWeight = dist[v];
                }
            }
        }
        
        weightFound[v] = true; //weightFound for node v
        
        for(int n = 0; n < numNodes; n++)
        {
            if(!weightFound[n] && edgeWeights[v][n] != 0) //if weight has not been found and an edge exist between
            {                                             //vertexes v and n, update distances if necessary
                if(minWeight + edgeWeights[v][n] < dist[n] || (dist[n] == 0 && n != vertex))
                {
                    dist[n] = minWeight + edgeWeights[v][n];
                    prev[n] = v;
                }
            }
        }
    } //end for
}

//**************************************************************************
//**************************************************************************
//END SHORTEST PATH ALGORITHM


//***************************************************************************
//***************************************************************************
//END FUNCTIONS

//**
//END OF FILE
//**
