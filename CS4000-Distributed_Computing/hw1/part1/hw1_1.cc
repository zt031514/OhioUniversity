//******************************************************
//
//  File: hw1_1.cc
//  Author: Zach Tumbleson
//  Created: 2/1/2019
//  Description: Basic openMP program for HW1 problem 1 
//	 	 that creates several threads
//		 Outputs a message from each thread
//
//******************************************************

#include <iostream>
#include <string>
#include <omp.h>

void helloThread();

int main(){	
	#pragma omp parallel	
		helloThread();	
	return 0;
}

void helloThread(){
	std::string name = "Zach Tumbleson's";
	#pragma omp critical	
		std::cout << "Hello from thread " << omp_get_thread_num() << "." << std::endl <<
		"This is " << name << " 'first' parallel program." << std::endl <<
		"There are currently " << omp_get_num_threads() << " threads running." << 
		std::endl << std::endl;
}
