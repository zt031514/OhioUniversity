//******************************************************************
//
//  mpi_cracker.cc	
//
//  Author: Zach Tumbleson
//
//	Date: 3-30-2019
//
//	Brief: Implements a password cracker according to the description
//		   given in the handout for assignment 5. The program reads in
//		   a list of dictionary words, then brute forces combinations of
//		   dictionary words and digits.
//
//		   Takes cracker_basic and adds OpenMPI framework to enable
//		   the program to run on multiple machines at once
//
//*****************************************************************


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <mpi.h>
using namespace std;

//Used to specify how many dollar signs must be seen to 
//represent the password salt
const int SALT_DOLLAR_COUNT = 3;

//Specify how many input arguments are required
const int NUM_INPUT_ARGS = 3;

//Argument number in argv of the encrypted password filename
const int ENC_PASS_ARG = 1;

//Argument number in argv of the dictionary words filename
const int DICT_ARG = 2;

//*************************************************************
// Function: getEncryptedPasswords                             
//
// Brief: Opens the file specified by enc_pass_file, reads in  
//		  the encrypted passwords and stores the strings in    
//		  the passwords vector parameter.                      
//
// Parameters: vector<string> > &passwords | vector to store   
//							    the encrypted passwords        
//             string enc_pass_file | contains the name of file where
//									  the passwords are stored 
//
//
// Return value: N/A
//
//*************************************************************
void getEncryptedPasswords(vector<string> &passwords, const string enc_pass_file){
		
		string tmp_input;

		ifstream infile;
		infile.open(enc_pass_file.c_str());
		while(!infile.eof()){
			getline(infile, tmp_input); //read in an encrypted password 
										//from the file
			if(tmp_input == ""){//Ignore empty lines
				;
			} else { //Add password to the list
				passwords.push_back(tmp_input);
			}
		}

		infile.close();
}


//*************************************************************
// Function: getDictionaryWords                             
//
// Brief: Opens the file specified by word_file, reads in  
//		  the dictionary words and stores the strings in    
//		  the dictionary vector parameter.                      
//
// Parameters: vector<string> > &dictionary | vector to store   
//							    the dictionary words        
//             string word_file | contains the name of the file
//								  where the words are stored
//
//
// Return value: N/A
//
//*************************************************************
void getDictionaryWords(vector<string> &dictionary, const string word_file){

		string tmp_input;

		ifstream infile;
		infile.open(word_file.c_str());
		while(!infile.eof()){
			getline(infile, tmp_input); //Read in a dictionary word
			if(tmp_input == ""){ //Do not store the line if it is empty
				;
			} else { //Add word to the dictionary
				dictionary.push_back(tmp_input);
			}
		}

		infile.close();
}

//*************************************************************
// Function: crackPassword()                            
//
// Brief: Takes an encrypted password, and a vector of 
//		  dictionary words, and brute forces different
//		  combinations of words and digits.                      
//
// Parameters: vector<string> > &dictionary | vector to store   
//							    the dictionary words        
//             string encrypted | the encrypted password
//
//
// Return value: string password | contains the password if one
//				 is found, contains "" otherwise.
//
//*************************************************************
string crackPassword(const vector<string> &dictionary, const string encrypted){
	string empty = "";

	//Read in the salt

	//Get the location of the third dollar sign
	int dollar_count = 0;
	int cursor = 0;
	while(dollar_count < SALT_DOLLAR_COUNT && cursor < (int) \
		(encrypted.length())){
		if(encrypted[cursor] == '$'){
			dollar_count++;
		}
		cursor++;
	}

	//Read in from the beginning of the string to the end of the salt
	string salt = encrypted.substr(0, cursor-1);
	//cout << "Salt is " << salt << endl;


	//Attempt all single words
	
	for(int i = 0; i < (int)(dictionary.size()); i++){
		string attempt = dictionary[i];
		string result = (string)(crypt(attempt.c_str(), salt.c_str()));

		//cout << attempt << endl;
		if(result == encrypted){ //encryptions match, return password
			return attempt;
		}
		//No match, keep trying
	}
	
	
	//Attempt all single words with digits trailing
	
	for(int i = 0; i < (int)(dictionary.size()); i++){
		for(int j = 0; j < 999; j++){
			string attempt = dictionary[i] + to_string(j);
			
			//cout << attempt << endl;
			string result = crypt(attempt.c_str(), salt.c_str());

			if(result == encrypted){ //encryptions match, return password
				return attempt;
			}
		}
		//No match, keep trying
	}
	

	
	//Attempt all single words with digits preceding
	
	for(int i = 0; i < (int)(dictionary.size()); i++){
		for(int j = 0; j < 999; j++){
			string attempt = to_string(j) + dictionary[i];

			//cout << attempt << endl;
			string result = crypt(attempt.c_str(), salt.c_str());

			if(result == encrypted){ //encryptions match, return password
				return attempt;
			}
		}
		//No match, keep trying
	}
	
	//no matches found, return an empty string
	return empty;
}


int main(int argc, char *argv[]){
	
	//Initiate open MPI links and ranks
	int num_processes;
	int proc_num;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);

	//Load the dictionary onto all machines
	vector<string> dictionary;

	//Get the filename containing the dictionary words
	string word_file = argv[DICT_ARG];

	//Load in the words
	getDictionaryWords(dictionary, word_file);

	//BEGIN CRACKING


	//First process should distribute work to other processes
	if(proc_num == 0){

		if(argc < NUM_INPUT_ARGS){
			cout << "Insufficient command line arguments given." 
				 << endl << endl 
				 << "Program requires the following command line arguments: "
				 << endl << endl 
				 << "Encrypted Password filename: " << endl
				 << "File containing"
				 << " the encrypted passwords to be cracked." 
				 << endl << endl
				 << "Dictionary filename:" << endl
				 << "File containing the dictionary "
				 << "words used for password cracking." 
				 << endl << endl;
			exit(1);
		} else { //both filenames provided, begin trying to crack

			//Load in the encrypted passwords
			vector<string> encrypted_passwords;

			//Get the filename containing the encrypted passwords
			string password_file = argv[ENC_PASS_ARG];

			getEncryptedPasswords(encrypted_passwords, password_file);

			//Used to store the results of crackPassword
			vector<string> passwords( (int)(encrypted_passwords.size()) );

			//Send a single word to each process and let them try to crack the passwords
			for(int i = 0; i < (int)(encrypted_passwords.size()); i++){
				string password = encrypted_passwords[i];
				int destination = i % 10;
				
				if(destination == 0){
					destination++; //don't try to send a password to yourself
				}

				//Send the password to another process to figure out

				//Send the length
				int length = password.length();
				MPI_Send(&length, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
				
				//Send the encrypted password
				MPI_Send(password.c_str(), password.length(), MPI_CHAR, destination, 0, 
					MPI_COMM_WORLD);
			}

			//Read in the results
			for(int i = 0; i < (int)(passwords.size()); i++){
				
				int sender = i % 10;
				if(sender == 0){
					sender++; //Can't receive what you didn't send
				}


				//Read in the length of the result
				int length;
				MPI_Recv(&length, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, 
					MPI_STATUS_IGNORE);

				//Read in the result
				char *returnValue = new char[length + 1];
				MPI_Recv(returnValue, length+1, MPI_CHAR, sender, 0, MPI_COMM_WORLD, 
					MPI_STATUS_IGNORE);

				//Store the result
				passwords[i] = returnValue;
				delete [] returnValue;
			}



			//Print results
			for(int i = 0; i < (int)(passwords.size()); i++){
				cout << passwords[i] << endl;
			}
		}

	} else {
		//Read in the encrypted password from process 0
		

		int length;
		//Read in the length
		MPI_Recv(&length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		//Read in the password
		char *encrypted = new char[length+1];
		MPI_Recv(encrypted, length+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		//Try to crack the password
		string cracked = crackPassword(dictionary, encrypted);

		//Get the length of the password
		length = cracked.length();

		//Sned the length
		MPI_Send(&length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

		//Send the result (the password or "") back to process 0)
		MPI_Send(cracked.c_str(), length+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

		delete [] encrypted;
	}

	MPI_Finalize();
	return 0;
}