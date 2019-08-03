// This file is provided for your benefit.
// It illustrates a potential implementation of a main program that
// tests your algorithm for this problem.
//
// It also illustrates one way to compute the time your program takes to
// complete its task in real-world seconds, which can be used to
// compare two potential implementations to see which one might be
// faster.
//
// NOTE: The code in this file does NOT conform to the style
// guidelines for this class, so would not get full points if
// submitted as is.
//
// Written by Prof. David Chelberg
// last-modified: Wed Oct 17 15:10:27 2018
//
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include "student.h"

using std::vector;
using std::cout;
using std::endl;

/*! Name: timeval2Sec
    
    Description: Computes the number of seconds from a timeval in 
                 microseconds.
      
    Side effects: None.

    \param T The timeval in microseconds.

    \return double The number of seconds in the timeval.
*/
double timeval2sec(const timeval& T) {
  // Constant for time unit conversion
  const double USEC_TO_SEC = 1000000.0;

  return ((double) T.tv_sec + (double) (T.tv_usec / USEC_TO_SEC));
}

/*! Name: timeofday
  
    Description: Computes the time of day in seconds.
    
    Side effects: Gets the time of day and stores it in T.

    \return timeval2sec(T) The time of day in seconds.
*/
double timeofday() {
  timeval T;
  gettimeofday(&T, NULL);
  return (timeval2sec(T));
}

// Sample inbetween functions, they need more comments.  
// 

// The following code should be in a separate files called
// inbetween.cc and inbetween.h
//
vector <Student> inbetweenGPA(vector <Student> list,
			      const size_t j,
			      const size_t k,
			      size_t &num_compares)
{
  // Code goes here
}

vector <Student> inbetweenAlpha(vector <Student> list,
				const size_t j,
				const size_t k,
				size_t &num_compares)
{
  // Code goes here
}
  
// Sample generateStudents, needs more comments.
// One way you can implement this is to randomly generate student
// records
// Hint: to ensure no two students have the same name, and SSN, you
// could make the SSN be equal to the index i.
vector<Student> generateStudents(size_t num)
{
  vector <Student> testing;
  for (size_t i = 0; i<num; ++i) {
    // Your code goes here.
  }
  return(testing);
}

// Sample Main, needs more comments.
int main ()
{
  vector<Student> Students;
  size_t num_compares=0;
  // Note the following value is just for illustration, you should
  // test your code on many different sized inputs.
  const size_t NUM_STUDENTS=1000000;

  // Is this in the right place for this statement?
  double start=timeofday();

  // Test first function.
  Students = generateStudents(NUM_STUDENTS);
  vector<Student> answer = inbetweenGPA(Students, 1, 10, num_compares);

  cout << "inbetweenGPA took " << timeofday() - start << " seconds" 
       << " on input of size " << NUM_STUDENTS << endl;

  cout << "inbetweenGPA took " << num_compares << " comparisons" 
       << " on input of size " << NUM_STUDENTS << endl;

  cout << "There are " << answer.size() << " students in the answer" << endl;

  // Now test second function.
  num_compares=0;
  start=timeofday();
  vector<Student> answer = inbetweenAlpha(Students, 100000, 200000, num_compares);

  cout << "inbetweenAlpha took " << timeofday() - start << " seconds" 
       << " on input of size " << NUM_STUDENTS << endl;

  cout << "inbetweenAlpha took " << num_compares << " comparisons" 
       << " on input of size " << NUM_STUDENTS << endl;

  cout << "There are " << answer.size() << " students in the answer" << endl;

  return(EXIT_SUCCESS);
}
