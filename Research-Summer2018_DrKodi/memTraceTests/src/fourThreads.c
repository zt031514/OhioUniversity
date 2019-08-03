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
/*		  Utilizes four simultaneous threads. Threads 2-4 run
/*		  through the function print_word(void *).
/*
/*****************************************************************************/	

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

const int NUM_THREADS = 4;

//this function is called by the second thread to print in parallel
void *print_word(void *word_void_ptr)
{
	
	
	//extract parameter value from void pointer	
	char *word2 = (char *)word_void_ptr;
	
	//print word2
	printf("%s", word2);
	
	//exit second thread
	return NULL;
}

int main(void)
{
	clock_t begin = clock();	

	//Variable declarations	
	char *word1 = "He";
	char *word2 = "llo";
	char *word3 = " wor";
	char *word4 = "ld!";

	//Thread declarations	
	pthread_t print_word2, print_word3, print_word4;

	//BEGIN CREATE THREADS
	//*********************

	//create the second thread
	if(pthread_create(&print_word4, NULL, print_word, word4))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	//create the third thread
	if(pthread_create(&print_word3, NULL, print_word, word3))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	//create the fourth thread
	if(pthread_create(&print_word2, NULL, print_word, word2))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	//END CREATE THREADS
	//*******************

	//BEGIN EXECUTING
	//*******************
	
	//In the 1st thread, print "He"
	printf("\n%s", word1);

	//Wait for second thread to finish executing
	if(pthread_join(print_word4, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	//Wait for third thread to finish
	if(pthread_join(print_word3, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}	
	
	//Wait for the fourth thread to finish
	if(pthread_join(print_word2, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	//END EXECUTING
	//****************

	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	printf("\nThis program took %f seconds to run.\n", elapsed);

	printf("\n\n");
	return 0;
}	
