/*
 * Headstart for Assignment 1
 * CS 4420/5420
 * 
 *
 * Student Name: Zach Tumbleson 
 *
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "parser.h"
#include <unistd.h>


int main(int argc, char *argv[])
{
	struct CommandData *commands = (struct CommandData *) malloc (1000);
	int errorOccurred = 0;
	char buffer[50];
	char *commandLine;
	int nbytes = 200;
	int bytesRead;
	
	size_t length;
	
	do
	{ 	//Print current working directory and $ for terminal prompt
		printf("\n%s$ ", getcwd(buffer, 50));
		
		//Get and parse command line
		commandLine = (char *) malloc (nbytes + 1); 
		bytesRead = getline(&commandLine, &length, stdin);
		errorOccurred = ParseCommandLine(commandLine, commands);
		
		//Close program if getline or parsing fails
		if(!errorOccurred || bytesRead == -1){
			printf("Error occured, closing.\n\n");
			exit(1);
		}
		else{ //No failures, print command information
			printf("\nNumber of simple commands : %d\n", commands->numcommands);
			for(int i = 0; i < commands->numcommands; i++){
				printf("command%d\t: %s\n", i+1, commands->TheCommands[i].command);
				if(commands->TheCommands[i].numargs != 0)
				{	
					for(int j = 0; j < commands->TheCommands[i].numargs; j++){
						printf("arg[%d]\t\t: %s\n", j, commands->TheCommands[i].args[j]);
					}
				}
			}

			printf("Input file\t: %s\n", commands->infile);
			printf("Output file\t: %s\n", commands->outfile);
			
			if(commands->background == 1)
				printf("Background option : ON\n");
			else
				printf("Background option : OFF\n");

			//check if first command is a built-in command
			if(strcmp(commands->TheCommands[0].command, "set") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "cd") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "exit") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "jobs") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "kill") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "bg") == 0){
				printf("Built-in command  : YES\n");
			}
			else if(strcmp(commands->TheCommands[0].command, "pwd") == 0){
				printf("Built-in command  : YES\n");
			}
			else{
				printf("Built-in command  : NO\n");
			}
		}
	}while(strcmp(commands->TheCommands[0].command, "exit") != 0);

    exit(0);
}