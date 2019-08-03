///****************************************
/// @file my_word_count.cc
/// @brief Program written for CS3560 Final Exam
///
///	@Author Zach Tumbleson
///	@date 12-6-2016
///
///*****************************************


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

int countLine(char* pName);
int countChar(char* pName);

int main(int argc, char *argv[])
{
	char default1[] = "Ohio University";
	char default2[] = "Athens";
	int i = 0;
	char pName[100];
	char c;
	ifstream fin;
	if(argc == 0)
	{
		countLine(default1);
		countChar(default2);
	}	

	if(argc == 1 ){	
		char *filename = argv[argc];
		fin.open(filename);
		fin.get(c);
		while(!fin.eof()){
			pName[i] = c;
			i++;
			fin.get(c);
		}
		countLine(pName);
		countChar(pName);
				
	}
	return 0;
}

/*! \fn int main(int argc, char *argv[])
    \brief The main function.
    \param argc is the number of arguments.
    \param argv is a vector of arguments.
*/


int countLine(char* pName)
{
	int i = 0, line_count = 0;
	while(i < strlen(pName))
	{
		if(pName[i] == '\n')
			line_count++;
	}
	cout << line_count << "Lines" << endl;
	return line_count;
}
/*! \fn int countLine(char* pName)
    \brief A function that counts lines
    \param A c-string of characters.
*/

int countChar(char* pName)
{
	int count = strlen(pName);
	cout << count << "Characters";
	return count;
}

/*! \fn int countChar(char* pName)
    \brief A function that counts characters
    \param A c-string of characters.
*/

