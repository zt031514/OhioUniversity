#targets

all : oneThread twoThreads fourThreads

#Base program, runs with one thread, two sequential printf statements
oneThread : oneThread.o
	g++ -o oneThread oneThread.o

oneThread.o : oneThread.c
	g++ -c oneThread.c

#Base program, but printing is broken into two threads
twoThreads : twoThreads.o
	g++ -o twoThreads twoThreads.o -lpthread

twoThreads.o : twoThreads.c
	g++ -c twoThreads.c -lpthread

#Base program, but printing is divided between four threads
fourThreads : fourThreads.o
	g++ -o fourThreads fourThreads.o -lpthread
	
fourThreads.o : fourThreads.c
	g++ -c fourThreads.c -lpthread

clean : 
	rm oneThread twoThreads fourThreads
	rm oneThread.o twoThreads.o fourThreads.o
