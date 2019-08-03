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
#include "helpers.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <libgen.h>

extern char** environ;

int main(int argc, char *argv[])
{

	struct CommandData *commands = (struct CommandData *) malloc (1000);
	int errorFree = 0;
	char *commandLine;
	int nbytes = 200;
	int bytesRead;
	
	int status = -1;
	int debug_on = 0;
	
	size_t length = 0;
	
	int usingPipes[2];
	int infile = 0, outfile = 0;

	while(1){
		printPrompt();

		//Get and parse command line
		commandLine = (char *) malloc (nbytes + 1); 
		bytesRead = getline(&commandLine, &length, stdin);
		
		if(setDebug(commandLine, &debug_on)){
			;
		}
		
		else
		{	//command is not for debugging
			errorFree = ParseCommandLine(commandLine, commands);

			//Stop execution if getline or parsing fails
			if(!errorFree || bytesRead == -1)
			{
				printf("Getline or parsing error occured\n\n");
				exit(1);
			} 
			else{ //No failures, start executing
				
				//exit loop if "exit" command is given
				if(strcmp(commands->TheCommands[0].command, "exit") == 0){
					//exit received
					//mem leaks
					free(commandLine);
					free(commands);
					return 0;
				}

				//print debug info for the commands if debugging is on
				if(debug_on){
					printDebug(commands);
				}
				//	Insert I/O direction
				
				//Check for pipes, more than 1 command means
				//piping is involved
				if(commands->numcommands > 1){
					//Create two pipes, one read and one write
					int pipeFailure = pipe(usingPipes);
					if(pipeFailure){
						printf("Pipe creation failed.\n");
					}
				}

				if(commands->infile != NULL){
					infile = open(commands->infile, O_RDONLY);
					dup2(infile, STDIN_FILENO);
				}

				if(commands->outfile != NULL){
					outfile = open(commands->outfile, O_WRONLY);
					dup2(outfile, STDIN_FILENO);
				}
				
				for(int i = 0; i < commands->numcommands; i++){

					if(isBuiltIn(commands->TheCommands[i].command)){
						handleBuiltIns(commands, environ);
					}
					else{ //Not a built-in command
						int pid = fork();
						if(pid != 0){
							//Parent process
							close(usingPipes[0]);//parent doesn't need pipes
							close(usingPipes[1]);//close them here
							if(commands->background == 0){
								wait(&status);
								
							}
						}
						else{  //Child process


							if(i == 0){//first command executed, check for input redir.
								if(commands->infile != NULL){ //infile present
									dup2(infile, STDIN_FILENO); //Direct stdin from the input file
									close(infile); //new fd created, close orignal file
								}

								//Check to see if pipes are needed
								if(commands->numcommands > 1){ //2 commands present, pipe needed
									close(usingPipes[0]); //close pipe in prep. for write
									//printf("Writing to pipe\n");
									dup2(usingPipes[1], STDOUT_FILENO);	//direct write end to stdout
									close(usingPipes[1]); //new fd created, close original pipe						
								}
							}
							if(i == commands->numcommands-1){ 
								
								if(commands->numcommands > 1){ 
									//second command is being executed, pipe input from first command
									close(usingPipes[1]); //prep pipe for read
									//printf("Reading from pipe\n");
									dup2(usingPipes[0], STDIN_FILENO); //read STDIN From pipe
									close(usingPipes[0]); //new fd created, cloes original pipe
								}
								if(commands->outfile != NULL){
									//outfile present, executing last command in the pipeline
									dup2(outfile, STDOUT_FILENO); //direct STDOUT to the outfile
									close(outfile); //new fd created, close original file
								}
								
							}

							//Fix parser issue for arguments
							if(commands->TheCommands[i].numargs != 0){
								char *new_args[12];
								new_args[0] = (char *) malloc (sizeof(commands->TheCommands[i].command));
							
								//add arguments from commandData struct to new_args
								for(int k = 1; k < commands->TheCommands[i].numargs+1; k++)
								{
									new_args[k] = (char *) malloc (sizeof(commands->TheCommands[i].args[k-1]));
									strcpy(new_args[k], commands->TheCommands[i].args[k-1]);
								}

								//Add command name, strip away any path information
								//use basename from <libgen.h>
								char command[50];
								strcpy(command, commands->TheCommands[i].command);
								strcpy(command, basename(command));
								
								//execute command with corrected arguments.
								if(i==0){printf("Executing ls\n");}
								if(i==1){printf("Executing grep\n");}
								execvp(commands->TheCommands[i].command, new_args);

								exit(0);
							}
						}
					}
				}			
			}		
		}			
	}			
}		