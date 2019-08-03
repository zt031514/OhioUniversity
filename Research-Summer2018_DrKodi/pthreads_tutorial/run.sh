#script to build and run all pthreads examples

make clean
make all

echo -e "\nHello World Example\n******************************\n"

./hello

echo -e "\nSimple counting examples\n*****************************\n"

./tutorial

echo -e "\nMutex example\n*******************************\n"

./mutex

echo -e "\nJoin example\n****************************\n"

./joins

echo -e "\nConditional Example\n**************************\n"

./condition

echo -e "\nExample from tommurphy.org\n*********************************\n"

./murphy

echo -e "\nEnd Testing\n********************************************\n\n"

make clean


