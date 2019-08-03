//********************************************************
//
// Author: Zach Tumbleson
// Class : CS 3610 - Fall 2017
// Date  : 11/14/17
// Brief : This program simulates an external sort,
//         using quicksort to sort individual
//         sublists, then using a multi-merge sort
//         to combine them into one list which is
//         outputted at the end of the main.
//
//         Quicksort and partition functions are
//         based on the textbook/lecture notes examples,
//         multiway_Merge is largely original.
//
//*******************************************************

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const double LARGE = pow(10, 6);

int partition(vector<int>& list, int first, int last) {
  // The pivot should be the median of the
  // first, middle, and last elements.
   
    int smaller = 0;
    int middle = (first + last) / 2;
    
    int pivot = list[middle]; //pivot is the middle element
    
    swap(list[first], list[middle]); //swap first and middle elements
    
    // use middle element as the pivot point
    smaller = first;
    
    for(int i = first + 1; i <= last; i++)
    {
        if(list[i] < pivot){ // if element is less than the pivot, add to the smaller list
            smaller++;
            swap(list[smaller], list[i]);
        }
        //else { add the number to the larger list
    }
    
    swap(list[first], list[smaller]);
    
    return smaller;
    
}

void quicksort(vector<int>& list, int first, int last) {
    
    if(first >= last) //
        return;
    else{
        int pivot = partition(list, first, last);
        quicksort(list, first, pivot - 1);
        quicksort(list, pivot + 1, last);
    }
}


//Returns the row of the next minimum value
int getMin(const vector<vector<int> > &input_lists, const int nth_curr_column[])
{
    int min_row = 0; //returns the row containing the minimum element
    int min = 0; //the current minimum value
    
    //Contains the current values for each row
    int values[input_lists.size()];
    
    //Check if any lists have been completed
    for(int i = 0; i < input_lists.size(); i++){
    //
    //    if(nth_curr_column[i] > input_lists.size()){ // if a list has been completed, don't use it to check
    //        values[i] = -1;                                           //for the min
    //
    //    }
    //    else
            values[i] = input_lists[i][ nth_curr_column[i] ]; //else use the value in the proper location
    //
    }
    if(nth_curr_column[0] < input_lists.size())
       min = values[0];
    else
       min = LARGE;
    for(int i = 1; i < input_lists.size(); i++)
    {
        if(values[i] < min && (nth_curr_column[i] < input_lists.size())){
            min_row = i;
            min = values[i];
        }
    }
    return min_row;
}

//Produces a sorted list of numbers in output list
void multiway_merge(
  vector<vector<int> >& input_lists, vector<int>& output_list
) 
{
    
    int nth_curr_column[input_lists.size()]; //Stores the current column index for each list
    int out_index = 0; // Stores the next input to output to
    int min_row = 0; // stores the row of the next minimum element
    
    priority_queue <int, vector<int>, greater<int> > heap; // MIN-heap
    
    //Initialize column arrray
    for(int j = 0; j < input_lists.size(); j++)
    {
        nth_curr_column[j] = 0;
    }
    
    //Find which row the first min came from
    min_row = getMin(input_lists, nth_curr_column);
    
    //Initialize heap with the first value from each list
    for(int i = 0; i < input_lists.size(); i++){
        heap.push(input_lists[i][ nth_curr_column[i] ]); //load initial values into the heap
    }
    
    while(!heap.empty() && out_index < input_lists.size() * input_lists[0].size())
    {
            if(nth_curr_column[min_row] < input_lists.size()){
        
                //Write min element to the output vector, then remove from heap
                output_list[out_index] = heap.top();
                heap.pop();
                out_index++;
        
                // Push successor into the queue into the queue
                heap.push(input_lists[min_row][ nth_curr_column[min_row] + 1 ]);
                nth_curr_column[min_row] += 1;
                min_row = getMin(input_lists, nth_curr_column);
            }
            
            else{
                //If popped element was the last in its row, pop next min from heap
        
                output_list[out_index] = heap.top();
                
                //Return to orignal sublist
                int a = 0;
                for(int b = 0; b < input_lists[a].size(); b++){
                    if(input_lists[a][nth_curr_column[min_row - 1]] == heap.top())
                        min_row = a;
                }
            
                heap.pop();
                out_index++;
            }
    }
}

int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }
    
  //Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
      quicksort(input_lists[i], 0, m-1);
    
  //Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);
    
  for (int i = 0; i < output_list.size(); ++i)
      cout << output_list[i] << " ";
      cout << endl;
}
