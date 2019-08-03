#Makefile for my_word_count.cc 

all : count doc

count : my_word_count.cc
	g++ my_word_count.cc -o count
clean : 
	-rm a.out

doc : 
	doxygen -g Doxyfile
	doxygen Doxyfile

check :
	cppcheck my_word_count.cc
	valgrind ./count
