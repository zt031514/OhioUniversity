/*****************************************************************************
/*
/*  Author	: Zach Tumbleson
/*  Lab		: Dr. Avinash Kodi
/*  Department	: Ohio University EECS
/*  Date	: 5-24-2018  		
/*
/*  Description	: Test programs to test
/*		  the pintool atomic-memory-trace
/*		  at https://github.com/stevenpelley/atomic-memory-trace
/*		  Utilizes two simultaneous threads. The second thread runs
/*		  through the function print_word(void *).
/*
/*****************************************************************************/	

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

const int NUM_THREADS = 2;

//this function is called by the second thread to print in parallel
void *print_word(void *word_void_ptr)
{

	//extract parameter value from void pointer	
	char *word2 = (char *)word_void_ptr;
	
	//print word2
	printf("%s\n", word2);
	
	//exit second thread
	
	return NULL;
}

int main(void)
{
	
	clock_t begin = clock();

	const char *word1 = "Hello";
	char *word2;
	word2 = " world!";
	
	//Create a second thread to print word2
	
	pthread_t print_word2;

	if(pthread_create(&print_word2, NULL, print_word, word2))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	
	//In the 1st thread, print "Hello"
	printf("\n%s", word1);

	//Wait for second thread to finish executing
	if(pthread_join(print_word2, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}	
	
	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	printf("\nThis program took %f seconds to run.\n", elapsed);

	return 0;
}

	
