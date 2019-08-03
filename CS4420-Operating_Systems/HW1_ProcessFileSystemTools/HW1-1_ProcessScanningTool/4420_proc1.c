/*****************************************************************
/*
/*	4420_proc1.c
/*
/*	Author	  : Zach Tumbleson
/*	Class 	  : CS4420
/*	Assignment: Assignment 1 Part 1
/*
/*	Description: A simple program that opens the stat files
/*		     for any processes currently in the proc 
/*		     filesystem. It then prints the PID, the
/*		     Command, parent PID, State, and the virtual 
/*		     memory size in kilobytes.
/*
/*	Due Date  : Friday, Sept. 7 by 11:59 PM
/*
/****************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(){

	printf("\n\n\tPID\tCommand\t\t\tPPID\tState\tVM Size (bytes)\n");
	printf("\n----------------------------------");
	printf("--------------------------------------\n");

	int pid;
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
				//printf("\n\n%s\n\n", path);

				FILE* statFile = fopen(path, "r"); 				
				if(statFile == NULL){
					printf("File failed\n\n");
					return 1;
				}
				
				char *buffer = NULL;
				size_t length = 0;
							
				getline(&buffer, &length, statFile);
				//printf("Stats: %s:\n\n", buffer);
				
				//temporary buffers to receive tokenized strings from statLine
				char *pid;
				char *command;
				char *ppid; 
				char *state;
				char *vmSize;
				char *garbage;
				const char space[2] = " ";

				//tokenize the statLine string
				pid = strtok(buffer, space);
				printf("\t%s", pid); 				
				for(int i = 1; i < 24; i++)
				{				
					int tokenID = i + 1;
					switch (tokenID){
						case 2: command = strtok(NULL, space); 
							break;
						case 3: state = strtok(NULL, space);
							break;
						case 4: ppid = strtok(NULL, space);
							break;
						case 23: vmSize = strtok(NULL, space);
							break;
						default:
							garbage = strtok(NULL, space);
							break;					
					}
				}
				//printf("\t%s", command);
				if(strlen(command) < 8)
				{
					printf("\t%s\t\t", command);
				}				
				else if(strlen(command) < 16){
					printf("\t%s\t", command);
				}
				else
				{
					printf("\t%s", command);
				}
				printf("\t%s", ppid);
				printf("\t%s", state);
				printf("\t%s", vmSize);
				printf("\n\n");				
				fclose(statFile);
			}
		}
		closedir(dp);
		printf("\n\n\n");
		return 0;
	}
	else
	{
		perror("Couldn't open the directory.");
		return 1;
	}	 	
}
