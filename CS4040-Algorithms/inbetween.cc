//*********************************************************************
//
//          Program: Homework 4 -- inbetween.cc
//
//			Author: Zach Tumbleson
//			Email: zt031514@ohio.edu
//
//			Class: CS4040 - Dr. Chelberg			
//
//			Assignment: Homework 4
//
//			Description: Header file for two functions 
//						 that return the students with 
//						 a gpa between the jth and kth 
//						 highest, inbetweenGPA(), or the 
//						 students whose names fall between 
//						 the jth and kth highests in the 
//						 list, inbetweenAlpha()
//
//			Date: 10-24-2018
//
//********************************************************************/

#include "inbetween.h"
//TODO: Function Comment blocks

//******************************************************************
//                                                                  
//  Function:   insertionSort
//                                                                  
//  Purpose:    Implement the insertion sort described in pseudocode
//              from page 18 of "Introduction to Algorithms" by
//              Cormen et. al.
//                                                                  
//  Parameters: list - list of students
//              start - beginning index of values to be sorted
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the GPA of the students with the 
//                  target rank.
//
// Calls:       None
//
// Space Complexity: O(Number of items in the list) - Sorting done in place.
//
// Time Complexity: O(end - start) - For this project, the input list is always 5 items long
//                  so the complexity becomes O(5)
//                                                                  
//******************************************************************


void insertion_sort(vector<Student> &list, int start, int end, size_t &num_compares){
      for(int i = start + 1; i < end; i++){
            
            Student currentStudent = list[i];   //Sort the value in list[i] to the correct place
            
            int j = i - 1;    //Start by comparing the second element
                              //with the first element

            while(j > -1 && list[j].gpa > currentStudent.gpa)
            {
                  list[j+1] = list[j];
                  j = j - 1;
                  num_compares++;
            }
            list[j+1] = currentStudent;
      }
}


//******************************************************************
//                                                                  
//  Function:   get_medians
//                                                                  
//  Purpose:    Collects the median students from each group of 5
//              and returns them as a vector
//                                                                  
//  Parameters: list - list of students
//              num_compares - total number of compares that the program takes
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: list is not empty, has valid values
//
// Post Conditions: returns a vector of the medians
//
// Calls:       function insertion_sort
//
// Space Complexity: O(Number of items in the list)
// Time Complexity: O(Number of items in the list / 5)
//                                                                  
//******************************************************************


vector<Student> get_medians(vector<Student> list, size_t &num_compares){

      //Divide into groups of 5
      const int GROUP_SIZE = 5;

      int num_groups = (list.size() / GROUP_SIZE); //Determine the number of groups of 5

      if(list.size() % GROUP_SIZE != 0){
            num_groups++;     //Add 1 if the last group is a group of less than five
      }

      vector<Student> medians(num_groups);      //Array that will contain the median for each group

      for(int i = 0; i < num_groups; i++){
            insertion_sort(list, ( GROUP_SIZE*i ), ( GROUP_SIZE+i ), num_compares);
            medians[i] = list[(i * GROUP_SIZE) + (GROUP_SIZE / 2)];
      }

      //Handle the last group if number of students is not divisible by 5
      
      if(list.size() % GROUP_SIZE != 0){
            int lastGroupSize = list.size() % 5;    //Determine the size of the last partial group
            insertion_sort(list, ( GROUP_SIZE * (num_groups - 1)), ( GROUP_SIZE + (num_groups - 1)), num_compares);
            medians[num_groups-1] = list[((num_groups - 1) * GROUP_SIZE) + ( lastGroupSize / 2 )];
      }

      return medians;
}


//******************************************************************
//                                                                  
//  Function:   partition
//                                                                  
//  Purpose:    parititon the array 
//              of target largest in the array.
//                                                                  
//  Parameters: list - list of students
//              target - rank of value to be 
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the GPA of the students with the 
//                  target rank.
//
// Calls:       function swap
//                                                                  
//******************************************************************


int partition(vector<Student> list, size_t &num_compares){
      /*float x = list[r].gpa;
      int i = p - 1;
      for(int j = p; j < r; j++)
      {
            if(list[j].gpa <= x){
                  i = i + 1;
                  swap(list[i], list[j]);
            }
      }
      swap(list[i+1], list[r]);
      return i+1;*/
      return 1;
}


//******************************************************************
//                                                                  
//  Function:   linear_gpa_select
//                                                                  
//  Purpose:    Return the student with the target highest ranking  
//              in gpa.
//                                                                  
//  Parameters: list - list of students
//              target - "jth largest" value to search for
//              num_compares - number of compares used by the entire program 
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: input parameters have valid values, target is smaller than the size of the list
//
// Post Conditions: returns the student with the 
//                  target rank gpa.
//
// Calls:       function get_medians, function insertion_sort, function partition
//
// Time Complexity = O(Number of items in the list)
// Space Complexity = O(Number of items in the list)
//                                                                  
//******************************************************************


Student linear_gpa_select(vector <Student> list, const size_t target, size_t &num_compares)
{
      //Find the medians
      vector<Student> medians = get_medians(list, num_compares);

      //Take the median of the medians
      insertion_sort(medians, 0, medians.size(), num_compares);
      Student median_of_medians = medians[medians.size() / 2];

      //Partition based on the median


      Student tmp;
      return tmp;
}


//******************************************************************
//                                                                  
//  Function:   gpa_in_Range
//                                                                  
//  Purpose:    Return the index in the array that is the value  
//              of target largest in the array.
//                                                                  
//  Parameters: list - list of students
//              target - rank of value to be 
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the GPA of the students with the 
//                  target rank.
//
// Calls:       None
//                                                                  
//******************************************************************


vector<Student> gpa_in_Range(vector <Student> list, const double low, const double high, size_t &num_compares){

      vector<Student> students;
      return students;

}


//******************************************************************
//                                                                  
//  Function:   inbetweenGPA
//                                                                  
//  Purpose:    Find and return students between two rankings  
//              based on GPA                                  
//                                                                  
//  Parameters: list - list of students
//              j - first GPA ranking
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the cost in dollars of shipping a
//                  package that weighs weight pounds a distance
//                  of distance miles.
//
// Calls:       function cargo_rates
//                                                                  
//******************************************************************


vector <Student> inbetweenGPA( vector <Student> list, const size_t j, const size_t k, size_t &num_compares){
	
	//Find jth biggest element
      const Student jth_biggest = linear_gpa_select(list, j, num_compares); //Student with the jth biggest gpa

	//Find kth biggest element
      const Student kth_biggest = linear_gpa_select(list, k, num_compares); //Student with the kth biggest gpa

	//Collect elements between j and k.
      if(jth_biggest.gpa <= kth_biggest.gpa)
      {
            return gpa_in_Range(list, jth_biggest.gpa, kth_biggest.gpa, num_compares);
      }
      else { // jth_gpa > kth_gpa
            return gpa_in_Range(list, kth_biggest.gpa, jth_biggest.gpa, num_compares);
      }

      vector<Student> newList;
      return newList;
}


//******************************************************************
//                                                                  
//  Function:   linearSelect
//                                                                  
//  Purpose:    Return the index in the array that is the value  
//              of target largest in the array.
//                                                                  
//  Parameters: list - list of students
//              target - rank of value to be 
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the GPA of the students with the 
//                  target rank.
//
// Calls:       None
//                                                                  
//******************************************************************


Student linear_name_select(vector <Student> list, const size_t target, size_t &num_compares)
{
      Student tmp;
      return tmp;
}


//******************************************************************
//                                                                  
//  Function:   name_in_range
//                                                                  
//  Purpose:    Return the index in the array that is the value  
//              of target largest in the array.
//                                                                  
//  Parameters: list - list of students
//              target - rank of value to be 
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the GPA of the students with the 
//                  target rank.
//
// Calls:       None
//                                                                  
//******************************************************************


vector<Student> name_in_range(vector <Student> list, const string low, const string high, size_t &num_compares){

      vector<Student> tmp;
      return tmp;
}



//******************************************************************
//                                                                  
//  Function:   inbetweenGPA
//                                                                  
//  Purpose:    Find and return students between two rankings  
//              based on GPA                                  
//                                                                  
//  Parameters: list - list of students
//              j - first GPA ranking
//                                                                  
// Member/Global Variables: none
//
// Pre Conditions: variables distance and weight have valid values
//
// Post Conditions: returns the cost in dollars of shipping a
//                  package that weighs weight pounds a distance
//                  of distance miles.
//
// Calls:       function cargo_rates
//                                                                  
//******************************************************************


vector <Student> inbetweenAlpha( vector <Student> list, const size_t j, const size_t k, size_t &num_compares){

	//Find jth largest name
      const Student jth_biggest = linear_name_select(list, j, num_compares);  //jth_name is the value of the jth biggest name in the list

      //Find the kth largest name
      const Student kth_biggest = linear_name_select(list, k, num_compares);  //kth_name is the value of the kth largest name in the list

      //Collect the students with names between jth_name and kth_name
       if(jth_biggest.last_name <= kth_biggest.last_name)
      {
            return name_in_range(list, jth_biggest.last_name, kth_biggest.last_name, num_compares);
      }
      else { // jth_gpa > kth_gpa
            return name_in_range(list, kth_biggest.last_name, jth_biggest.last_name, num_compares);
      }

      vector<Student> newList;
	return newList;
}
