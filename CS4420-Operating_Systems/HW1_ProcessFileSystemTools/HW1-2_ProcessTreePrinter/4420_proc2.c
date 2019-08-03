/*****************************************************************
/*
/*	4420_proc2.c
/*
/*	Author	  : Zach Tumbleson
/*	Class 	  : CS4420
/*	Assignment: Assignment 1 Part 2
/*
/*	Description: A simple program that prints a graph of 
/*		     parent-child process relationships. Each
/*		     parent process is listed first, with its
/*		     children listed next to it.
/*
/*	Due Date  : Monday, Sept. 10 by 11:59 PM
/*
/****************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void getChildren(int current, int childrenIndexes[]);
void printChildren(int childrenIndexes[], int numChildren);

//"struct" to hold the pid, ppid, and name of process for each process. The same index for each array
// references the same process' information. 
int processIDs[1000];
int parentID[1000];
int wasPrinted[1000];
char processNames[1000][1000]; // global to get around annoying pointer/type issues 
int layer = 0;		       //with passing arrays of c-strings as function arguments
int num_processes = 0;

int main(){

	//printf("\n\n\tPID\tCommand\t\t\tPPID\tState\tVM Size (bytes)\n");
	//printf("\n----------------------------------");
	//printf("--------------------------------------\n");

	int pid;

	int childrenIndexes[1000];
	int num_children = 0;	
	
	//Add dummy process 0
	processIDs[0] = 0;
	parentID[0] = 0;
	strcpy(processNames[0], "(dummy)");
		
	num_processes = 1;
	
	struct dirent *ep;
	DIR* dp;
	dp = opendir ("/proc");
		
	if(dp != NULL)
	{
		while(ep = readdir(dp))
		{
			pid = strtol(ep->d_name, NULL, 10);
			if((ep->d_type == DT_DIR) && (pid > 0))
			{
				char path[1000];
				sprintf(path, "/proc/%d/stat", pid);

				FILE* statFile = fopen(path, "r"); 				
				if(statFile == NULL){
					printf("File failed\n\n");
					return 1;
				}
				
				char *buffer = NULL;
				size_t length = 0;
							
				getline(&buffer, &length, statFile);
				
				//temporary buffers to receive tokenized strings from statLine
				char *pid;
				char *command;
				char *ppid; 
				char *garbage;
				const char space[2] = " ";

				//tokenize the statLine string
				pid = strtok(buffer, space);
				
				for(int i = 1; i < 24; i++)
				{				
					int tokenID = i + 1;
					switch (tokenID){
						case 2: command = strtok(NULL, space); 
							break;
						case 4: ppid = strtok(NULL, space);
							break;
						default:
							garbage = strtok(NULL, space);
							break;					
					}
				}

				processIDs[num_processes] = strtol(pid, NULL, 10);
				parentID[num_processes] = strtol(ppid, NULL, 10);
				strcpy(processNames[num_processes], command);
				wasPrinted[num_processes] = 0;
				num_processes = num_processes + 1;		
				fclose(statFile);
			}
		}
		closedir(dp);

		//test loop for viewing pids, ppids and program names
		for(int i = 0; i < num_processes; i++)
		{
			printf("%d", processIDs[i]);
			printf("\t%d", parentID[i]);
			printf("\t%s\n", processNames[i]);
		}
		printf("Number of processes: %d\n\n\n", num_processes);
				

		for(int i = 0; i < num_processes; i++)
		{
			if(wasPrinted[i] == 0)
			{
				getChildren(i, childrenIndexes);		
			}
		printf("\n\n");
		}
	}
	else
	{
		perror("Couldn't open the directory.");
		return 1;
	}	 	
}


void getChildren(int current, int childrenIndexes[])
{
	int num_children = 0;

	for(int i = 0; i < num_processes; i++)
	{
		if(parentID[i] == processIDs[current]){
			childrenIndexes[num_children] = i;
			num_children = num_children + 1;		
		}
	}
	printChildren(childrenIndexes, num_children);
}


void printChildren(int childrenIndexes[], int numChildren){
	
		
	for(int i = 0; i < numChildren; i++)
	{
		printf("%d%s", processIDs[childrenIndexes[i]], processNames[childrenIndexes[i]]);
		layer = layer + 1;
	}
}

