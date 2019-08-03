#KodiLab-summer2018

This directory was created to test the pintool described at https://github.com/stevenpelley/atomic-memory-trace/ 

/src directory contains source files for tests with 1, 2, and 4 threads.

- oneThread.c prints "Hello World!" with two sequential printf calls.
- twoThread.c prints "Hello World!" by printing the two words separately, each in one thread.
- fourThreads.c prints "Hello World!" by printing small half of each word in a given thread.
- $make all builds all executable tests, individual targets are oneThread, twoThreads, and fourThreads 

/memTraces directory contains the pin output files from the trace.so tool 
defined in ~/pin-linux-3.6/atomic-memory-trace/trace/obj-intel64/

- oneThread.out is the output for the single-threaded execution of oneThread.c
- twoThreads.out is the pin output for the 2 threaded execution of twoThreads.c
- fourThreads.out is the pin output for the 4 threaded execution of fourThreads.c


To run, enter:

$./run.sh

This script build alls executables, runs each example with pin, moves the output files to memTraceTests/memTraces/, and cleans itself again.

NOTE: Each time run.sh is run, the old .out files are deleted in memTraces, so if you wish to save multiple runs, add commands to move the old .out files into a new directory
