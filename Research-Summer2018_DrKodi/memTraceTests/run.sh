# script to run all tests in ~/memTraceTests and put output in the memTraces/ directory.

#remake executables from scratch
cd memTraces
rm *.out

cd ../src

make clean
make all

~/pin-linux-3.6/pin -t ~/pin-linux-3.6/atomic-memory-trace/trace/obj-intel64/trace.so -o oneThread.out -- ~/memTraceTests/src/oneThread

~/pin-linux-3.6/pin -t ~/pin-linux-3.6/atomic-memory-trace/trace/obj-intel64/trace.so -o twoThreads.out -- ~/memTraceTests/src/twoThreads

~/pin-linux-3.6/pin -t ~/pin-linux-3.6/atomic-memory-trace/trace/obj-intel64/trace.so -o fourThreads.out -- ./fourThreads

mv *.out ../memTraces
make clean

