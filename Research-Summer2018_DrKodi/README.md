#KodiLab-summer2018

This repository contains any work created during the course of research conducted at Ohio University over the summer of 2018.

memTraceTests/ contains a script to run 3 "Hello world!" programs. Each uses a different number of threads at runtime. All executables are run alongside the pintool trace.so described at https://github.com/stevenpelley/atomic-memory-trace to trace the multithreaded loads and stores from each program.

pthreads_tutorial/ contains example programs using the linux library libpthread-stubs0-dev (pthreads). 

sortTests/ contains output files used with the bash command "sort."

caffeTraces/ contains a script and output files from running the pintool mentioned above on the caffe examples for mnist/LeNet, CIFAR10, and 
