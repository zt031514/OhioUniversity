/*****************************************************************
/*
/*	4420_proctools_ps.c
/*
/*	Author	  : Zach Tumbleson
/*	Class 	  : CS4420
/*	Assignment: Assignment 1 Part 3
/*
/*	Description: A simple program that implements the unix
/*		     ps tool.
/*
/*	Due Date  : Wednesday, Oct. 3rd by 11:59 PM
/*
/****************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h> //for NaN

struct process{
	long pid;
	char *command;
	char state;
	double cpu;
	double mem;
	char *vmSize;
	long int rsSize;
};

//All "sortBy" functions use simple bubble sort
//from https://www.geeksforgeeks.org/bubble-sort/

void sortByCPU(struct process processes[], int num_processes){

	struct process temp;

	for (int i = 0; i < num_processes-1; i++){
   		for (int j = 0; j < num_processes-i-1; j++){
           		if (processes[j].cpu > processes[j+1].cpu){
				temp = processes[j+1];
				processes[j+1] = processes[j];
				processes[j] = temp;
			}
		}
	}
}

void sortByMEM(struct process processes[], int num_processes){
	struct process temp;

	for (int i = 0; i < num_processes-1; i++){
   		for (int j = 0; j < num_processes-i-1; j++){
           		if (processes[j].mem > processes[j+1].mem){
				temp = processes[j+1];
				processes[j+1] = processes[j];
				processes[j] = temp;
			}
		}
	}
}

void sortByPID(struct process processes[], int num_processes){

	struct process temp;

	for (int i = 0; i < num_processes-1; i++){
   		for (int j = 0; j < num_processes-i-1; j++){
           		if (processes[j].pid > processes[j+1].pid){
				temp = processes[j+1];
				processes[j+1] = processes[j];
				processes[j] = temp;
			}
		}
	}
}

void sortByCommand(struct process processes[], int num_processes){

	struct process temp;

	for (int i = 0; i < num_processes-1; i++){
   		for (int j = 0; j < num_processes-i-1; j++){
           		if (strcmp(processes[j].command, processes[j+1].command) > 0){
				temp = processes[j+1];
				processes[j+1] = processes[j];
				processes[j] = temp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	enum sorts{CPU, MEM, PID, COM};
	enum sorts sortType;

	if(argc != 2){
		printf("\n\tPlease give one of the following command line arguments: -cpu, -mem, -pid, -com");
		printf("\n\tNo command line argument given, closing...\n\n");
		return 1;
	}
	else if(strcmp(argv[1], "-cpu") == 0){
		sortType = CPU;
	}
	else if(strcmp(argv[1], "-mem") == 0){
		sortType = MEM;
	}
	else if(strcmp(argv[1], "-pid") == 0){
		sortType = PID;
	}
	else if(strcmp(argv[1], "-com") == 0){
		sortType = COM;
	}
	else
	{
		printf("\n\tPlease give one of the following command line arguments: -cpu, -mem, -pid, -com");
		printf("\n\tInvalid command line argument given, closing...\n\n");
		return 1;
	}

	const int PARTS_PER = 100;
	struct process processes[10000];
	int num_processes = 0;

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
				long pid;
				char *command;
				char *state;
				char *vmSize;
				char *garbage;
				long int rsSize;
				const char space[2] = " ";
				unsigned long utime;
				unsigned long stime;
				unsigned long long startTime;

				//tokenize the statLine string
				pid = atol(strtok(buffer, space));
				//printf("\t%ld\n", pid);
				for(int i = 1; i < 24; i++)
				{
					int tokenID = i + 1;
					switch (tokenID){
						case 2: command = strtok(NULL, space);
							break;
						case 3: state = strtok(NULL, space);
							break;
						case 14: utime = atol(strtok(NULL, space));
							break;
						case 15: stime = atol(strtok(NULL, space));
							break;
						case 22: startTime = atol(strtok(NULL, space));
							break;
						case 23: vmSize = strtok(NULL, space);
							break;
						case 24: rsSize = atol(strtok(NULL, space));
							break;
						default:
							garbage = strtok(NULL, space);
							break;
					}
				}

				processes[num_processes].pid = pid;

				//Remove parentheses from the command
				if(strcmp(command, "(Web") == 0)
					processes[num_processes].command = "Web";
				else{
					for(int i = 0; i < strlen(command) - 1; i = i + 1)
					{
						command[i] = command [i + 1];
					}


					processes[num_processes].command = command;
					command[strlen(command) - 1] = '\0';
					command[strlen(command) - 1] = '\0';

					processes[num_processes].command = command;
				}

				processes[num_processes].state = state[0];
				processes[num_processes].vmSize = vmSize;
				processes[num_processes].rsSize = rsSize;
				num_processes = num_processes + 1;

				fclose(statFile);

				//
				//Calculate %cpu
				//
				sprintf(path, "/proc/uptime");

				FILE* uptimeFile = fopen(path, "r");

				if(uptimeFile == NULL){
					printf("File failed\n\n");
					return 1;
				}

				char upTimeStr[1000];
				fscanf(uptimeFile, "%s ", upTimeStr);
				long int uptime = atol(upTimeStr);

				fclose(uptimeFile);

				double processTime = (utime / sysconf(_SC_CLK_TCK)) + (stime / sysconf(_SC_CLK_TCK));
				double realTime = uptime - (startTime / sysconf(_SC_CLK_TCK));
				double cpu_percent = processTime * PARTS_PER / realTime;

				//assign to struct
				processes[num_processes].cpu = cpu_percent;

				//
				//Calculate %mem
				//
				long phys_pages = sysconf(_SC_PHYS_PAGES);
				long page_size = sysconf(_SC_PAGE_SIZE);

				long phys_mem_size = phys_pages * page_size;
				double mem_percent = (rsSize * getpagesize() * PARTS_PER) / phys_mem_size;

				//assign to struct
				processes[num_processes].mem = mem_percent;
			}
		}
		closedir(dp);


		switch (sortType){

			case CPU: sortByCPU(processes, num_processes);
				break;
			case MEM: sortByMEM(processes, num_processes);
				break;
			case PID: sortByPID(processes, num_processes);
				break;
			case COM: sortByCommand(processes, num_processes);
				break;
			default:
				break;
		}

		//Print beginning of table
		printf("\n\n\tPID\tCommand\t\t\tState\t%%CPU \t\t%%MEM\t\tVM Size (bytes)\t\tRSS\n");

		printf("\n------------------------------------------------");
		printf("----------------------------------------------------------------------\n");

		//print data
		for(int i = 0; i < num_processes; i = i + 1){
			printf("\t%ld", processes[i].pid);

			if(strlen(processes[i].command) < 8)
				{
					printf("\t%s\t\t", processes[i].command);
				}
				else if(strlen(processes[i].command) < 16){
					printf("\t%s\t", processes[i].command);
				}
				else
				{
					printf("\t%s", processes[i].command);
				}

			printf("\t%c", processes[i].state);

			if(processes[i].cpu < 0)
				printf("\t%f\t", processes[i].cpu);
			else
				printf("\t%f", processes[i].cpu);

			printf("\t%f", processes[i].mem);

			if(strlen(processes[i].vmSize) < 8)
				printf("\t%s\t", processes[i].vmSize);
			else
				printf("\t%s", processes[i].vmSize);

			printf("\t\t%ld\n", processes[i].rsSize);
		}

		printf("\n\n");
		return 0;
	}
	else
	{
		perror("Couldn't open the directory.");
		return 1;
	}
}


