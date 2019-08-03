/*****************************************************************************
/*
/*  Author	: Zach Tumbleson
/*  Lab		: Dr. Avinash Kodi
/*  Department	: Ohio University EECS
/*  Date	: 5-24-2018  		
/*
/*  Description	: 1st of 2 test programs to test
/*		  the pintool atomic-memory-trace
/*		  at https://github.com/stevenpelley/atomic-memory-trace
/*		  Uses no explicit multithreading.
/*
/*****************************************************************************/	

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	clock_t begin = clock();	
	const char *word1 = "Hello";
	const char *word2 = " world!";
	
	//print "Hello World!"
	printf("\n%s", word1);
	printf("%s\n\n", word2);
	

	clock_t end = clock();
	double time_Elapsed = double(end-begin) / CLOCKS_PER_SEC;
	printf("\nThis program took %f second to run\n", time_Elapsed);
	return 0;
}

	
