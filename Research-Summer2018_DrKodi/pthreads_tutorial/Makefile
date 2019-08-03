#targets

#make all executable examples
all : hello tutorial mutex joins condition murphy
	
#Individual Targets for each example program

#makes 4 threads and prints as each completes
hello : hello_world.o
	g++ hello_world.o -o hello -lpthread

hello_world.o : hello_world.c
	g++ -c hello_world.c -lpthread

#Creates 2 threads and returns the results 
tutorial : pthread1.o
	g++ pthread1.o -o tutorial -lpthread

pthread1.o : pthread1.c
	g++ -c pthread1.c -lpthread

#Creates 2 threads, increments a counter in each and returns the result of counter
#Demonstrates how a mutex works
mutex : mutex1.o
	g++ -o mutex mutex1.o -lpthread -fpermissive

mutex1.o : mutex1.c
	g++ -c mutex1.c -lpthread -fpermissive

#Demonstrates the join function for threads
joins : join1.o
	g++ -o joins join1.o -lpthread

join1.o : join1.c
	g++ -c join1.c -lpthread

#demonstrates the use of conditional statements
condition : cond1.o
	g++ -o condition cond1.o -lpthread -fpermissive

cond1.o : cond1.c
	g++ -c cond1.c -lpthread -fpermissive

#simple example from timmurphy.org
murphy : murphyExample.o
	g++ -o murphy murphyExample.o -lpthread

murphyExample.o : murphyExample.c
	g++ -c murphyExample.c -lpthread

#Clean
clean:
	rm pthread1.o hello_world.o mutex1.o join1.o cond1.o murphyExample.o
	rm hello tutorial mutex joins condition murphy



