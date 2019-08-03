//******************************************************************
//
//  parallel_cracker.cc	
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
//		   Adds parallelism via openmp to the main and crackPassword()
//		   functions
//
//*****************************************************************

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include "omp.h"
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
	string password =""; //only one thread will get a success
						//store it here
	bool found = false; //Indicate whether a password has been found

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
	#pragma omp parallel for
	for(int i = 0; i < (int)(dictionary.size()); i++){
		if(!found){

			string attempt = dictionary[i];
			string result = (string)(crypt(attempt.c_str(), salt.c_str()));

			//cout << attempt << endl;
			if(result == encrypted){ //encryptions match
				password = attempt;
				found = true;
			}
			//No match, keep trying
		}
	}

	if(found){
		return password;
	}
	
	
	//Attempt all single words with digits trailing
	#pragma omp parallel for
	for(int i = 0; i < (int)(dictionary.size()); i++){
		#pragma omp parallel for
		for(int j = 0; j < 999; j++){
			if(!found){

				string attempt = dictionary[i] + to_string(j);
				
				//cout << attempt << endl;
				string result = crypt(attempt.c_str(), salt.c_str());

				if(result == encrypted){ //encryptions match, return password
					password = attempt;
					found = true;
				}
			}
			//No match, keep trying
		}
	}
	
	if(found){
		return password;
	}

	
	//Attempt all single words with digits preceding
	#pragma omp parallel for
	for(int i = 0; i < (int)(dictionary.size()); i++){
		#pragma omp parallel for
		for(int j = 0; j < 999; j++){
			if(!found){

				string attempt = to_string(j) + dictionary[i];

				//cout << attempt << endl;
				string result = crypt(attempt.c_str(), salt.c_str());

				if(result == encrypted){ //encryptions match, return password
					password = attempt;
					found = true;
				}
			}
			//No match, keep trying
		}
	}
	
	if(found){
		return password;
	}

	/*
	//Attempt all double word combinations
	#pragma omp parallel for collapse(2)
	for(int i = 0; i < (int)(dictionary.size()); i++){
		for(int j = 0; j < (int)(dictionary.size()); j++){
			string attempt = dictionary[i] + dictionary[j];
			
			string result = crypt(attempt.c_str(), salt.c_str());

			if(result == encrypted){ //encryptions match, return password
				password = attempt;
				found = true;
				#pragma omp cancel for
			}
		}
		//No match, keep trying
	}

	if(found){
		return password;
	}

	//Attempt all double word combinations with digits in between
	#pragma omp parallel for collapse(3)
	for(int i = 0; i < (int)(dictionary.size()); i++){
		for(int j = 0; j < (int)(dictionary.size()); j++){
			for(int k = 0; k < 999; k++){
				string attempt = dictionary[i] + to_string(k) \
								 + dictionary[j];
								
				string result = crypt(attempt.c_str(), salt.c_str());

				if(result == encrypted){ //encryptions match, return password
					password = attempt;
					found = true;
					#pragma omp cancel for
				}
			}
		}
		//No match, keep trying
	}
	
	if(found){
		return password;
	}
	*/
	//no matches found, return an empty string
	return empty;
}


int main(int argc, char *argv[]){

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
		
		//Master vectors for storing dictionary words and encrypted passwords
		vector<string> dictionary;
		vector<string> encrypted_passwords;

		//Get the filename containing the encrypted passwords
		string password_file = argv[ENC_PASS_ARG];

		//Get the filename containing the dictionary words
		string word_file = argv[DICT_ARG];

		getEncryptedPasswords(encrypted_passwords, password_file);
		getDictionaryWords(dictionary, word_file);

		//Used to store the results of crackPassword
		vector<string> passwords( (int)(encrypted_passwords.size()) );

		//BEGIN CRACKING
		#pragma omp parallel for
		for(int i = 0; i < (int)(passwords.size()); i++){
			string tmp_pw; //store the result temporarily
			tmp_pw = crackPassword(dictionary, encrypted_passwords[i]);
			if(tmp_pw == ""){
				passwords[i] = ("Password not found");
			} else { //Real password found
				passwords[i] = ("Password:" + tmp_pw);
			}
		}

		//Print results
		for(int i = 0; i < (int)(passwords.size()); i++){
			cout << passwords[i] << endl;
		}

	}
}

#endif