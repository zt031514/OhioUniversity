//******************************************************************* 
//                                                                    
//  Program:  Program 1 Student Records FindMaxMin
//                                                                     
//  Author:  Prof. David Chelberg
//  Email: chelberg@ohio.edu
//  ID: XXX-XX-XXXX
//                                                                    
//  Course: CS4040
//                                                                    
//  Description:  This file contains the Class definition for records used in FindMaxMin code.
//                
// Originally written for CS4040/5040
//
// last-modified: Fri Oct 27 15:24:44 2017
//                
//*******************************************************************
//
// NOTE YOU MAY NOT MODIFY THIS FILE IN ANY WAY FOR THIS ASSIGNMENT!
#ifndef student_h
#define student_h
#include <string>

using std::string;

class Student {
  public:
  string SSN;
  string first_name;
  string last_name;
  string major;
  float  gpa;
};

#endif
