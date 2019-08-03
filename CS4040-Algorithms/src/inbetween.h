//*********************************************************
//
//          Program: Homework 4 -- inbetween.h
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
//*********************************************************/

#include <vector>
#include "student.h"
using namespace std;


//GPA functions
void insertion_sort(vector<Student> &list, int start, int end, size_t &num_compares);
vector<Student> get_medians(vector<Student> list, size_t &num_compares);
int partition(vector<Student> list, const int p, const int r, size_t &num_compares);
Student linear_gpa_select(vector <Student> list, const size_t target, size_t &num_compares);
vector<Student> gpa_in_Range(vector <Student> list, const double low, const double high, size_t &num_compares);

vector <Student> inbetweenGPA( vector <Student> list, const size_t j, const size_t k, size_t &num_compares);

//Alpha functions
Student linear_name_select(vector <Student> list, const size_t target, size_t &num_compares);
vector<Student> name_in_range(vector <Student> list, const string low, const string high, size_t &num_compares);

vector <Student> inbetweenAlpha( vector <Student> list, const size_t j, const size_t k, size_t &num_compares); 
