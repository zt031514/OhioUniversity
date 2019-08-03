/*
 * Headstart for Assignment 1
 * CS 4420/5420
 * 
 *
 * Student Name: Zach Tumbleson 
 *
 *  Helper functions for mybash.c
 *	Defined here to reduce size of mybash.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"

#ifndef HELPER_H
#define HELPER_H


void printPrompt()
{
	//Print username, device name, and current working directory and $ for terminal prompt
	char buffer[50];
	printf("\n%s@%s:%s/$ ", getenv("USER"), getenv("NAME"), getcwd(buffer, 50));
}

//check if the command passed is a built in command
int isBuiltIn(const char *command){
			if(strcmp(command, "cd") == 0){
				return 1;
			}
			else if(strcmp(command, "pwd") == 0){
				return 1;
			}
			else if(strcmp(command, "pwd") == 0){
				return 1;
			}
			else if(strcmp(command, "exit") == 0){
				return 1;
			}
			else if(strcmp(command, "set") == 0){
				return 1;
			}
			else if(strcmp(command, "DEBUG=yes") == 0){
				return 1;
			}
			else if(strcmp(command, "DEBUG=no") == 0){
				return 1;
			}
			else{
				return 0;
			}
}

//print whether a command has the "run in background" option turned on
void printBackground(int background){
	if(background == 1){
		printf("Background option : ON\n");
	}
	else{
		printf("Background option : OFF\n");
	}
}


void printBuiltIn(char *command){	
	if(isBuiltIn(command)){
		printf("Built-in command  : YES\n");
	}
	else{
		printf("Built-in command  : NO\n");
	}
}

void printDebug(const struct CommandData *commands){
	printf("\nDEBUG OUTPUT: \n");
	printf("------------------------------------------\n");

	printf("\nDEBUG: Number of simple commands : %d\n", commands->numcommands);
			for(int i = 0; i < commands->numcommands; i++){
				printf("DEBUG: command%d\t: %s\n", i+1, commands->TheCommands[i].command);
				if(commands->TheCommands[i].numargs != 0)
				{	
					for(int j = 0; j < commands->TheCommands[i].numargs; j++){
						printf("DEBUG: arg[%d]\t\t: %s\n", j, commands->TheCommands[i].args[j]);
					}
				}	
			}
			printf("DEBUG: Input file\t: %s\n", commands->infile);
			printf("DEBUG: Output file\t: %s\n", commands->outfile);
			printf("DEBUG: ");
			printBackground(commands->background);
			printf("DEBUG: ");
			printBuiltIn(commands->TheCommands[0].command);
	printf("--------------------------------------------\n\n");
}

int setDebug(char *command, int *status){
	//Check for Debugging
	int debugging = 0; //Return 1 if command sets the debug_on variable

	if(strcmp(command, "DEBUG=yes\n") == 0){
		(*status) = 1;
		printf("Debugging is on");
		debugging = 1;
	}
	//Debugging
	else if(strcmp(command, \
		"DEBUG=no\n") == 0)
	{
		(*status) = 0;
		printf("Debugging is off");
		debugging = 1;
	}
	return debugging;
}

void handleBuiltIns(const struct CommandData *commands, char **environ){
	//Change directory
	if(strcmp(commands->TheCommands[0].command, "cd") == 0){
		int success = 0;
		if(commands->TheCommands[0].numargs == 0){
			//No arguments, change directory to home

			success = chdir(getenv("HOME"));
			if(success == -1){
				printf("Something went wrong, going" \
				 " back to previous directory");
			}
		}
		else{ //argument for directory provided
			success = chdir(commands->TheCommands[0].args[0]);
			if(success == -1){
				printf("Something went wrong, going" \
				" back to previous directory");
			}
		}
	}	
	//print the current working directory
	else if(strcmp(commands->TheCommands[0].command, "pwd") == 0){
		char buffer[100];
		printf("%s\n", getcwd(buffer, 100));
	}	
	//print unix environment to the terminal screen
	else if(strcmp(commands->TheCommands[0].command, "set") == 0){
		if (commands->TheCommands[0].numargs == 0){
	  	  	//print environment
			for(int i = 0; environ[i] != NULL; i++){
				printf("%s\n", environ[i]);
			}	
		}	
	}
}

#endif