all : simple parallel mpi

simple: cracker_basic.cc
	g++ -std=c++11 -Wall -o simple cracker_basic.cc -lcrypt

parallel: parallel_cracker.cc
	g++ -std=c++11 -Wall -o parallel parallel_cracker.cc -lcrypt -fopenmp

mpi: mpi_cracker.cc
	mpic++ -std=c++11 -Wall -o mpi mpi_cracker.cc -lcrypt


clean:
	rm simple parallel mpi