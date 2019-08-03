all : GameOfLife.o Test_Harness.o
	g++ -Wall GameOfLife.o Test_Harness.o

GameOfLife.o : GameOfLife.cc GameOfLife.h
	g++ -c -Wall GameOfLife.cc

Test_Harness.o : Test_Harness.cc GameOfLife.o
	g++ -Wall -c Test_Harness.cc

clean : 
	rm GameOfLife.o Test_Harness.o a.out