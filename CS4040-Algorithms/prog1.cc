//****************************************************************
//
//          Program: Homework 4 -- main/test file
//
//			Author: Zach Tumbleson
//			Email: zt031514@ohio.edu
//
//			Class: CS4040 - Dr. Chelberg			
//
//			Assignment: Homework 4
//
//			Description: Main program to test the functions 
//						 inbetweenGPA(), and inbetweenAlpha() 
//						 defined in inbetween.h and inbetween.cc,
//						 as well as various helper functions
//
//			Date: 10-24-2018
//
//***************************************************************/

#include "inbetween.h"
#include "student.h"
#include <iostream>

vector<Student> create_test_students(const int num_students);
void test_insertion_sort(vector<Student> list, size_t &num_compares);
void test_get_medians(vector<Student> list, size_t &num_compares);

int main(){

	const int NUMBER_OF_STUDENTS = 16;
	size_t num_compares = 0;

	vector<Student> students = create_test_students(NUMBER_OF_STUDENTS);

	test_insertion_sort(students, num_compares);
	test_get_medians(students, num_compares);
	
	cout << "Compares: " << num_compares << endl << endl;

	return 0;
}

vector<Student> create_test_students(const int num_students){

//Create list of students and print initial result.

	

	float gpa = 4.0;
	int SSN = 1000;
	string first_name = "Brian";
	string last_name = "Smith";
	string major = "Computer Science";

	vector<Student> students(num_students);

	for(int i = 0; i < students.size(); i++){
		students[i].gpa = gpa;
		gpa -= 0.1;

		students[i].SSN = SSN;
		SSN++;

		students[i].major = major;

		students[i].last_name = last_name;
		last_name[0] += 1;

		students[i].first_name = first_name;
	}

	for(int i = 0; i < students.size(); i++){
		cout << students[i].last_name << ", " << students[i].first_name << "- GPA: " << students[i].gpa << endl;
	}

	cout << endl << endl;

	return students;
}

void test_get_medians(vector<Student> list, size_t &num_compares){
	//Get medians and print results to the screen
	vector<Student> medians = get_medians(list, num_compares);
	
	cout << "Number of medians: " << medians.size() << endl;

	for(int j = 0; j < medians.size(); j++)
	{
		cout << medians[j].last_name << ", " << medians[j].first_name << "- GPA: " << medians[j].gpa << endl;
	}

	cout << endl << endl;
}

void test_insertion_sort(vector<Student> list, size_t &num_compares){
	insertion_sort(list, 0, 5, num_compares);

	for(int i = 0; i < list.size(); i++){
		cout << list[i].last_name << ", " << list[i].first_name << "- GPA: " << list[i].gpa << endl;
	}
}